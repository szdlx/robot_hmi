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

#include <ros/network.h>
#include <ros/ros.h>
#include <sstream>
#include <std_msgs/String.h>
#include <string>

#include "../include/cyrobot_monitor/Num.h"
#include "../include/cyrobot_monitor/carTop.h"
#include "../include/cyrobot_monitor/formationwithtask.h"
#include "../include/cyrobot_monitor/qnode.hpp"
#include "../include/cyrobot_monitor/reconnoitrewithtask.h"

#include <QDebug>
#include <QEventLoop>
#include <QTimer>

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace cyrobot_monitor {

/*****************************************************************************
** Implementation
*****************************************************************************/

QNode::QNode(int argc, char** argv)
    : init_argc(argc)
    , init_argv(argv)
{
    //    读取topic的设置
    QSettings topic_setting("topic_setting", "cyrobot_monitor");
    //car0
    odom_topic[0] = topic_setting.value("topic_odom0", "raw_odom").toString(); //默认值raw_odom
    vel_topic[0] = topic_setting.value("topic_vel0", "cmd_vel").toString();
    msgtype[0] = topic_setting.value("vel_type0", 0).toInt();
    //car1
    odom_topic[1] = topic_setting.value("topic_odom1", "raw_odom").toString();
    vel_topic[1] = topic_setting.value("topic_vel1", "cmd_vel").toString();
    msgtype[1] = topic_setting.value("vel_type1", 0).toInt();
    //car2
    odom_topic[2] = topic_setting.value("topic_odom2", "raw_odom").toString();
    vel_topic[2] = topic_setting.value("topic_vel2", "cmd_vel").toString();
    msgtype[2] = topic_setting.value("vel_type2", 0).toInt();
    //car3
    odom_topic[3] = topic_setting.value("topic_odom3", "raw_odom").toString();
    vel_topic[3] = topic_setting.value("topic_vel3", "cmd_vel").toString();
    msgtype[3] = topic_setting.value("vel_type3", 0).toInt();
    //car4
    odom_topic[4] = topic_setting.value("topic_odom4", "raw_odom").toString();
    vel_topic[4] = topic_setting.value("topic_vel4", "cmd_vel").toString();
    msgtype[4] = topic_setting.value("vel_type4", 0).toInt();

    power_topic = topic_setting.value("topic_power", "power").toString();
    pose_topic = topic_setting.value("topic_amcl", "amcl_vel").toString();
    power_min = topic_setting.value("power_min", "min").toString();
    power_max = topic_setting.value("power_max", "max").toString();

    image_id.resize(5);
}

QNode::~QNode()
{
    if (ros::isStarted()) {
        ros::shutdown(); // explicitly needed since we use ros::start();
        ros::waitForShutdown();
    }
    wait();
}

void QNode::rosinit()
{ //ros初始化设置
    ros::start(); // explicitly needed since our nodehandle is going out of scope.
    ros::NodeHandle n;
    // Add your ros communications here.

    typedef void (QNode::*fp)(const geometry_msgs::Twist::ConstPtr&);
    fp twist[] = { &QNode::speedCallback0, &QNode::speedCallback1,
        &QNode::speedCallback2, &QNode::speedCallback3,
        &QNode::speedCallback4 }; // b[] 为一个指向函数的指针数组
    //   typedef void  (QNode::*fpa)(const ackermann_msgs::AckermannDriveStamped::ConstPtr&);
    //   fpa acker[] = {&QNode::ackerman_speed};

    for (int i = 0; i < 5; i++) {

        if (msgtype[i] == 0) {
            cmdVel_sub[i] = n.subscribe<geometry_msgs::Twist>(vel_topic[i].toStdString(), 200, twist[i], this);
            cmd_pub_twist[i] = n.advertise<geometry_msgs::Twist>(vel_topic[i].toStdString(), 1000);
            qDebug() << i << "vel_topic:" << vel_topic[i];
        }
        if (msgtype[i] == 1) { //TODO
            cmdVel_sub[i] = n.subscribe(vel_topic[i].toStdString(), 200, &QNode::ackerman_speed, this);
            cmd_pub_ackermann[i] = n.advertise<ackermann_msgs::AckermannDriveStamped>(vel_topic[i].toStdString(), 1000);
            qDebug() << i << "ackermann_topic:" << vel_topic[i];
        }
    }

    //添加道路信息订阅 TODO
    QSettings road_setting("road_topic", "cyrobot_monitor");
    road_sub = n.subscribe(road_setting.value("road/topic", "").toString().toStdString(), 10, &QNode::roadCallback, this);
    carpos_sub = n.subscribe(road_setting.value("carpos/topic", "").toString().toStdString(), 10, &QNode::carPosCallback, this);

    //猛犸车消息订阅
    //    CarTop_sub = n.subscribe("/car_message", 200, &QNode::carTopCallback, this);
    //    std::string veltopic = vel_topic[0].toStdString();
    //    qDebug() << QString::fromStdString(veltopic);
    //    carVel_pub = n.advertise<ackermann_msgs::AckermannDriveStamped>("/ackermann_cmd", 1000);

    power_sub = n.subscribe(power_topic.toStdString(), 1000, &QNode::powerCallback, this);
    //机器人位置话题
    pos_sub = n.subscribe(pose_topic.toStdString(), 1000, &QNode::poseCallback, this);
    //导航目标点发送话题
    goal_pub = n.advertise<geometry_msgs::PoseStamped>("move_base_simple/goal", 1000);

    //编队消息相关话题的发布
    formation_task_pub = n.advertise<mission_parse::formationwithtask>("/formation_task", 1000); //,&QNode::formationCallback,this);
    reconnoitre_task_pub = n.advertise<mission_parse::reconnoitrewithtask>("/reconnoitre_task", 1000); //,&QNode::reconnoitreCallback,this);
    reconnoitre_goal_pub = n.advertise<move_base_msgs::MoveBaseActionGoal>("/move_base/goal", 1000); //,&QNode::reconnoitregoalCallback,this);

    start();
    isWork = true;
}

bool QNode::init()
{
    ros::init(init_argc, init_argv, "cyrobot_monitor");
    if (!ros::master::check()) {
        return false;
    }
    rosinit();
    return true;
}

//初始化的函数*********************************
bool QNode::init(const std::string& master_url, const std::string& host_url)
{
    std::map<std::string, std::string> remappings;
    remappings["__master"] = master_url;
    remappings["__hostname"] = host_url;
    ros::init(remappings, "cyrobot_monitor");
    if (!ros::master::check()) {
        return false;
    }
    rosinit(); //ros初始化
    return true;
}

void QNode::disinit()
{
    if (ros::isStarted()) {
        ROS_INFO("ROS will shutdown");
        ros::shutdown();
        ros::waitForShutdown();
    }
    isWork = false;
    this->exit();
}

QMap<QString, QString> QNode::get_topic_list()
{
    ros::master::V_TopicInfo topic_list;
    ros::master::getTopics(topic_list);
    //    ros::master::getNodes(formation_task)
    QMap<QString, QString> res;
    for (auto topic : topic_list) {

        res.insert(QString::fromStdString(topic.name), QString::fromStdString(topic.datatype));
    }
    return res;
}
//机器人位置话题的回调函数
void QNode::poseCallback(const geometry_msgs::PoseWithCovarianceStamped& pos)
{
    emit position(pos.header.frame_id.data(), pos.pose.pose.position.x, pos.pose.pose.position.y, pos.pose.pose.orientation.z, pos.pose.pose.orientation.w);
    //    qDebug()<<<<" "<<pos.pose.pose.position.y;
}
void QNode::powerCallback(const std_msgs::Float32& message_holder)
{

    emit power(message_holder.data);
}
void QNode::myCallback(const std_msgs::Float64& message_holder)
{
    qDebug() << message_holder.data << endl;
}
//发布导航目标点信息
void QNode::set_goal(QString frame, double x, double y, double z, double w)
{
    geometry_msgs::PoseStamped goal;
    //设置frame
    goal.header.frame_id = frame.toStdString();
    //设置时刻
    goal.header.stamp = ros::Time::now();
    goal.pose.position.x = x;
    goal.pose.position.y = y;
    goal.pose.position.z = 0;
    goal.pose.orientation.z = z;
    goal.pose.orientation.w = w;
    goal_pub.publish(goal);
    ros::spinOnce();
}

//速度回调函数
void QNode::speedCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
    emit speed_x(msg->linear.x);
    emit speed_y(msg->angular.z);
}

