/**
 * @file /include/cyrobot_monitor/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef cyrobot_monitor_QNODE_HPP_
#define cyrobot_monitor_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

// To workaround boost/qt4 problems that won't be bugfixed. Refer to
//    https://bugreports.qt.io/browse/QTBUG-22829
#ifndef Q_MOC_RUN
#include <ros/ros.h>
#endif

#include "ackermann_msgs/AckermannDrive.h"
#include "ackermann_msgs/AckermannDriveStamped.h"
#include <QAbstractItemModel>
#include <QLabel>
#include <QStringListModel>
#include <QThread>
#include <cv_bridge/cv_bridge.h> //cv_bridge
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/Twist.h>
#include <image_transport/image_transport.h> //image_transport
#include <nav_msgs/Odometry.h>
#include <road_recognition_msgs/RoadRecognitionStamped.h>
#include <sensor_msgs/image_encodings.h> //图像编码格式
#include <std_msgs/Float32.h>
#include <std_msgs/Float64.h>
#include <string>
//#include <rqt_image_view/image_view.h>

#include <QImage>
#include <QLabel>
#include <QSettings>
#include <map>

#include <QVector>

//编队消息
#include "carTop.h"
#include "formationwithtask.h"
#include "reconnoitrewithtask.h"
#include <move_base_msgs/MoveBaseAction.h>

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace cyrobot_monitor {

extern mission_parse::formationwithtask f_msg;
extern mission_parse::reconnoitrewithtask r_msg;

#define CARNUM 5 //5

#define ROTATE_0 0
#define ROTATE_90 1
#define ROTATE_180 2
#define ROTATE_270 3

/*****************************************************************************
** Class
*****************************************************************************/

class QNode : public QThread {
    Q_OBJECT
public:
    QNode(int argc, char** argv);
    virtual ~QNode();
    bool init();
    bool init(const std::string& master_url, const std::string& host_url);
    void rosinit();

    void disinit();
    void move_base(char k, float speed_linear, float speed_trun, int curCar);
    void ackerman_control(float speed_linear, float turn_angle, int curCar); //阿克曼车辆控制
    void set_goal(QString frame, double x, double y, double z, double w);
    void Sub_Image(QString topic, int frame_id);
    void Sub_Image(QString topic, int frame_id, int leader_id);

    QMap<QString, QString> get_topic_list();
    void run();
    bool isWork = false;

    //编队话题发布
    void formationPub(char task);

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

    //视频编码
    struct video_encode {
        std::string BGR8 = sensor_msgs::image_encodings::BGR8;
        std::string RGB8 = sensor_msgs::image_encodings::RGB8;
        std::string BGR16 = sensor_msgs::image_encodings::BGR16;
        std::string BGRA8 = sensor_msgs::image_encodings::BGRA8;
        std::string MONO8 = sensor_msgs::image_encodings::MONO8;
        std::string RGB16 = sensor_msgs::image_encodings::RGB16;
        std::string RGBA8 = sensor_msgs::image_encodings::RGBA8;
        std::string BGRA16 = sensor_msgs::image_encodings::BGRA16;
        std::string MONO16 = sensor_msgs::image_encodings::MONO16;
        std::string RGBA16 = sensor_msgs::image_encodings::RGBA16;
    }; //视频的编码形式

    //图像相关设置
    struct VideoSetting {
        bool horMir = false;
        bool verMir = false;
        std::string encode[10] = {
            sensor_msgs::image_encodings::BGR8,
            sensor_msgs::image_encodings::RGB8,
            sensor_msgs::image_encodings::BGR16,
            sensor_msgs::image_encodings::BGRA8,
            sensor_msgs::image_encodings::MONO8,
            sensor_msgs::image_encodings::RGB16,
            sensor_msgs::image_encodings::RGBA8,
            sensor_msgs::image_encodings::BGRA16,
            sensor_msgs::image_encodings::MONO16,
            sensor_msgs::image_encodings::RGBA16
        };
        char id = 0;
        char rotate = ROTATE_0;
    } videoSet[CARNUM];

    //    vecor<VideoSetting>

    QStringListModel* loggingModel() { return &logging_model; }
    void log(const LogLevel& level, const std::string& msg);

Q_SIGNALS:
    void loggingUpdated();
    void rosShutdown();

    void speed_x(double x);
    void speed_y(double y);
    void power(float p);
    void Master_shutdown();
    void flag_error(char flag);

    void Show_image(int, QImage);
    void position(QString frame, double x, double y, double z, double w);

