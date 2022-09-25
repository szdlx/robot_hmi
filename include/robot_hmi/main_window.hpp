/**
 * @file /include/robot_hmi/main_window.hpp
 *
 * @brief Qt based gui for robot_hmi.
 *
 * @date November 2010
 **/
#ifndef robot_hmi_MAIN_WINDOW_H
#define robot_hmi_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtWidgets/QMainWindow>
#include "ui_main_window.h"
#include "qnode.hpp"
#include "joystick.h"
#include <QImage>
#include <QProcess>
#include <QComboBox>
#include <QQueue>
#include <QSpinBox>
#include "rvizpanel.h"
#include "common.hpp"
#include "purepusuit.h"
#include "QMouseEvent"
#include "ros_launch_manager.hpp"

/*****************************************************************************
** Namespace
*****************************************************************************/

namespace robot_hmi {


/*****************************************************************************
** Interface [MainWindow]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */
class MainWindow : public QMainWindow {
Q_OBJECT

public:
	MainWindow(int argc, char** argv, QWidget *parent = 0);
	~MainWindow();

    void ui_init();
    void connect_init();
	void ReadSettings(); // Load up qt program settings at startup
	void WriteSettings(); // Save qt program settings when closing

	void closeEvent(QCloseEvent *event); // Overloaded function
	void showNoMasterMessage();
    void changeComboex(QComboBox *combox, const QString& messagetype);
//    void selectTopic(const QString& topic);  // save preview
    bool connectMaster(QString master_ip, QString ros_ip, int car);

    template <class T1,class T2>
    T1* set_spinbox(T2 *value);
    void setShadowEffect(QWidget * w);

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent *event) {
        if(event->button() == Qt::LeftButton ) {
            if(isMaximized()) showNormal();
            else showMaximized();
        }
    }
//    void enterEvent(QEvent* event);
//    void leaveEvent(QEvent* event);
//    void testEdge(QMouseEvent *event);  //检测鼠标是否接近窗口边缘

public Q_SLOTS:
	/******************************************
	** Auto-connections (connectSlotsByName())
    *******************************************/

    void connectSuccess(int car); // successful connect ROS master
    void connectFailed(int car); // successful connect ROS master

    /******************************************
    ** Manual connections
    *******************************************/
    void slot_update_dashboard(float,float);    // 更新速度显示
    void slot_update_power(float);          // 更新电池电量
    void slot_set_start_pose();
    void slot_car_connect(int car); // select car
//    void slot_indor_connect();  //
//    void slot_outdor_connect(); //

    void updateImgTopicList();  // refresh img topic list
    void updateMapTopicList();  //
    void onTopicChanged(int index);   // show image
    void onTopicMapChanged(int index);   // show image
    void onTopicLaserChanged(int index);   // show image
    void saveImage();       // s

    void slot_set_param(int index); //
    void road_value_set();   //

    void timerSlot();       // save image timer;
    void startTimer();
    void stopTimer();

    void slot_gps(int posqual, int headingqual, double x, double y, double yaw);
    void set_track_path();
    void local_coor(double x, double y, double yaw);
    void slot_stopTrack();

    state<double> getXYT(state<double> xyt);

private:
	Ui::MainWindowDesign ui;
    QPoint dragPosition;   //鼠标拖动的位置
        enum {nodir,
            top = 0x01,
            bottom = 0x02,
            left = 0x04,
            right = 0x08,
            topLeft = 0x01 | 0x04,
            topRight = 0x01 | 0x08,
            bottomLeft = 0x02 | 0x04,
            bottomRight = 0x02 | 0x08
        } resizeDir; //更改尺寸的方向

    bool is_drag_ = false;  // drag window
    QPoint mouse_start_point_;
    QPoint window_start_point_;

    QNode qnode;
    PurePusuit* track;  // pure pursuit algorithm

//    JoyStick *vel_joy;  //left vel control
    JoyStick *omg_joy;  // right turn control
    QTimer *cmd_time;    // publish cmd
    QPair<float, float> vel;

    ROSLaunchManager* roslaunch_slam=NULL;
    pid_t slam_pid;
    ROSLaunchManager* roslaunch_nav=NULL;
    pid_t nav_pid;
    QProcess *laser_cmd;
    QProcess *slam;
    QProcess *nav;
    QProcess *launch=NULL;   // gmapping launch;
//    RvizMapLidar *rmap;
    RvizPanel   *rpanel;    

    //
    QVector<QWidget *> pathWidgets;    // 记录路径的参数组件
    QSpacerItem* spacer; //
    road_data road;  // 路径
    QVector<QVector<double>> fb;        // 记录直线路径的多个路径段
    int st_state=0;                     // 记录跟踪直线路径的状态，跟踪到哪一段了
    PlotRoad *plot;
    state<double> pos0;   // (x,y,theta) 记录跟踪路径的第一个点作为初始坐标系
    state<double> posr;   // 实时的坐标
    bool isTracking=false;  //
    uint track_state=0;     // 0 start 1 pause
    bool param_fresh=false; // 是否需要刷新数据

    // 轨迹采点
    float sample_interval = 0.1;    // m
    QString savepath;



    QString car0_qRosIp;
    QString car0_qMasterIp;
    QString car1_qRosIp;
    QString car1_qMasterIp;

    QString img_filepath;
    QString map_filepath;

    int connectState = 0; // 0 is not connect, 1 is connect car0, 2 is connect car1;
    int volState = 0;   // 1 is low battery, 2 is enough battery;
    int img_state=0;   // 判断截图是否开始 1 is start, 2 is end
    QVector<QImage> img_vec;   // 批量保存图片
    QTimer *timer;          // record save image timer



    bool fullscreen=false;
    bool fullwindow=false;

    bool indoor=true;   // 默认室内

    bool car_stop=false;
    bool gps_qual=false;
    bool imu_qual=false;

    bool gpstest=false;
};

}  // namespace robot_hmi


#endif // robot_hmi_MAIN_WINDOW_H