void QNode::speedCallback0(const geometry_msgs::Twist::ConstPtr& msg)
{
    emit speed_x(msg->linear.x);
    emit speed_y(msg->angular.z);
}
void QNode::speedCallback1(const geometry_msgs::Twist::ConstPtr& msg)
{
    emit speed_x(msg->linear.x);
    emit speed_y(msg->angular.z);
}
void QNode::speedCallback2(const geometry_msgs::Twist::ConstPtr& msg)
{
    emit speed_x(msg->linear.x);
    emit speed_y(msg->angular.z);
}
void QNode::speedCallback3(const geometry_msgs::Twist::ConstPtr& msg)
{
    emit speed_x(msg->linear.x);
    emit speed_y(msg->angular.z);
}
void QNode::speedCallback4(const geometry_msgs::Twist::ConstPtr& msg)
{
    emit speed_x(msg->linear.x);
    emit speed_y(msg->angular.z);
}

void QNode::ackerman_speed(const ackermann_msgs::AckermannDriveStamped::ConstPtr& msg)
{
    qDebug() << "speed:" << msg->drive.speed << "/t turn_angle:" << msg->drive.steering_angle << endl;
}

void QNode::run()
{

    ros::Rate loop_rate(10);
    //当当前节点没有关闭时
    while (ros::ok()) {
        //调用消息处理回调函数
        ros::spinOnce();

        loop_rate.sleep();
    }
    //如果当前节点关闭
    Q_EMIT rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
}
//发布机器人速度控制
void QNode::move_base(char k, float speed_linear, float speed_trun, int curCar)
{
    //fCar[0].leader = 0;
    std::map<char, std::vector<float>> moveBindings {

        { 'i', { 1, 0, 0, 0 } },
        { 'o', { 1, 0, 0, -1 } },
        { 'j', { 0, 0, 0, 1 } },
        { 'l', { 0, 0, 0, -1 } },
        { 'u', { 1, 0, 0, 1 } },
        { ',', { -1, 0, 0, 0 } },
        { '.', { -1, 0, 0, 1 } },
        { 'm', { -1, 0, 0, -1 } },
        { 'O', { 1, -1, 0, 0 } },
        { 'I', { 1, 0, 0, 0 } },
        { 'J', { 0, 1, 0, 0 } },
        { 'L', { 0, -1, 0, 0 } },
        { 'U', { 1, 1, 0, 0 } },
        { '<', { -1, 0, 0, 0 } },
        { '>', { -1, -1, 0, 0 } },
        { 'M', { -1, 1, 0, 0 } },
        { 't', { 0, 0, 1, 0 } },
        { 'b', { 0, 0, -1, 0 } },
        { 'k', { 0, 0, 0, 0 } },
        { 'K', { 0, 0, 0, 0 } }
    };
    char key = k;
    //计算是往哪个方向
    float x = moveBindings[key][0];
    float y = moveBindings[key][1];
    float z = moveBindings[key][2];
    float th = moveBindings[key][3];
    //计算线速度和角速度
    float speed = speed_linear;
    float turn = speed_trun;
    // Update the Twist message
    geometry_msgs::Twist twist;
    twist.linear.x = x * speed;
    twist.linear.y = y * speed;
    twist.linear.z = z * speed;

    twist.angular.x = 0;
    twist.angular.y = 0;
    twist.angular.z = th * turn;

    //    vel.header.frame_id;
    if (msgtype[curCar] == 0) {
        qDebug() << "twist control pub";
        cmd_pub_twist[curCar].publish(twist);
    }

    ros::spinOnce();
}