    //道路信息信号
    void getTypeValue(int road_type);
    void getCurvValue(double road_curvature);
    void getSlopeValue(double road_slope);
    void updateCarPos(double x, double y);

private:
    int init_argc;
    char** init_argv;

    //    ros::Publisher chatter_publisher;

    ros::Subscriber road_sub; //添加道路信息订阅 TODO
    ros::Subscriber carpos_sub;

    ros::Subscriber cmdVel_sub[5];
    ros::Subscriber chatter_subscriber;
    ros::Subscriber pos_sub;
    ros::Subscriber power_sub;
    ros::Subscriber CarTop_sub; //猛犸车自定义消息类型订阅
    ros::Publisher carVel_pub;

    ros::Publisher goal_pub;
    ros::Publisher cmd_pub_twist[5];
    ros::Publisher cmd_pub_ackermann[5];
    //
    ros::Publisher mission_goal_pub;
    //编队
    ros::Subscriber formation_task_sub;
    ros::Subscriber reconnoitre_task_sub;
    ros::Subscriber reconnoitre_goal_sub;
    //ros::Subscriber rviz_goal_sub;
    //
    ros::Publisher formation_task_pub;
    ros::Publisher reconnoitre_task_pub;
    ros::Publisher reconnoitre_goal_pub;

    QStringListModel logging_model;
    //图像订阅

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    image_transport::Subscriber image_sub[5];
    int temp_id;
    int leader_qnode_id;
    QVector<int> image_id;

    image_transport::Subscriber image_sub0;
    image_transport::Subscriber image_sub1;
    image_transport::Subscriber image_sub2;
    image_transport::Subscriber image_sub3;
    image_transport::Subscriber image_sub4;
    //图像format
    QString video0_format;
    QString video1_format;
    QString video2_format;
    QString video3_format;
    QString video4_format;

    QString odom_topic[5];
    QString vel_topic[5];
    int msgtype[5];

    QString power_topic;
    QString pose_topic;
    QString power_max;
    QString power_min;

    cv::Mat conversion_mat_;

    QImage Mat2QImage(cv::Mat const& src, char rotate_state_);
    void poseCallback(const geometry_msgs::PoseWithCovarianceStamped& pos);
    void rvizGoalCallback(const geometry_msgs::PoseStamped& goal);
    void carTopCallback(const carTop::carTop& date);
    void roadCallback(const road_recognition_msgs::RoadRecognitionStamped::ConstPtr& msg);
    void carPosCallback(const nav_msgs::Odometry::ConstPtr& msg);

    void speedCallback(const geometry_msgs::Twist::ConstPtr& msg);
    void speedCallback0(const geometry_msgs::Twist::ConstPtr& msg);
    void speedCallback1(const geometry_msgs::Twist::ConstPtr& msg);
    void speedCallback2(const geometry_msgs::Twist::ConstPtr& msg);
    void speedCallback3(const geometry_msgs::Twist::ConstPtr& msg);
    void speedCallback4(const geometry_msgs::Twist::ConstPtr& msg);
    void ackerman_speed(const ackermann_msgs::AckermannDriveStamped::ConstPtr& msg);

    void powerCallback(const std_msgs::Float32& message_holder);

    //``````````````````````````````````````````````````````````````
    void imageCallback(const sensor_msgs::ImageConstPtr& msg, int& frame_id);

    void imageCallback0(const sensor_msgs::ImageConstPtr& msg);
    void imageCallback1(const sensor_msgs::ImageConstPtr& msg);
    void imageCallback2(const sensor_msgs::ImageConstPtr& msg);
    void imageCallback3(const sensor_msgs::ImageConstPtr& msg);
    void imageCallback4(const sensor_msgs::ImageConstPtr& msg);
    void myCallback(const std_msgs::Float64& message_holder);
    void callbackImage(const sensor_msgs::Image::ConstPtr& msg);

    //编队消息
    bool formation_task = false;
    bool reconnoitre_task = true;
    geometry_msgs::Pose formation_goal;
    geometry_msgs::Pose reconnoitre_goal;
    void formationCallback(const mission_parse::formationwithtaskConstPtr& formation_msg);
    void reconnoitreCallback(const mission_parse::reconnoitrewithtaskConstPtr& reconnoitre_msg);
    void reconnoitregoalCallback(const move_base_msgs::MoveBaseActionGoalConstPtr& reconnoitre_goal_msg);
};

} // namespace cyrobot_monitor

#endif /* cyrobot_monitor_QNODE_HPP_ */
