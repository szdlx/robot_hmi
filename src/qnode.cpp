/**
 * @file /src/qnode.cpp
 *
 * @brief Ros communication central!
 *
 * @date February 2011
 **/

/*****************************************************************************
** Includes
*****************************************************************************/
#include <ros/master.h>

#include <ros/ros.h>
#include <ros/network.h>
#include "tf/transform_datatypes.h"//转换函数头文件
//#include "tf2_ros/buffer.h"
//#include "tf2_ros/transform_listener.h"
//#include "tf2/buffer_core.h"
#include <pluginlib/class_list_macros.h>
#include <ros/master.h>
#include <sensor_msgs/image_encodings.h>
#include <sensor_msgs/LaserScan.h>
#include <ackermann_msgs/AckermannDrive.h>
#include <ackermann_msgs/AckermannDriveStamped.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/TwistStamped.h>

#include <cv_bridge/cv_bridge.h>
#include <opencv2/imgproc/imgproc.hpp>

//#include <roscpp/

#include <string>
#include <sstream>
#include "QDebug"
#include "QProcess" // deal cmd
#include "qnode.hpp"
#include "four1.h"

#ifdef __linux__
 #include <signal.h>
 #include <sys/types.h>
 #include <sys/wait.h>
#else

#endif

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace robot_hmi {

/*****************************************************************************
** Implementation
*****************************************************************************/

QNode::QNode(int argc, char** argv ) :
    init_argc(argc), init_argv(argv), car(0){
    // karto_ = std::shared_ptr<QProcess>(new QProcess(this));
    // nav_ = std::shared_ptr<QProcess>(new QProcess(this));
    status = 3;
}

QNode::~QNode(){
    if(ros::isStarted()) {
        control_elevator(0,0);
        exe_robot("killall",{"killall"});  //
    //     if(karto_->state()==QProcess::Running){
    // #ifdef __linux__
    //         ::kill(karto_->processId(),SIGINT); //
    // #else   //windows kill process
    //        QProcess::execute("taskkill", {"/pid", QString::number(karto_->processId()), "/t", "/f"});
    // #endif
    //     }
    //     if(nav_->state()==QProcess::Running){
    // #ifdef __linux__
    //         ::kill(nav_->processId(),SIGINT); //
    // #else   //windows kill process
    //         QProcess::execute("taskkill", {"/pid", QString::number(nav_->processId()), "/t", "/f"});
    // #endif
    //     }
        ros::shutdown(); // explicitly needed since we use ros::start();

        ros::waitForShutdown();
    }
    // qDebug() << "karto state " << karto_->state() << endl;
    // qDebug() << "nav_ state " << nav_->state() << endl;

	wait();
}

bool QNode::init(int car) {
	ros::init(init_argc,init_argv,"robot_hmi");
	if ( ! ros::master::check() ) {
        initFlag = false;
		return false;
	}
    if(!initFlag)
        init_set();
//    auto tf_buffer = tf2_ros::Buffer();
//    auto tf_listener=tf2_ros::TransformListener(tf_buffer);

//    auto str = tf_buffer.allFramesAsString();
//    qDebug()<<QString(str.c_str());

    emit connectMasterSuccess(car);    // connect ROS master success;
	return true;
}

/*
 * Retrieve list topic names and their types.
 * */
bool QNode::getTopicTypes(ros::master::V_TopicInfo& topics) {
    XmlRpc::XmlRpcValue args, result, payload;
    args[0] = ros::this_node::getName();

    if (!ros::master::execute("getTopicTypes", args, result, payload, true)) {
        std::cout << "Failed!" << std::endl;
        return false;
    }
    topics.clear();
//    std::cout << "----------TopicTypes----------" << std::endl;
//    std::cout << "topic_name\t message_name" << std::endl;
    for (int i = 0; i < payload.size(); ++i) {
        topics.push_back(
                ros::master::TopicInfo(std::string(payload[i][0]),
                                       std::string(payload[i][1])));
//        std::string v1 = std::string(payload[i][0]);
//        std::string v2 = std::string(payload[i][1]);
//        std::cout << v1.c_str() << "\t" << v2.c_str() << std::endl;
    }

    return true;
}

/**
 * @brief QNode::updateTopics 更新所有相关话题列表
 * @return  所有话题列表
 */
void QNode::updateTopics(){
    ros::master::V_TopicInfo topic_info;  // 获取所有的ros话题
//    ros::master::getTopics(topic_info);   // 只能获取发布出来的消息
    if(!getTopicTypes(topic_info))
        return ;
//    ros::master:
//    ros::this_node::getName()
    pathList.clear();   // path topic
    mapList.clear();
    polyList.clear();
    decltype(vel_list) last_velist=vel_list;    // 根据表达式推断变量类型
    vel_list.clear();
    QSet<QString> all_topics;
    for (ros::master::V_TopicInfo::const_iterator it = topic_info.begin(); it != topic_info.end(); it++)
    {
      all_topics.insert(it->name.c_str());
    }
    for (ros::master::V_TopicInfo::const_iterator it = topic_info.begin(); it != topic_info.end(); it++)
    {
      if(it->datatype=="nav_msgs/Path"){
          pathList.push_back(it->name);
      }
      if(it->datatype=="nav_msgs/OccupancyGrid")
          mapList.push_back(it->name);
      if(it->datatype=="geometry_msgs/PolygonStamped")  // robot footprint
          polyList.push_back(it->name);
      if(it->datatype.find("ackermann_msgs/AckermannDrive") != it->datatype.npos
              || it->datatype.find("geometry_msgs/Twist") != it->datatype.npos ){
          vel_list.insert(it->name, it->datatype);

      }
    }
    if(last_velist != vel_list){
        qDebug() << "vel topics list update";
        emit vel_list_changed();
    }
}

QList<QString> QNode::getTopics(const QString& message_types){
    ros::master::V_TopicInfo topic_info;  // 获取所有的ros话题
    ros::master::getTopics(topic_info);
    QSet<QString> all_topics;
    for (ros::master::V_TopicInfo::const_iterator it = topic_info.begin(); it != topic_info.end(); it++)
    {
      all_topics.insert(it->name.c_str());
    }
    QList<QString> topics;
    for (ros::master::V_TopicInfo::const_iterator it = topic_info.begin(); it != topic_info.end(); it++)
    {
      if (message_types.contains(it->datatype.c_str()))   // 如果话题类型相同
      {
          QString topic = it->name.c_str();
          topics.append(topic);
      }
    }
    return topics;
}


QSet<QString> QNode::getTopics(const QSet<QString>& message_types, const QSet<QString>& message_sub_types, const QList<QString>& transports)
{
  ros::master::V_TopicInfo topic_info;  // 获取所有的ros话题
  ros::master::getTopics(topic_info);

  QSet<QString> all_topics;
  for (ros::master::V_TopicInfo::const_iterator it = topic_info.begin(); it != topic_info.end(); it++)
  {
    all_topics.insert(it->name.c_str());
  }

  QSet<QString> topics;
  for (ros::master::V_TopicInfo::const_iterator it = topic_info.begin(); it != topic_info.end(); it++)
  {
    if (message_types.contains(it->datatype.c_str()))   // 如果话题类型相同
    {
      QString topic = it->name.c_str();

      // add raw topic
      topics.insert(topic);
      //qDebug("ImageView::getTopics() raw topic '%s'", topic.toStdString().c_str());

      // add transport specific sub-topics
      for (QList<QString>::const_iterator jt = transports.begin(); jt != transports.end(); jt++)
      {
        if (all_topics.contains(topic + "/" + *jt))
        {
          QString sub = topic + " " + *jt;
          topics.insert(sub);
          //qDebug("ImageView::getTopics() transport specific sub-topic '%s'", sub.toStdString().c_str());
        }
      }
    }
    if (message_sub_types.contains(it->datatype.c_str()))
    {
      QString topic = it->name.c_str();
      int index = topic.lastIndexOf("/");   // 找到"/"最后出现的位置，找不到说明不是消息类型
      if (index != -1)
      {
        topic.replace(index, 1, " ");
        topics.insert(topic);
        //qDebug("ImageView::getTopics() transport specific sub-topic '%s'", topic.toStdString().c_str());
      }
    }
  }
  return topics;
}

void QNode::cmd_output(int car){
    if ( ! ros::master::check() ) { // if still connect ROS master failed
        qDebug() << "connect again and failed!" << endl;
        emit connectMasterFailed(car);
        initFlag = false;
        return ;
    }
    if(!initFlag)
        init_set();
    emit connectMasterSuccess(car);    // connect ROS master success;
}



void QNode::publish_vel(QString vel_topic){
//    if(pub_list.count(vel_topic)>0){
//        *vel_pub = pub_list[vel_topic];
//    }
//    ros::Publisher pub;
//    ros::NodeHandle n;
//    pub=n.advertise<geometry_msgs::Twist>(vel_topic.toStdString(),1000);
//    pub_list.insert({vel_topic,pub});
}

void QNode::robot_control(QPair<int,int> rbt){
    robot_msg::robot rdata;
    rdata.header.stamp=ros::Time::now();
    rdata.mode=rbt.first;
    rdata.state=rbt.second;
    rdata.comparams={"rosrun","map_server","map_saver","-f","map"};
    robot_pub.publish(rdata);
}

void QNode::exe_robot(QString type, QVector<QString> rbt){
    robot_msg::robot rdata;
    rdata.header.stamp=ros::Time::now();
    rdata.mode=0;rdata.state=0;
    rdata.type = type.toStdString();
    for(auto it:rbt){
        rdata.comparams.push_back(it.toStdString());
    }
    robot_pub.publish(rdata);
}

void QNode::sendTrackPath(std::vector<std::vector<double>> path){
    action_pure::purePursuitGoal goal;
    goal.pathx=std::vector<float>(path[0].begin(),path[0].end());
    goal.pathy=std::vector<float>(path[1].begin(),path[1].end());
    pure_client->sendGoal(goal);
    ROS_INFO("send pure goal");
}

void QNode::cmd_error_output(int car){
    qDebug() << "connect failed" << endl;
    emit connectMasterFailed(car); // connect ROS master failed;
}

QList<QString> QNode::getImgTopiclist(){
    QSet<QString> message_types;
    message_types.insert("sensor_msgs/Image");
    QSet<QString> message_sub_types;
    message_sub_types.insert("sensor_msgs/CompressedImage");

    // get declared transports
    QList<QString> transports;
    ros::NodeHandle n;
    image_transport::ImageTransport it(n);
    std::vector<std::string> declared = it.getDeclaredTransports();
    for (std::vector<std::string>::const_iterator it = declared.begin(); it != declared.end(); it++)
    {
//      qDebug("ImageView::updateTopicList() declared transport '%s'", it->c_str());
      QString transport = it->c_str();

      // strip prefix from transport name
      QString prefix = "image_transport/";
      if (transport.startsWith(prefix))
      {
        transport = transport.mid(prefix.length());
      }
      transports.append(transport);
    }

    // fill combo box
    QList<QString> topics = getTopics(message_types, message_sub_types, transports).values();
    topics.append("");
    qSort(topics);
    return topics;
}

bool QNode::init(const std::string &master_url, const std::string &host_url, int car) {
	std::map<std::string,std::string> remappings;
	remappings["__master"] = master_url;
	remappings["__hostname"] = host_url;
	ros::init(remappings,"robot_hmi");
    qDebug() << "check if roscore is ready\n";
//    ros::WallDuration d(1);
//    ros::master::setRetryTimeout(d);
    if (!ros::master::check())
    {
        initFlag=false;
        return false;
    }
    ros::Time::init();
    std::cout << "master started!" << std::endl;
    if(!initFlag)   // 避免重复初始化
        init_set();
    emit connectMasterSuccess(car);    // connect ROS master success;

    return true;
}

void QNode::init_set(){
    initFlag = true;
//    nav_pid = -1;
//    slam_pid = -1;
    ros::start(); // explicitly needed since our nodehandle is going out of scope.

    ros::NodeHandle nh_;
    std::string ugv[2] ={"/UGV0", "/UGV1"};
    goal_pub[0]=nh_.advertise<geometry_msgs::PoseStamped>(ugv[0]+"/goal",1000);
    goal_pub[1]=nh_.advertise<geometry_msgs::PoseStamped>(ugv[0]+"/goal",1000);
    marker_pub[0]=nh_.advertise<visualization_msgs::Marker>(ugv[0]+"/marker",1000);
    marker_pub[1]=nh_.advertise<visualization_msgs::Marker>(ugv[1]+"/marker",1000);
    motor_pub[0]=nh_.advertise<left_motor::com>(ugv[0]+"/elevator",1000);
    motor_pub[1]=nh_.advertise<left_motor::com>(ugv[1]+"/elevator",1000);
    robot_pub = nh_.advertise<robot_msg::robot>("slam_nav",100);

    // 利用boost::bind 函数 绑定 额外参数
    power_sub[0] = nh_.subscribe<ros_four1_msg::four1>(ugv[0]+"/four_info",1000,boost::bind(&QNode::power_callback,this, _1, 0));
    power_sub[1] = nh_.subscribe<ros_four1_msg::four1>(ugv[1]+"/four_info",1000,boost::bind(&QNode::power_callback,this, _1, 1));
    odom_sub[0] = nh_.subscribe<nav_msgs::Odometry>(ugv[0]+"/odom",1000,boost::bind(&QNode::odom_callback,this,_1,0));
    odom_sub[1] = nh_.subscribe<nav_msgs::Odometry>(ugv[1]+"/odom",1000,boost::bind(&QNode::odom_callback,this,_1,1));
    // 订阅GPS消息
    gps_sub[0] = nh_.subscribe<gps_ksxt_msg::GPS_ksxt>(ugv[0]+"/gps",1000, boost::bind(&QNode::gps_callback,this,_1,0));
    gps_sub[1] = nh_.subscribe<gps_ksxt_msg::GPS_ksxt>(ugv[1]+"/gps",1000, boost::bind(&QNode::gps_callback,this,_1,1));
    laser_sub[0] = nh_.subscribe<sensor_msgs::LaserScan>(ugv[0]+"/laser",1000, boost::bind(&QNode::laser_callback, this,_1,0));
    laser_sub[1] = nh_.subscribe<sensor_msgs::LaserScan>(ugv[1]+"/laser",1000, boost::bind(&QNode::laser_callback, this,_1,1));
    nh_.subscribe<geometry_msgs::Pose>("/amcl_odom",1000,boost::bind(&QNode::map_pose,this,_1,0));
    mbstate = nh_.subscribe<actionlib_msgs::GoalStatusArray>("/move_base/status",100, &QNode::actionCallback,this);

//    pthread_create(&pth, NULL, &QNode::actionThread,NULL);
    pure_client = new PureClient("pure_pursuit",true);
    pure_client->waitForServer(ros::Duration(1.0));

    start();

}

void QNode::disinit()
{
    if (ros::isStarted()) {
        ROS_INFO("ROS will shutdown");
        ros::shutdown();
        ros::waitForShutdown();
    }
    initFlag = false;
    this->exit();
}


/**
 * @brief 发布升降机高度与发热靶开关
 * 
 * @param hight 
 * @param sw 
 */
void QNode::control_elevator(int hight, bool sw){
    left_motor::com motor;
    motor.Data_1=hight;
    motor.Data_2=sw;
    motor_pub[car].publish(motor);
}

void QNode::set_goal(double x,double y,double z)
{
    geometry_msgs::PoseStamped goal;
    //设置frame
    goal.header.frame_id="map";
    //设置时刻
    goal.header.stamp=ros::Time::now();
    goal.pose.position.x=x;
    goal.pose.position.y=y;
    goal.pose.orientation.z=z;
    goal_pub[car].publish(goal);
}


void QNode::gps_callback(const gps_ksxt_msg::GPS_ksxtConstPtr &msg, int car){

    if(car!=this->car){
        return ;
    }
//   解析出数据中 位置信息与航向信息
    emit gps_pos(msg->posqual, msg->headingqual,msg->east, msg->north, msg->heading);
}

uint meet_cnt=0;
void QNode::laser_callback(const sensor_msgs::LaserScanConstPtr &msg, int car){
    if(this->car != car) return ;
//    qDebug() << "laser ang:" << msg->angle_increment <<" " << msg->angle_min << " " << msg->angle_max;
    float mindis=msg->range_max;
    float angl=60*M_PI/180.0, angm=300*M_PI/180;    // 检测前方 -60~60 范围内的障碍物
    float ang=0;
    int cnt=0;
    float obsang=0;
    float maxang=0;
    for (auto dis : msg->ranges) {
        cnt++;
        ang += msg->angle_increment;

        if(ang>=angl && ang<=angm)  //过滤激光雷达范围 (90-270)车体后面
            continue;
        if(dis<=msg->range_min){
            continue;
        }
        if(dis < mindis ){   // 记录最小距离
            mindis = dis;
            obsang += msg->angle_increment;
        }
        else{
            obsang = 0;
            maxang = fmax(obsang,maxang);
        }
    }
    if(mindis<0.5 && maxang > 10/180*M_PI){ // 小于0.5m 认为遇到障碍物
        meet_cnt = fmax(meet_cnt++,1000);
        if(meet_cnt>100){
            emit obs_meet(mindis,car);  // 发送遇到障碍物信号
            meetObs=true;
        }
    }
    else {
        meet_cnt=fmax(meet_cnt--,1);
        meetObs = false;
    }
        
//    qDebug()<<"lasr count " << cnt << endl;
}


void QNode::power_callback(const ros_four1_msg::four1ConstPtr &msg, int car)
{
    if(car!=this->car){
        return ;
    }
//    qDebug() << "gps car is " << car << endl;
    double base_width=470;  // mm 轴距
    double vel = (msg->FRSpeed+msg->FLSpeed)/2000.0;  // mm/s -> m/s
    double angv = 2.0*(msg->FRSpeed-msg->FLSpeed)/base_width;
    emit speed_vel(vel,angv);
    emit power_vel(msg->Voltage);
}

void QNode::map_pose(const geometry_msgs::Pose::ConstPtr &msg, int car){
    tf::Quaternion quat;
    tf::quaternionMsgToTF(msg->orientation, quat);
    double roll, pitch, yaw;//定义存储r\p\y的容器
    tf::Matrix3x3(quat).getRPY(roll, pitch, yaw);//进行转换
    emit pose2D(msg->position.x,msg->position.y, yaw);
}

void QNode::actionCallback(const actionlib_msgs::GoalStatusArrayConstPtr &goalstates){
    status = 3;
    for (int i = 0; i < goalstates->status_list.size(); ++i) {
            auto it = goalstates->status_list[i];
            status = MIN(status,it.status);

    }
    // ROS_INFO("status:%d ", status);
}

void QNode::actionThread(){
//    Client client("pure_pursuit", true);
//    client.waitForServer();

}


void QNode::odom_callback(const nav_msgs::Odometry::ConstPtr &msg, int car)
{
    visualization_msgs::Marker marker;
    marker.header.frame_id = "odom";
    marker.header.stamp = ros::Time();
//    marker.ns = "my_namespace";
    marker.id = 0;
    marker.type = visualization_msgs::Marker::SPHERE;
    marker.action = visualization_msgs::Marker::ADD;
    marker.pose.position= msg->pose.pose.position;
    marker.pose.orientation = msg->pose.pose.orientation;
    marker.scale.x = 1;
    marker.scale.y = 0.1;
    marker.scale.z = 0.1;
    marker.color.a = 1.0; // Don't forget to set the alpha!
    marker.color.r = 0.0;
    marker.color.g = 1.0;
    marker.color.b = 0.0;
    //only if using a MESH_RESOURCE marker type:
//    marker.mesh_resource = "package://pr2_description/meshes/base_v0/base.dae";
    marker_pub[car].publish( marker );
    emit showMarker("/UGV"+QString::number(car)+"/marker", car);

//    qDebug() << "odom car is " << *car << endl;
    if(car!=this->car){
        return ;
    }
//    qDebug() << "gps car is " << car << endl;
    tf::Quaternion quat;
    tf::quaternionMsgToTF(msg->pose.pose.orientation, quat);
    double roll, pitch, yaw;//定义存储r\p\y的容器
    tf::Matrix3x3(quat).getRPY(roll, pitch, yaw);//进行转换
    emit position(msg->pose.pose.position.x,msg->pose.pose.position.y, yaw);
    emit pose2D(msg->pose.pose.position.x,msg->pose.pose.position.y, yaw);
}
/**
 * @brief 设置下发速度
 * 
 * @param linear 
 * @param angular 
 */
void QNode::set_cmd_vel(float linear,float angular)
{
    // if(nav_->state()==QProcess::Running)
    //     return ;    //
    if(status != 3)  // move base is running
        return ;
    if(meetObs) {
        if(linear>0) linear=0;
    }

    if(ros::ok() && vel_pub){
        if(vel_topic_type==TWIST){
            geometry_msgs::Twist twist;
            twist.linear.x=1*linear;
            twist.linear.y=1*linear;
            twist.linear.z=0;
            twist.angular.x=0;
            twist.angular.y=0;
            twist.angular.z=angular;
            vel_pub.publish(twist);
        } else if(vel_topic_type==TWIST_STAMPED){
            geometry_msgs::TwistStamped twist;
            twist.header.stamp = ros::Time::now();
            twist.twist.linear.x=1*linear;
            twist.twist.linear.y=1*linear;
            twist.twist.linear.z=0;
            twist.twist.angular.x=0;
            twist.twist.angular.y=0;
            twist.twist.angular.z=angular;
            vel_pub.publish(twist);
        }
        if(vel_topic_type==ACKERMANN){
            ackermann_msgs::AckermannDrive acker;
            acker.speed = linear;
            acker.steering_angle = angular;
            vel_pub.publish(acker);
        } else if(vel_topic_type==ACKERMANN_STAMPED){
            ackermann_msgs::AckermannDriveStamped acker;
            acker.header.stamp = ros::Time::now();
            acker.drive.speed = linear;
            acker.drive.steering_angle = angular;
            vel_pub.publish(acker);
        }
    }

}


void QNode::set_cmd_topic(const QString& topic){
    if(!initFlag) return;
    if(topic != vel_topic){
        vel_topic = topic;
        if(topic == ""){
            vel_pub.shutdown();
        } else {
            auto str = topic.toStdString();
            if(vel_list.contains(str)){
                ros::NodeHandle nh_;
                if(vel_list.find(str).value()=="ackermann_msgs/AckermannDrive"){
                    if(vel_topic_type != ACKERMANN) vel_pub.shutdown();
                    vel_topic_type = ACKERMANN;
                    vel_pub = nh_.advertise<ackermann_msgs::AckermannDrive>(str, 1);
                    qDebug() << "change topic type to ackermann_msgs/AckermannDrive";
                }
                else if(vel_list.find(str).value()=="ackermann_msgs/AckermannDriveStamped"){
                    if(vel_topic_type != ACKERMANN_STAMPED) vel_pub.shutdown();
                    vel_topic_type = ACKERMANN_STAMPED;
                    vel_pub = nh_.advertise<ackermann_msgs::AckermannDriveStamped>(str, 1);
                    qDebug() << "change topic type to ackermann_msgs/AckermannDriveStamped";
                }
                else if(vel_list.find(str).value()=="geometry_msgs/Twist"){
                    if(vel_topic_type != TWIST) vel_pub.shutdown();
                    vel_topic_type = TWIST;
                    vel_pub = nh_.advertise<geometry_msgs::Twist>(str, 1);
                    qDebug() << "change topic type to geometry_msgs/Twist";
                }
                else if(vel_list.find(str).value()=="geometry_msgs/TwistStamped"){
                    if(vel_topic_type != TWIST_STAMPED) vel_pub.shutdown();
                    vel_topic_type = TWIST_STAMPED;
                    vel_pub = nh_.advertise<geometry_msgs::TwistStamped>(str, 1);
                    qDebug() << "change topic type to geometry_msgs/Twist";
                }
            }
        }
    }
}

void QNode::run() {
	ros::Rate loop_rate(1);
	int count = 0;
	while ( ros::ok() ) {
		ros::spinOnce();
	}
	std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
	Q_EMIT rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
}


void QNode::log( const LogLevel &level, const std::string &msg) {
	logging_model.insertRows(logging_model.rowCount(),1);
	std::stringstream logging_model_msg;
	switch ( level ) {
		case(Debug) : {
				ROS_DEBUG_STREAM(msg);
				logging_model_msg << "[DEBUG] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Info) : {
				ROS_INFO_STREAM(msg);
				logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Warn) : {
				ROS_WARN_STREAM(msg);
				logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Error) : {
				ROS_ERROR_STREAM(msg);
				logging_model_msg << "[ERROR] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Fatal) : {
				ROS_FATAL_STREAM(msg);
				logging_model_msg << "[FATAL] [" << ros::Time::now() << "]: " << msg;
				break;
		}
	}
	QVariant new_row(QString(logging_model_msg.str().c_str()));
	logging_model.setData(logging_model.index(logging_model.rowCount()-1),new_row);
	Q_EMIT loggingUpdated(); // used to readjust the scrollbar
}

void QNode::roslaunch(bool checked){
    if(checked){  // navigation
        exe_robot("nav",{"roslaunch", "mission_sim_bringup", "mission_start.launch"});
        // QProcess can't closee all pid
//         if(karto_->state()==QProcess::Running){
//             qDebug()<<"kartor is running" << endl;
// #ifdef __linux__
//             ::kill(karto_->processId(),SIGINT); // qprocess 只能调用sigkill信号，无法杀死子进程
// #else   //windows kill process
//         QProcess::execute("taskkill", {"/pid", QString::number(karto_->processId()), "/t", "/f"});
// #endif
//         }

//         if(nav_->state()==QProcess::NotRunning){
//             nav_->start("roslaunch",{"mission_sim_bringup", "mission_start.launch"});
//             nav_->waitForStarted();
//         }

//        if(slam_pid!=-1){
//            try {
//                roslaunch_slam->stop(slam_pid, SIGINT);
//                slam_pid = -1;
//            }
//            catch (std::exception const &exception) {
//                ROS_WARN("%s", exception.what());
//            }
//        }
//        if(roslaunch_nav==NULL) roslaunch_nav = new ROSLaunchManager;
//        try {
//            nav_pid = roslaunch_nav->start(
//                "turtlebot3_navigation", "turtlebot3_navigation.launch");
//        }
//        catch (std::exception const &exception) {
//            ROS_WARN("%s", exception.what());
//        }
    }
    else {  // slam
        exe_robot("slam",{"roslaunch", "car_slam", "karto_slam.launch"});
//         if(nav_->state()==QProcess::Running){
//             qDebug()<<"nav_ is running" << endl;
// #ifdef __linux__
//             ::kill(nav_->processId(),SIGINT); // qprocess 只能调用sigkill信号，无法杀死子进程
// #else   //windows kill process
//             QProcess::execute("taskkill", {"/pid", QString::number(nav_->processId()), "/t", "/f"});
// #endif
//         }
//         if(karto_->state()==QProcess::NotRunning){
//             karto_->start("roslaunch",{"car_slam", "karto_slam.launch"});
//             karto_->waitForStarted();
//         }

//        if(nav_pid!=-1){
//            try {
//                roslaunch_nav->stop(nav_pid, SIGINT);
//                nav_pid=-1;
//            }
//            catch (std::exception const &exception) {
//                ROS_WARN("%s", exception.what());
//            }
//        }
//        if(roslaunch_slam==NULL) roslaunch_slam = new ROSLaunchManager;
//        try {
//            if(slam_pid==-1 )
//                slam_pid = roslaunch_slam->start(
//                    "car_slam", "karto_slam.launch");
//        }
//        catch (std::exception const &exception) {
//            ROS_WARN("%s", exception.what());
//        }
    }
}

}  // namespace robot_hmi