void QNode::ackerman_control(float speed_linear, float turn_angle, int curCar)
{

    //     // Publish it and resolve any remaining callbacks
    ackermann_msgs::AckermannDriveStamped vel;
    vel.drive.speed = speed_linear;
    //     vel.drive.jerk = 0;
    //     vel.drive.acceleration=0;
    //     vel.drive.steering_angle_velocity = ;
    vel.drive.steering_angle = turn_angle;
    vel.header.stamp = ros::Time::now();
    vel.header.seq = 0;
    vel.header.frame_id = "car";
    //    qDebug() << "ackerman control pub";
    if (msgtype[curCar] == 1) {
        qDebug() << "ackerman control pub";
        cmd_pub_ackermann[curCar].publish(vel); //TODO
    }
    //        carVel_pub.publish(vel);
    //    qDebug() << "ackerman control";
    ros::spinOnce();
}

//订阅图片话题，并在label上显示
void QNode::Sub_Image(QString topic, int frame_id, int leader_id)
{
    ros::NodeHandle n;
    image_transport::ImageTransport it_(n);
    leader_qnode_id = leader_id;

    qDebug() << "~~~~~~~~~~~~~~~~~~~~~~~~~~ ";
    qDebug() << "leader_qnode_id: " << leader_qnode_id;

    switch (frame_id) {
    case 0:
        image_sub0 = it_.subscribe(topic.toStdString(), 100, &QNode::imageCallback0, this);
        break;
    case 1:
        image_sub1 = it_.subscribe(topic.toStdString(), 100, &QNode::imageCallback1, this);
        break;
    case 2:
        image_sub2 = it_.subscribe(topic.toStdString(), 100, &QNode::imageCallback2, this);
        break;
    case 3:
        image_sub3 = it_.subscribe(topic.toStdString(), 100, &QNode::imageCallback3, this);
        break;
    case 4:
        image_sub4 = it_.subscribe(topic.toStdString(), 100, &QNode::imageCallback4, this);
        break;
    }
    ros::spinOnce();
}

