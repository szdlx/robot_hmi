/**
 * @file /include/robot_hmi/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef robot_hmi_QNODE_HPP_
#define robot_hmi_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

// To workaround boost/qt4 problems that won't be bugfixed. Refer to
//    https://bugreports.qt.io/browse/QTBUG-22829
#ifndef Q_MOC_RUN
#include <ros/ros.h>
#endif
#include <string>
#include <QThread>
#include <QStringListModel>
#include <QImage>
#include <QProcess>
#include <pthread.h>
#include <QMap>

#include <std_msgs/String.h>
#include <map>

#include <nav_msgs/Odometry.h>
#include <nav_msgs/OccupancyGrid.h>
#include <sensor_msgs/LaserScan.h>
#include <std_msgs/Float32.h>
//#include <gmapping/slam_gmapping.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/PoseStamped.h>
#include <visualization_msgs/Marker.h>

#include <actionlib/server/simple_action_server.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib_msgs/GoalStatusArray.h>


#include "four1.h"
#include "GPS_ksxt.h"   //GPS ksxt报文 自定义消息
#include "com.h"        // 控制升降机消息类型
#include "robot.h"      // 界面控制机器人建图与导航的消息

//

#include "action_pure/purePursuitAction.h"
typedef actionlib::SimpleActionClient<action_pure::purePursuitAction> PureClient;


/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace robot_hmi {

/*****************************************************************************
** Class
*****************************************************************************/

#define TWIST 0
#define ACKERMANN 1
#define TWIST_STAMPED 2   //
#define ACKERMANN_STAMPED 3

class QNode : public QThread {
    Q_OBJECT
public:
	QNode(int argc, char** argv );
	virtual ~QNode();
    bool init(int car);
    bool init(const std::string &master_url, const std::string &host_url, int car);
    void disinit();
    void init_set();
    bool getTopicTypes(ros::master::V_TopicInfo& topics);   // 获取所有话题
    void updateTopics();    // 更新所有相关话题列表

    QList<QString> getTopics(const QString& message_types);    //La
    QSet<QString> getTopics(const QSet<QString>& message_types,
                                   const QSet<QString>& message_sub_types, const QList<QString>& transports);
    void set_cmd_vel(float linear,float angular);   // send vel topic
    void set_cmd_topic(const QString& topic);   // set vel topic
    void sub_image(QString topic_name);
    void control_elevator(int hight, bool sw);  //升降机高度与温度开关
    void set_goal(double x,double y,double z);
    void roslaunch(bool checked);
	void run();
	/*********************
	** Logging
	**********************/
	enum LogLevel {
	         Debug,
	         Info,
	         Warn,
	         Error,
	         Fatal
	 };

	QStringListModel* loggingModel() { return &logging_model; }
	void log( const LogLevel &level, const std::string &msg);
    QList<QString> getImgTopiclist();   //

    void publish_vel(QString vel_topic);
    void robot_control(QPair<int,int> rbt);
    void exe_robot(QString type, QVector<QString> rbt);

    void sendTrackPath(std::vector<std::vector<double>> path);

Q_SIGNALS:
	void loggingUpdated();
    void rosShutdown();
    void speed_vel(float vel,float angv);
    void power_vel(float);
    void position(double x,double y,double z);
    void pose2D(double x, double y, double yaw);
    void showMarker(QString topic, int car);
    void connectMasterSuccess(int car);
    void connectMasterFailed(int car);
    void gps_pos(int posqual, int headingqual, double x, double y, double heading);
    void obs_meet(float dis,int car);
    void vel_list_changed();

public slots:
    void cmd_output(int car);
    void cmd_error_output(int car);

private:

    // ROSLaunchManager* roslaunch_slam=NULL;
    // pid_t slam_pid=-1;
    // ROSLaunchManager* roslaunch_nav=NULL;
    // pid_t nav_pid=-1;

    std::map<QString, ros::Publisher> pub_list;

    // std::shared_ptr<QProcess> karto_; //
    // std::shared_ptr<QProcess> nav_;   //

	int init_argc;
    char** init_argv;

    ros::Publisher cmd_vel_pub;
    ros::Publisher goal_pub[2];
    ros::Publisher marker_pub[2];
    ros::Publisher motor_pub[2];        // 控制升降机
    ros::Publisher vel_pub;    // vel
    ros::Publisher robot_pub;   // slam & navigation

    QStringListModel logging_model;
    ros::Subscriber odom_sub[2];
    ros::Subscriber power_sub[2];
    ros::Subscriber gps_sub[2];
    ros::Subscriber laser_sub[2];
    ros::Subscriber mbstate;    // get move base state

    robot_msg::robot rsnav;     // slam &  navigation
    unsigned short int status;                 // move base state

    void power_callback(const ros_four1_msg::four1ConstPtr &msg, int car);
    void odom_callback(const nav_msgs::Odometry::ConstPtr &msg, int car);
    void gps_callback(const gps_ksxt_msg::GPS_ksxtConstPtr &msg, int car);
    void laser_callback(const sensor_msgs::LaserScanConstPtr &msg, int car);
    void map_pose(const geometry_msgs::Pose::ConstPtr &msg, int car);
    void actionCallback(const actionlib_msgs::GoalStatusArrayConstPtr &goalstates);

    pthread_t pth;
    PureClient *pure_client;
    void actionThread();    //

    QString vel_topic;

public:
    bool initFlag=false;    // 判断是否连接ros master成功
    bool meetObs=false;
    uint car=0;     //
    int car0=0, car1=1;
    QVector<std::string> pathList;
    QVector<std::string> mapList;
    QVector<std::string> polyList;
    QMap<std::string, std::string> vel_list;   // 速度类型消息

    float vmax[2], angmax[2];
    uint vel_topic_type = TWIST;

};

}  // namespace robot_hmi

#endif /* robot_hmi_QNODE_HPP_ */