//图像话题的回调函数
void QNode::imageCallback(const sensor_msgs::ImageConstPtr& msg, int& frame_id)
{
    //     cv_bridge::CvImagePtr cv_ptr[5];
    cv_bridge::CvImagePtr cv_ptr;
    //     int frame_id = id;
    try {

        cv_ptr = cv_bridge::toCvCopy(msg, videoSet[frame_id].encode[videoSet[frame_id].id]);
        QImage im = Mat2QImage(cv_ptr->image, videoSet[frame_id].rotate);
        emit Show_image(frame_id, im.mirrored(videoSet[frame_id].horMir, videoSet[frame_id].verMir));

    } catch (cv_bridge::Exception& e) {

        log(Error, ("video frame0 exception: " + QString(e.what())).toStdString());
        return;
    }
}

//图像话题的回调函数
void QNode::imageCallback0(const sensor_msgs::ImageConstPtr& msg)
{
    cv_bridge::CvImagePtr cv_ptr;
    try {
        //         cv_bridge::CvImageConstPtr cv_ptr = cv_bridge::toCvShare(msg, sensor_msgs::image_encodings::BGR8);
        cv_ptr = cv_bridge::toCvCopy(msg, videoSet[0].encode[videoSet[0].id]);
        //         QImage im=Mat2QImage(cv_ptr->image,videoSet[0].rotate);

        if (leader_qnode_id != 0) {
            QImage im = Mat2QImage(cv_ptr->image, videoSet[leader_qnode_id].rotate);
            emit Show_image(leader_qnode_id, im.mirrored(videoSet[leader_qnode_id].horMir, videoSet[leader_qnode_id].verMir));
        } else {
            QImage im = Mat2QImage(cv_ptr->image, videoSet[0].rotate);
            emit Show_image(0, im.mirrored(videoSet[0].horMir, videoSet[0].verMir));
        }
    } catch (cv_bridge::Exception& e) {

        log(Error, ("video frame0 exception: " + QString(e.what())).toStdString());
        return;
    }
}
//图像话题的回调函数
void QNode::imageCallback1(const sensor_msgs::ImageConstPtr& msg)
{
    cv_bridge::CvImagePtr cv_ptr;
    try {
        //深拷贝转换为opencv类型
        cv_ptr = cv_bridge::toCvCopy(msg, videoSet[1].encode[videoSet[1].id]);
        //         QImage im=Mat2QImage(cv_ptr->image,videoSet[1].rotate);

        if (leader_qnode_id == 1) {
            QImage im = Mat2QImage(cv_ptr->image, videoSet[0].rotate);
            emit Show_image(0, im.mirrored(videoSet[0].horMir, videoSet[0].verMir));
        } else {
            QImage im = Mat2QImage(cv_ptr->image, videoSet[1].rotate);
            emit Show_image(1, im.mirrored(videoSet[1].horMir, videoSet[1].verMir));
        }

    }

    catch (cv_bridge::Exception& e) {
        log(Error, ("video frame1 exception: " + QString(e.what())).toStdString());
        return;
    }
}
//图像话题的回调函数
void QNode::imageCallback2(const sensor_msgs::ImageConstPtr& msg)
{
    cv_bridge::CvImagePtr cv_ptr;
    try {
        //深拷贝转换为opencv类型
        cv_ptr = cv_bridge::toCvCopy(msg, videoSet[2].encode[videoSet[2].id]);
        //         QImage im=Mat2QImage(cv_ptr->image,videoSet[2].rotate);

        if (leader_qnode_id == 2) {
            QImage im = Mat2QImage(cv_ptr->image, videoSet[0].rotate);
            emit Show_image(0, im.mirrored(videoSet[0].horMir, videoSet[0].verMir));
        } else {
            QImage im = Mat2QImage(cv_ptr->image, videoSet[2].rotate);
            emit Show_image(2, im.mirrored(videoSet[2].horMir, videoSet[2].verMir));
        }

    } catch (cv_bridge::Exception& e) {
        log(Error, ("video frame2 exception: " + QString(e.what())).toStdString());
        return;
    }
}
//图像话题的回调函数
void QNode::imageCallback3(const sensor_msgs::ImageConstPtr& msg)
{
    cv_bridge::CvImagePtr cv_ptr;
    try {
        //深拷贝转换为opencv类型
        cv_ptr = cv_bridge::toCvCopy(msg, videoSet[3].encode[videoSet[3].id]);
        //         QImage im=Mat2QImage(cv_ptr->image,videoSet[3].rotate);

        if (leader_qnode_id == 3) {
            QImage im = Mat2QImage(cv_ptr->image, videoSet[0].rotate);
            emit Show_image(0, im.mirrored(videoSet[0].horMir, videoSet[0].verMir));
        } else {
            QImage im = Mat2QImage(cv_ptr->image, videoSet[3].rotate);
            emit Show_image(3, im.mirrored(videoSet[3].horMir, videoSet[3].verMir));
        }

        //         emit Show_image(3,im.mirrored(videoSet[3].horMir,videoSet[3].verMir));
    } catch (cv_bridge::Exception& e) {
        log(Error, ("video frame3 exception: " + QString(e.what())).toStdString());
        return;
    }
}

//图像话题的回调函数
void QNode::imageCallback4(const sensor_msgs::ImageConstPtr& msg)
{
    cv_bridge::CvImagePtr cv_ptr;
    try {
        //深拷贝转换为opencv类型
        cv_ptr = cv_bridge::toCvCopy(msg, videoSet[0].encode[videoSet[0].id]);
        //         QImage im=Mat2QImage(cv_ptr->image,videoSet[4].rotate);

        if (leader_qnode_id == 4) {
            QImage im = Mat2QImage(cv_ptr->image, videoSet[0].rotate);
            emit Show_image(0, im.mirrored(videoSet[0].horMir, videoSet[0].verMir));
        } else {
            QImage im = Mat2QImage(cv_ptr->image, videoSet[4].rotate);
            emit Show_image(4, im.mirrored(videoSet[4].horMir, videoSet[4].verMir));
        }

        //         emit Show_image(4,im.mirrored(videoSet[4].horMir,videoSet[4].verMir));
    } catch (cv_bridge::Exception& e) {
        log(Error, ("video frame3 exception: " + QString(e.what())).toStdString());
        return;
    }
}

QImage QNode::Mat2QImage(cv::Mat const& img, char rotate_state_)
{
    cv::Mat src = img;

    //  int rotate_state_ = 1;
    switch (rotate_state_) {
    case ROTATE_90: {
        cv::Mat tmp;
        cv::transpose(src, tmp);
        cv::flip(tmp, src, 1);
        break;
    }
    case ROTATE_180: {
        cv::Mat tmp;
        cv::flip(src, tmp, -1);
        src = tmp;
        break;
    }
    case ROTATE_270: {
        cv::Mat tmp;
        cv::transpose(src, tmp);
        cv::flip(tmp, src, 0);
        break;
    }
    default:
        break;
    }

    QImage dest(src.cols, src.rows, QImage::Format_ARGB32);

    const float scale = 255.0;

    if (src.depth() == CV_8U) {
        if (src.channels() == 1) {
            for (int i = 0; i < src.rows; ++i) {
                for (int j = 0; j < src.cols; ++j) {
                    int level = src.at<quint8>(i, j);
                    dest.setPixel(j, i, qRgb(level, level, level));
                }
            }
        } else if (src.channels() == 3) {
            for (int i = 0; i < src.rows; ++i) {
                for (int j = 0; j < src.cols; ++j) {
                    cv::Vec3b bgr = src.at<cv::Vec3b>(i, j);
                    dest.setPixel(j, i, qRgb(bgr[2], bgr[1], bgr[0]));
                }
            }
        }
    } else if (src.depth() == CV_32F) {
        if (src.channels() == 1) {
            for (int i = 0; i < src.rows; ++i) {
                for (int j = 0; j < src.cols; ++j) {
                    int level = scale * src.at<float>(i, j);
                    dest.setPixel(j, i, qRgb(level, level, level));
                }
            }
        } else if (src.channels() == 3) {
            for (int i = 0; i < src.rows; ++i) {
                for (int j = 0; j < src.cols; ++j) {
                    cv::Vec3f bgr = scale * src.at<cv::Vec3f>(i, j);
                    dest.setPixel(j, i, qRgb(bgr[2], bgr[1], bgr[0]));
                }
            }
        }
    }

    return dest;
}

void QNode::log(const LogLevel& level, const std::string& msg)
{
    logging_model.insertRows(logging_model.rowCount(), 1);
    std::stringstream logging_model_msg;
    switch (level) {
    case (Debug): {
        ROS_DEBUG_STREAM(msg);
        logging_model_msg << "[DEBUG] [" << ros::Time::now() << "]: " << msg;
        break;
    }
    case (Info): {
        ROS_INFO_STREAM(msg);
        logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
        break;
    }
    case (Warn): {
        ROS_WARN_STREAM(msg);
        logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
        break;
    }
    case (Error): {
        ROS_ERROR_STREAM(msg);
        logging_model_msg << "[ERROR] [" << ros::Time::now() << "]: " << msg;
        break;
    }
    case (Fatal): {
        ROS_FATAL_STREAM(msg);
        logging_model_msg << "[FATAL] [" << ros::Time::now() << "]: " << msg;
        break;
    }
    }
    QVariant new_row(QString(logging_model_msg.str().c_str()));
    logging_model.setData(logging_model.index(logging_model.rowCount() - 1), new_row);
    Q_EMIT loggingUpdated(); // used to readjust the scrollbar
}

//****************编队消息回调函数*****//
void QNode::formationCallback(const mission_parse::formationwithtaskConstPtr& formation_msg)
{
    formation_task = true;
    formation_goal = formation_msg->goal;
}

void QNode::reconnoitreCallback(const mission_parse::reconnoitrewithtaskConstPtr& reconnoitre_msg)
{
    reconnoitre_task = true;
}

void QNode::reconnoitregoalCallback(const move_base_msgs::MoveBaseActionGoalConstPtr& reconnoitre_goal_msg)
{
    reconnoitre_goal = reconnoitre_goal_msg->goal.target_pose.pose;
    //ROS_INFO("goal x is %f, y is %f, z is %f", reconnoitre_goal.position.x, reconnoitre_goal.position.y, reconnoitre_goal.position.z);
}

//编队消息发布
void QNode::formationPub(char task)
{
    if (task == 1) {
        formation_task_pub.publish(f_msg);
    } else {
        r_msg.header.stamp = ros::Time::now();
        r_msg.header.seq = 0;
        r_msg.header.frame_id = "map";
        reconnoitre_task_pub.publish(r_msg);
    }
    ros::spinOnce();
}

void QNode::rvizGoalCallback(const geometry_msgs::PoseStamped& goal)
{
    f_msg.goal = goal.pose;
    f_msg.header = goal.header;
}

void QNode::carTopCallback(const carTop::carTop& date)
{
    emit power(date.battery_level);
    emit speed_x(date.back_wheel_speed);
    emit speed_y(date.turn_angle);
    emit flag_error(date.error_flag);
    //    qDebug() << "receive car topic" ;
    //    date.error_flag
}

void QNode::roadCallback(const road_recognition_msgs::RoadRecognitionStamped::ConstPtr& msg)
{
    emit getTypeValue(msg->roadrecognition.road_type);
    emit getCurvValue(msg->roadrecognition.road_curvature);
    emit getSlopeValue(msg->roadrecognition.road_slope);
}

void QNode::carPosCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
    emit updateCarPos(msg->pose.pose.position.x, msg->pose.pose.position.y);
}

} // namespace cyrobot_monitor
