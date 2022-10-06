/**
 * @file /src/main_window.cpp
 *
 * @brief Implementation for the qt gui.
 *
 * @date 2022.08
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui>
#include <QtGlobal>
#include <QMessageBox>
#include <QNetworkInterface>
#include <QHostAddress>
#include <QFileDialog>
#include <QtDebug>
#include <QGraphicsDropShadowEffect>
#include <iostream>

#include <Eigen/Eigen>

#include <QtConcurrent/QtConcurrent>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include "../include/robot_hmi/main_window.hpp"
#include "messagetips.h"

#include "SwitchButton.h"




/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace robot_hmi {

using namespace Qt;

/*****************************************************************************
** Implementation [MainWindow]
*****************************************************************************/

MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
	: QMainWindow(parent)
	, qnode(argc,argv)
{
	ui.setupUi(this); // Calling this incidentally connects all ui's triggers to on_...() callbacks in this class.
    ui_init();

//#ifdef 1
//    获取rosmaster ip 和rosip ip
     foreach (QHostAddress address, QNetworkInterface::allAddresses()) { //
       if (address.protocol() == QAbstractSocket::IPv4Protocol) {
         QString addre = address.toString();
         if (addre.split(".")[0] == "192") {
           car0_qRosIp = addre;
//           car0_qMasterIp = "http://" + addre + ":11311";
         } else if (addre.split(".")[0] == "10") {
           car0_qRosIp = addre;
//           car0_qMasterIp = "http://" + addre + ":11311";
         } else if (addre.split(".")[0] == "172") {
           car0_qRosIp = addre;
//           car0_qMasterIp = "http://" + addre + ":11311";
         }
       }
     }
    car0_qMasterIp = "http://" + car0_qRosIp + ":11311";   // 主机地址本机

     connect(ui.rosmasteruri, &QLineEdit::editingFinished,[this]{
         car0_qMasterIp=ui.rosmasteruri->text();
     });

    ReadSettings();
    ui.rosmasteruri->setText(car0_qMasterIp);

    track = new PurePusuit();   //

    connect_init(); // initial connect


}

void MainWindow::ui_init(){

    resizeDir = nodir;   //初始化检测方向为无
    setWindowFlags(Qt::FramelessWindowHint);  //设置无边框
    setMouseTracking(true); //开启鼠标追踪
    setMinimumSize(200, 200);

//    setShadowEffect(ui.param_widget);
//        setShadowEffect(ui.info_widget);
    setShadowEffect(ui.state_widget);   // 设置阴影
    setShadowEffect(ui.widget_plat);
//        setShadowEffect(ui.widget_view);
    setShadowEffect(ui.widget_plot);
//        setShadowEffect(ui.rviz_widget);
    setShadowEffect(ui.map_widget);
//    setShadowEffect(ui.rviz_img);
    setShadowEffect(ui.panel_widget);
//    setShadowEffect(ui.rviz_panel);
    setShadowEffect(ui.widget_4);

//    QFile qss("://images/qss/whiteBackground.qss");  //Ubuntu.qss
    QFile qss(":/qdarkstyle/light/lightstyle.qss"); // qss 设置界面皮肤
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();

    qApp->setFont(QFont("Microsoft YaHei"));

    // 摇杆控制初始化
//    vel_joy = new JoyStick(ui.velControl);
    omg_joy = new JoyStick(ui.omgControl);
//    setShadowEffect(vel_joy);
    setShadowEffect(omg_joy);
//    vel_joy->show();
    omg_joy->show();

    spacer = ui.space_path; // 弹簧
    rpanel = ui.rviz_panel; // rviz panel
    plot = ui.plot_road;

    ui.horizontalWidget->setStyleSheet(".QWidget{background-color:#cdcdcd;border-radius:3px;}");
    ui.info_widget->setStyleSheet(".QWidget{background-color:#ededed;border-radius:3px;}");

    ui.indoor->setChecked(false);
    ui.outdoor->setStyleSheet("color:black;");
    ui.indoor->setStyleSheet("color:blue;");

    ui.map_switch->setBgColorOff(QColor("#092e64"));
    ui.map_switch->setTextOff("建图");
    ui.map_switch->setTextOn("导航");
    bool ischecked = ui.map_switch->checked();
    ui.set_goal->setVisible(ischecked);
    ui.set_start->setVisible(ischecked);
    ui.save_map->setVisible(!ischecked);
    ui.gmapping_btn->setVisible(!ischecked);

//    ui.widget_5->setVisible(false);

}

bool showtips=false;
void MainWindow::connect_init(){
//    QObject::connect(ui.actionAbout_Qt, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt())); // qApp is a global variable for the application
//    QObject::connect(ui.image_file, &QAction::triggered,this, [this]{
//        QString existPath= img_filepath;//==""?"":img_filepath;
//        img_filepath = QFileDialog::getExistingDirectory(this,tr("截图保存路径"),existPath);
//    });     // set where to save image
    connect(ui.img_path, &QPushButton::clicked, this,[this]{
        QString existPath= img_filepath;//==""?"":img_filepath;
        img_filepath = QFileDialog::getExistingDirectory(this,tr("截图保存路径"),existPath);
    });
    connect(ui.map_path, &QPushButton::clicked, this, [this]{
        QString existPath= map_filepath;//==""?"":img_filepath;
        map_filepath = QFileDialog::getExistingDirectory(this,tr("slam建图保存路径"),existPath);
    });


    connect(ui.car0_connect, &MyPushButton::doubleClicked,this, [this]{slot_car_connect(1);});
    connect(ui.car1_connect, &MyPushButton::doubleClicked,this, [this]{slot_car_connect(2);});
    connect(ui.indoor, &MyPushButton::doubleClicked,this, [this]{
        indoor=true;
        ui.indoor->setChecked(false);
        ui.outdoor->setStyleSheet("color:black;");
        ui.indoor->setStyleSheet("color:blue;");
    });
    connect(ui.outdoor, &MyPushButton::doubleClicked,this,[this]{
        indoor = false;
        ui.outdoor->setChecked(false);
        ui.indoor->setStyleSheet("color:black;");
        ui.outdoor->setStyleSheet("color:blue;");
    });

    // 速度控制
    connect(omg_joy, &JoyStick::keyControl, this, [this](float v, float ang){
        vel={v*qnode.vmax[qnode.car],ang*qnode.angmax[qnode.car]};
    });
    connect(ui.topics_vel, QOverload<int>::of(&QComboBox::currentIndexChanged), this,[this]{
        if(!qnode.initFlag) return;

    });
    cmd_time = new QTimer(this);
    cmd_time->start(50);    // 控制周期为50 ms
    connect(cmd_time,&QTimer::timeout, this, &MainWindow::set_track_path);

    connect(ui.refresh, SIGNAL(clicked(bool)), this, SLOT(updateImgTopicList()));
    connect(ui.refresh_map,&QPushButton::clicked, this, &MainWindow::updateMapTopicList);
    connect(ui.topics_map, SIGNAL(currentIndexChanged(int)), this, SLOT(onTopicMapChanged(int)) );
    connect(ui.topics_laser, SIGNAL(currentIndexChanged(int)), this, SLOT(onTopicLaserChanged(int)) );
    connect(ui.topics_img, SIGNAL(currentIndexChanged(int)), this, SLOT(onTopicChanged(int)));
    connect(ui.snapshoot, SIGNAL(pressed()), this, SLOT(saveImage()));  // save image
    connect(ui.set_goal, &QPushButton::pressed,this, [this]{
        if(!qnode.initFlag) return;
        rpanel->Set_Goal_Pose();
    });
    connect(ui.set_start, &QPushButton::pressed, this,[this]{
        if(!qnode.initFlag) return ;
        rpanel->Set_Start_Pose();
    });

    connect(ui.gmapping_btn, &QPushButton::clicked, this, [this]{  //
        if(!qnode.initFlag) return;
        qnode.roslaunch(0);
        updateMapTopicList();
    });
    connect(ui.save_map, &QPushButton::clicked, this, [this]{
        if(!qnode.initFlag) return ;
        QDateTime datetime;
        QString timestr=datetime.currentDateTime().toString("yyyy-MM-dd-HH-mm-ss");
        QDir dir;
        if (map_filepath.isEmpty())
        {
          map_filepath=dir.currentPath();
        }
        auto filepath = QString(map_filepath+"/"+timestr);
        // 检查目录是否存在，若不存在则新建

        if (!dir.exists(filepath))
        {
            bool res = dir.mkpath(filepath);
           // qDebug() << "新建目录成功" << res;
        }
        // 智能指针，独立指针
        std::unique_ptr<QProcess> save = std::unique_ptr<QProcess>(new QProcess);
        save->start("rosrun",{"map_server","map_saver","-f",filepath+"/map"});
        save->waitForFinished();
        std::unique_ptr<MessageTips> mMessageTips =
                std::unique_ptr<MessageTips>(
                    new MessageTips(
                    "slam建图保存在路径:"+filepath //+"\n在菜单中设置保存路径"
                    ,this)
                    );
        mMessageTips->setStyleSheet("border-radius:5px;text-align:center;background: rgb(211, 215, 207); border: none;");
        mMessageTips->show();
    });



    //connect ros node
    connect(&qnode, SIGNAL(connectMasterSuccess(int)), this, SLOT(connectSuccess(int)));
    connect(&qnode, SIGNAL(connectMasterFailed(int)), this, SLOT(connectFailed(int)));
    connect(&qnode, SIGNAL(power_vel(float)),this,SLOT(slot_update_power(float)));
    connect(&qnode, &QNode::gps_pos, this, &MainWindow::slot_gps);
    connect(&qnode, &QNode::position, this, &MainWindow::local_coor);
    connect(&qnode, &QNode::speed_vel, this, &MainWindow::slot_update_dashboard);
    connect(&qnode, &QNode::obs_meet, this, [=](float dis){
        if(track_state==1){
            if(isTracking){
                ui.track_path->setText("继续跟踪");
                ui.track_path->setChecked(false);
                ui.track_path->setStyleSheet("color:black;");
                isTracking=false;                
            }
        }
        if(showtips==0){
            MessageTips *mMessageTips = new MessageTips(
                        "前方"+QString::number(dis*100,'f',1)+"cm遇到障碍物，请注意安全",this);
            mMessageTips->setStyleSheet("color:red;");
            mMessageTips->setCloseTimeSpeed();
            connect(mMessageTips,&MessageTips::close,[]{
                showtips=0;
            });
            mMessageTips->show();
        }
        else showtips=true;
    });

    slot_set_param(road.type);
    ui.selected_path->setCurrentIndex(road.type);   //
    connect(ui.selected_path, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int index){
        isTracking=false;
        st_state=0;
        slot_set_param(index);
    });
    connect(ui.stop_track, &QPushButton::clicked, this,&MainWindow::slot_stopTrack );
    connect(ui.track_path, &QPushButton::clicked,this, [this]{  // lambda function
        if(!qnode.initFlag || !gps_qual&&!indoor || !imu_qual&&indoor) return;
        if(!track_state){
            track_state++;
            plot->clearPath();
            ui.track_path->setText("暂停跟踪");
            ui.track_path->setChecked(true);
            ui.track_path->setStyleSheet("color:blue;");
            pos0=posr; isTracking = true;
            plot->plotCar(0,0,0);
//            qDebug() << QString("pos0: %1,%1,%1").arg(pos0.x).arg(pos0.y).arg(pos0.t);
        }
        else if(track_state==1){
            if(!isTracking){
                ui.track_path->setText("暂停跟踪");
                ui.track_path->setChecked(true);
                ui.track_path->setStyleSheet("color:blue;");
                isTracking=true;
            } else {
                ui.track_path->setText("继续跟踪");
                ui.track_path->setChecked(false);
                ui.track_path->setStyleSheet("color:black;");
                isTracking=false;
            }
        }
    });
    connect(track,&PurePusuit::track_finish, this, [this]{
        isTracking=false;
        st_state=0;
        track_state=0;
        ui.track_path->setText("开始跟踪");
        ui.track_path->setChecked(false);
        ui.track_path->setStyleSheet("color:black;");
    });


    timer = new QTimer(this);   // image timer
    connect(timer, SIGNAL(timeout()), this, SLOT(timerSlot()));

    connect(ui.screen_btn, &QPushButton::pressed, [this]{
        ui.widget_plot->setVisible(fullscreen);
        ui.verticalWidget_2->setVisible(fullscreen);
        ui.gridWidget->setVisible(fullscreen);
        fullscreen=!fullscreen;
        if(fullscreen){
            ui.screen_btn->setText("缩小");
            ui.screen_btn->setIcon(QIcon(QString::fromLocal8Bit("://images/narrow.png")));
        }
        else{
            ui.screen_btn->setText("放大");
            ui.screen_btn->setIcon(QIcon(QString::fromLocal8Bit("://images/fullscren.png")));
        }
    });

    //升降机高度
    connect(ui.left_motor, &QSlider::valueChanged, [this](int val){
        if(!qnode.initFlag){
            ui.left_motor->setValue(0);
            return;
        }
        qnode.control_elevator(val, ui.tmp_switch->checked());
        ui.elevator_hight->setText("高度 "+QString::number(val)+"mm");
//        ui.left_motor->setValue()
        //  qDebug()<< QString("升降机高度:") << val << endl;
    });
    // 温度开关
    connect(ui.tmp_switch, &SwitchButton::statusChanged, [this](bool status){
        if(!qnode.initFlag)return;
        qnode.control_elevator(ui.left_motor->value(), ui.tmp_switch->checked());
    });
    connect(ui.evelator_up, &QPushButton::clicked, [this]{ui.left_motor->setValue(fmin(500,ui.left_motor->value()+10));});
    connect(ui.evelator_down, &QPushButton::clicked, [this]{ui.left_motor->setValue(fmax(0,ui.left_motor->value()-10));});

    connect(ui.ang_slide, &QSlider::valueChanged, [this](int val){
        if(!qnode.initFlag){
            ui.ang_slide->setValue(0);
            return;
        }
        ui.ang_val->setText(QString::number(val/100.0,'f',3)+"rad/s");
        qnode.angmax[qnode.car] =  ui.ang_slide->value()/100.0;
    });
    connect(ui.ang_up, &QPushButton::clicked, [this]{
        ui.ang_slide->setValue(fmin(100,ui.ang_slide->value()+10));});
    connect(ui.ang_down, &QPushButton::clicked, [this]{
        ui.ang_slide->setValue(fmax(0,ui.ang_slide->value()-10));});

    connect(ui.vel_slider, &QSlider::valueChanged, [this](int val){
        if(!qnode.initFlag){
            ui.vel_slider->setValue(0);
            return;
        }
        ui.vel_val->setText(QString::number(val/100.0,'f',3)+"cm/s");
        qnode.vmax[qnode.car] =  ui.vel_slider->value()/100.0;
    });
    connect(ui.vel_add, &QPushButton::clicked, [this]{
        ui.vel_slider->setValue(fmin(100,ui.vel_slider->value()+10));});
    connect(ui.vel_down, &QPushButton::clicked, [this]{
        ui.vel_slider->setValue(fmax(0,ui.vel_slider->value()-10));});

    // 窗口处理
    connect(ui.shutdown, &QPushButton::clicked, [this]{close();});  // close window
    connect(ui.screen, &QPushButton::clicked,[this]{    //
        if(isMaximized()){
            showNormal();
            ui.screen->setIcon(QIcon(QString::fromLocal8Bit("://images/zoom.png")));
        }
        else{
            ui.screen->setIcon(QIcon(QString::fromLocal8Bit("://images/minscreen.png")));
            showMaximized();    // 全屏
        }
    });
    connect(ui.minumize, &QPushButton::clicked,[this]{showMinimized();});   // 最小化

    connect(ui.pushButton,&QPushButton::clicked, [this]{
        gpstest=1;
        pos0 = posr;
    });

    ui.rosmasteruri->setEnabled(!(ui.local_ip->isChecked()));
    connect(ui.local_ip, &QCheckBox::clicked,[this]{
        ui.rosmasteruri->setEnabled(!(ui.local_ip->isChecked()));});

    /*** test ****/
    launch = new QProcess(this);
    connect(ui.pushButton_3, &QPushButton::clicked, [this]{
        launch->setProgram("rosrun");   //输入可执行程序
        launch->setArguments({"rqt_tf_tree","rqt_tf_tree"});    // 输入参数
        launch->start();    // 执行程序
    });
    connect(ui.pushButton_5, &QPushButton::clicked, [this]{
        launch->kill(); //

    });

    connect(ui.map_switch, &SwitchButton::statusChanged, [this]{
        bool ischecked = ui.map_switch->checked();
        ui.set_goal->setVisible(ischecked);
        ui.set_start->setVisible(ischecked);
        ui.save_map->setVisible(!ischecked);
        ui.gmapping_btn->setVisible(!ischecked);
        if(!qnode.initFlag) return ;
        qnode.roslaunch(ischecked);
        updateMapTopicList();
    });
}

void MainWindow::slot_stopTrack(){
    if(!qnode.initFlag) return;
    track_state=0;isTracking=false;
    ui.track_path->setText("开始跟踪");
    ui.track_path->setChecked(false);
    ui.track_path->setStyleSheet("color:black;");
    plot->clearPath();
    st_state=0;plot->plotCar(0,0,0);
    track->reset();
}

void MainWindow::slot_gps(int posqual, int headingqual, double x, double y, double yaw){

    QString text[]={"定位不可用","单点定位","RTK 浮点解","RTK 固定解"};
    ui.posqual->setText(text[posqual]);
    ui.headingqual->setText(text[headingqual]);
    ui.gps_east->setText("东: "+QString::number(x,'f',2)+"m ");
    ui.gps_north->setText("北: " + QString::number(y,'f',2)+"m ");
    ui.gps_heading->setText("朝向: "+QString::number(yaw,'f',2)+"° ");
    if(posqual==0||headingqual==0){
        gps_qual = false;
        ui.gps_east->setStyleSheet("color:red");
        ui.gps_north->setStyleSheet("color:red");
        ui.gps_heading->setStyleSheet("color:red");
    } else {
        gps_qual=true;
        ui.gps_east->setStyleSheet("color:black");
        ui.gps_north->setStyleSheet("color:black");
        ui.gps_heading->setStyleSheet("color:black");
    }

    if(!indoor){    //南方向为0度方位角，顺时针为正
        yaw += 90;
        if(yaw>360)    // 改为东方向为x轴
            yaw=yaw-360;
        if(yaw>180){
            yaw = 360-yaw;
        } else
            yaw = -yaw;
        posr={x, y, yaw*M_PI/180.0}; // 要保存逆时针旋转为正
        qDebug() << QString("outdoor p: %1,%2,%3").arg(x).arg(y).arg(yaw);
    }
    auto p = getXYT(posr);
    char str[100];
    sprintf(str, "gps x:%0.3lf, y:%0.3lf, yaw:%0.3lf", p.x, p.y, p.t*180/M_PI);
    ui.label_3->setText(str);
//    qDebug()<<QString("tmpxyt:%1,%2,%3").arg(p.x).arg(p.y).arg(p.t);

}

/**
 * @brief 利用定时器，将图片消息类型转换为QImage
 */
void MainWindow::timerSlot(){

    cv_bridge::CvImagePtr cv_ptr;
    auto msg = ui.rviz_img->getImage();
    if( msg == NULL) {
        //qDebug() << "img NULL!" << endl;
        return;
    }
    cv::Mat img;
    try {
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
        img = cv_ptr->image;

    } catch (cv_bridge::Exception& e) {
        ROS_ERROR("Could not convert from '%s' to '32fc1'.", msg->encoding.c_str());
        return;
    }
    QImage dest(img.cols, img.rows, QImage::Format_ARGB32);
    const float scale = 255.0;

    if (img.depth() == CV_8U) {
      if (img.channels() == 1) {
          for (int i = 0; i < img.rows; ++i) {
              for (int j = 0; j < img.cols; ++j) {
                  int level = img.at<quint8>(i, j);
                  dest.setPixel(j, i, qRgb(level, level, level));
              }
          }
      } else if (img.channels() == 3) {
          for (int i = 0; i < img.rows; ++i) {
              for (int j = 0; j < img.cols; ++j) {
                  cv::Vec3b bgr = img.at<cv::Vec3b>(i, j);
                  dest.setPixel(j, i, qRgb(bgr[2], bgr[1], bgr[0]));
              }
          }
      }
    } else if (img.depth() == CV_32F) {
      if (img.channels() == 1) {
          for (int i = 0; i < img.rows; ++i) {
              for (int j = 0; j < img.cols; ++j) {
                  int level = scale * img.at<float>(i, j);
                  dest.setPixel(j, i, qRgb(level, level, level));
              }
          }
      } else if (img.channels() == 3) {
          for (int i = 0; i < img.rows; ++i) {
              for (int j = 0; j < img.cols; ++j) {
                  cv::Vec3f bgr = scale * img.at<cv::Vec3f>(i, j);
                  dest.setPixel(j, i, qRgb(bgr[2], bgr[1], bgr[0]));
              }
          }
      }
    }
    img_vec.push_back(dest);
    //qDebug() << "save img by timer,state:" << img_state << "img number:" << img_vec.size() << "\n";
}

void MainWindow::startTimer(){
    //qDebug()<<"start timer" << endl;
    if(!timer->isActive())
        timer->start(500);  // timer interval
    img_vec.clear();    //
    ui.snapshoot->setText("停止截图");
    ui.snapshoot->setIcon(QIcon(QString::fromLocal8Bit("://images/end.png")));
}

void MainWindow::stopTimer(){
   // qDebug()<<"stop timer" << endl;
    ui.snapshoot->setText("开始截图");
    ui.snapshoot->setIcon(QIcon(QString::fromLocal8Bit("://images/start.png")));
    if(img_state == 2){
        if(timer->isActive())
            timer->stop();
        QString filepath;
        auto runFunc = [&](){
            QDateTime datetime;
            QString timestr=datetime.currentDateTime().toString("yyyy-MM-dd-HH-mm-ss");
            QDir dir;
            if (img_filepath.isEmpty())
            {
              img_filepath=dir.currentPath();
            }
            filepath = QString(img_filepath+"/"+timestr);
            // 检查目录是否存在，若不存在则新建

            if (!dir.exists(filepath))
            {
                bool res = dir.mkpath(filepath);
               // qDebug() << "新建目录成功" << res;
            }
            int cnt=0;
            //qDebug()<< "img number:" <<img_vec.size() << endl;
            for(QImage dest:img_vec){
                dest.save(filepath+"/"+QString::number(cnt)+"."+ui.select_format->currentText().toLower());
                cnt++;
            }
            //qDebug()<< "save images success" << endl;
            // auto p=watcher.future.result();// 获取返回值，因为这里是void，所以没有返回值
            MessageTips *mMessageTips = new MessageTips(
                        "图片保存在路径:"+filepath //+"\n在菜单中设置保存路径"
                        ,this);
            mMessageTips->setStyleSheet("border-radius:5px;text-align:center;background: rgb(211, 215, 207); border: none;");
            mMessageTips->show();
        };

        QEventLoop loop;  // 创建一个事件循环对象
        // 创建一个线程执行状态观察者
        QFutureWatcher<void> watcher;
        //关联线程执行完毕信号，当线程执行完毕之后，退出QEventLoop的事件循环
        connect(&watcher, &QFutureWatcher<void>::finished, &loop, &QEventLoop::quit);

        // 运行并设置线程状态对象给观察者
        watcher.setFuture(QtConcurrent::run(runFunc));
        // 函数运行到此后阻塞，进入事件循环,等待退出回调
        loop.exec();

        // 退出了事件循环,函数继续往下执行

        img_state = 0;
    }
}

/**
 * @brief 给界面设置阴影
 * @param w
 */
void MainWindow::setShadowEffect(QWidget * w)
{
    QGraphicsDropShadowEffect * effect = new QGraphicsDropShadowEffect(w);
    effect->setOffset(0, 0);//设置阴影距离
    effect->setColor(QColor(0,0,0,90));//设置阴影颜色
    effect->setBlurRadius(15);//设置阴影圆角
    w->setStyleSheet(".QWidget{background-color:#FFFFFF;border-radius:6px;}");
    w->setGraphicsEffect(effect);
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        is_drag_ = true;
        //获得鼠标的初始位置
        mouse_start_point_ = event->globalPos();
        //获得窗口的初始位置
        window_start_point_ = this->frameGeometry().topLeft();
        dragPosition = mouse_start_point_-window_start_point_;
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
//    //判断是否在拖拽移动
    if (is_drag_)
    {
        //获得鼠标移动的距离
        QPoint move_distance = event->globalPos() - mouse_start_point_;
        //改变窗口的位置
        this->move(window_start_point_ + move_distance);
    }
//    if (event->buttons() & Qt::LeftButton){                 //如果左键是按下的
//            if(resizeDir == nodir){                             //如果鼠标不是放在边缘那么说明这是在拖动窗口
//                move(event->globalPos() - dragPosition);
//            }
//            else{
//                int ptop,pbottom,pleft,pright;                   //窗口上下左右的值
//                ptop = frameGeometry().top();
//                pbottom = frameGeometry().bottom();
//                pleft = frameGeometry().left();
//                pright = frameGeometry().right();
//                if(resizeDir & top){                               //检测更改尺寸方向中包含的上下左右分量
//                    if(height() == minimumHeight()){
//                        ptop = fmin(event->globalY(),ptop);
//                    }
//                    else if(height() == maximumHeight()){
//                        ptop = fmax(event->globalY(),ptop);
//                    }
//                    else{
//                        ptop = event->globalY();
//                    }
//                }
//                else if(resizeDir & bottom){
//                    if(height() == minimumHeight()){
//                        pbottom = fmax(event->globalY(),ptop);
//                    }
//                    else if(height() == maximumHeight()){
//                        pbottom = fmin(event->globalY(),ptop);
//                    }
//                    else{
//                        pbottom = event->globalY();
//                    }
//                }

//                if(resizeDir & left){                        //检测左右分量
//                    if(width() == minimumWidth()){
//                        pleft = fmin(event->globalX(),pleft);
//                    }
//                    else if(width() == maximumWidth()){
//                        pleft = fmax(event->globalX(),pleft);
//                    }
//                    else{
//                        pleft = event->globalX();
//                    }
//                }
//                else if(resizeDir & right){
//                    if(width() == minimumWidth()){
//                        pright = fmax(event->globalX(),pright);
//                    }
//                    else if(width() == maximumWidth()){
//                        pright = fmin(event->globalX(),pright);
//                    }
//                    else{
//                        pright = event->globalX();
//                    }
//                }
//                setGeometry(QRect(QPoint(pleft,ptop),QPoint(pright,pbottom)));
//            }
//        }
//        else testEdge(event);   //当不拖动窗口、不改变窗口大小尺寸的时候  检测鼠标边缘
}
void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
    //放下左键即停止移动
    if (event->button() == Qt::LeftButton)
    {
        is_drag_ = false;
    }
//    if(resizeDir != nodir){         //还原鼠标样式
//        testEdge(event);
//    }
}


//void MainWindow::enterEvent(QEvent* event){
//    QWidget::enterEvent(event);
//}

//void MainWindow::leaveEvent(QEvent* event){
//    QApplication::setOverrideCursor(Qt::IBeamCursor);
//    QWidget::leaveEvent(event);
//}

//void MainWindow::testEdge(QMouseEvent *event){
//    int diffLeft = event->globalPos().x() - frameGeometry().left();      //计算鼠标距离窗口上下左右有多少距离
//    int diffRight = event->globalPos().x() - frameGeometry().right();
//    int diffTop = event->globalPos().y() - frameGeometry().top();
//    int diffBottom = event->globalPos().y() - frameGeometry().bottom();

//    Qt::CursorShape cursorShape;
//    int EDGE_MARGIN=8;
//    if(diffTop < EDGE_MARGIN && diffTop>=0){                              //根据 边缘距离 分类改变尺寸的方向
//        if(diffLeft < EDGE_MARGIN && diffLeft>=0){
//            resizeDir = topLeft;
//            cursorShape = Qt::SizeFDiagCursor;
//        }
//        else if(diffRight > -EDGE_MARGIN && diffRight<=0){
//            resizeDir = topRight;
//            cursorShape = Qt::SizeBDiagCursor;
//        }
//        else{
//            resizeDir = top;
//            cursorShape = Qt::SizeVerCursor;
//        }
//    }
//    else if(abs(diffBottom) < EDGE_MARGIN && diffBottom<=0){
//        if(diffLeft < EDGE_MARGIN && diffLeft>=0){
//            resizeDir = bottomLeft;
//            cursorShape = Qt::SizeBDiagCursor;
//        }
//        else if(diffRight > -EDGE_MARGIN && diffRight<=0){
//            resizeDir = bottomRight;
//            cursorShape = Qt::SizeFDiagCursor;
//        }
//        else{
//            resizeDir = bottom;
//            cursorShape = Qt::SizeVerCursor;
//        }
//    }
//    else if(abs(diffLeft) < EDGE_MARGIN){
//        resizeDir = left;
//        cursorShape = Qt::SizeHorCursor;
//    }
//    else if(abs(diffRight) < EDGE_MARGIN){
//        resizeDir = right;
//        cursorShape = Qt::SizeHorCursor;
//    }
//    else{
//        resizeDir = nodir;
//        cursorShape = Qt::ArrowCursor;
//    }

//    QApplication::setOverrideCursor(cursorShape);

//}

void MainWindow::saveImage()
{
    if(!qnode.initFlag) return;
    switch (img_state) {
    case 0:
        img_state++;
        startTimer();
        break;
    case 1:
        img_state++;
        stopTimer();        
        break;
    default:
        //qDebug() << "state error!" << endl;
        break;
    }
}

void MainWindow::onTopicMapChanged(int index){
    if(!qnode.initFlag) return;
    //qDebug() << "set Map topic \n";
//    QStringList parts = ui.topics_map->itemData(index).toString().split(" ");
//    QString topic = parts.first();
//    if(!topic.isEmpty())
//        rpanel->mapDisplaySlot(topic);
    if(!qnode.mapList.empty()){
        rpanel->mapDisplaySlot(qnode.mapList);
    }
}

void MainWindow::onTopicLaserChanged(int index){
    if(!qnode.initFlag) return;
   // qDebug() << "set Laser topic \n";
    QStringList parts = ui.topics_laser->itemData(index).toString().split(" ");
    QString topic = parts.first();
    if(!topic.isEmpty())
        rpanel->LaserDisplaySlot(topic);
}

void MainWindow::onTopicChanged(int index){
    if(!qnode.initFlag) return;
   // qDebug() << "set img topic \n";
    QStringList parts = ui.topics_img->itemData(index).toString().split(" ");
    QString topic = parts.first();
    if(!topic.isEmpty())
        ui.rviz_img->setTopicSlot(topic);
}


/**
 * @brief 将全局坐标转换为局部坐标
 * @param (x,y,\theta)
 * @return 返回局部坐标系下的坐标
 */
state<double> MainWindow::getXYT(state<double> xyt){

//    state<double> s;
//    s=xyt-pos0;
//    s.x = s.x*cos(pos0.t)+s.y*sin(pos0.t);
//    s.y = s.y*cos(pos0.t)-s.x*sin(pos0.t);  // 要保存逆时针旋转为正
//    if(s.t>M_PI) s.t -= 2*M_PI;
//    else if( s.t<-M_PI) s.t += 2*M_PI;
////    qDebug() << QString("state: %1,%2,%3").arg(s.x).arg(s.y).arg(s.t);

//    return s;

    Eigen::AngleAxisd rotzp0(pos0.t, Eigen::Vector3d::UnitZ());
    Eigen::Matrix3d rotp0 = rotzp0.toRotationMatrix();
    Eigen::Isometry3d p0;
    p0 = rotp0;
    p0.translation() = Eigen::Vector3d(pos0.x, pos0.y, 0);

    Eigen::AngleAxisd rotzp1(xyt.t, Eigen::Vector3d::UnitZ());
    Eigen::Matrix3d rotp1 = rotzp1.toRotationMatrix();
    Eigen::Isometry3d p1;
    p1 = rotp1;
    p1.translation() = Eigen::Vector3d(xyt.x, xyt.y, 0);

    Eigen::Isometry3d t12=p0.inverse() *p1;
    Eigen::Matrix3d r12m=t12.rotation();
    Eigen::Vector3d vt12=t12.translation();
    Eigen::Vector3d eulerAngle=r12m.eulerAngles(0,1,2);
//    std::cout<<"eulerAngle roll pitch yaw\n" << 180*eulerAngle.transpose()/M_PI<< std::endl;
//    std::cout<<"t12="<<std::endl<< vt12.transpose()<< std::endl;

    state<double> s={vt12.x(), vt12.y(), eulerAngle.z()};
    return s;

}

void MainWindow::road_value_set(){
    QVector<double> px, py;
    auto vec = road.st_road.combin;
    plot->clearCurve();
    if(road.type==0){   // 直线来回倒退轨迹
        fb.clear();
        st_state=0;
        double left, right;
        left=0, right=vec[0].first;
        fb.push_back({left,right});
        left=right, right-=vec[0].second;
        fb.push_back({left,right});
        for (int i = 1; i < road.st_road.num; ++i) {
            left=right; right += vec[i].first;
            fb.push_back({left,right});
            left=right, right-=vec[i].second;
            fb.push_back({left,right});
        }
        plot->plotPolyLine(fb);
    }else if(road.type==1){ // S形轨迹
        double k=fmax(0.0001,road.c_road.cur), L = road.c_road.len;
        if( L == 0) return;
        double cx=L/4;
        double cy=sqrtf(1/(k*k)-L*L/16);
        double ang0=atan2(0-(-cy),0-cx);   // atan2 返回的是以x轴顺时针旋转方向，范围 (-pi, pi)
        double ang2=atan2(0-(-cy),L/2-cx);
        for(int i=0; i<100; i++){
            double ang = ang0+i*(ang2-ang0)/100;

            px.append(cx+cos(ang)/k);
            py.append(-cy+sin(ang)/k);
            // qDebug() <<ang*180/3.14  << "x " << cx+cos(ang)/k <<",y" << -cy+sin(ang)/k <<endl;
        }
        ang0=atan2(0-cy,L/2-3*L/4);   // atan2 返回的是以x轴顺时针旋转方向，范围 (-pi, pi)
        ang2=atan2(0-cy,L-3*L/4);
        for(int i=0; i<=100; i++){
            double ang = ang0+i*(ang2-ang0)/100;
            px.append(3*cx+cos(ang)/k);
            py.append(cy+sin(ang)/k);
            // qDebug() <<ang*180/3.14  << "x " << 3*cx+cos(ang)/k <<",y" << cy+sin(ang)/k <<endl;
        }
        // qDebug() << "ang:" << ang0*180/3.14 << " " << ang2*180/3.14 << endl;
        plot->plotDot(L,0);
        plot->plotxy(px,py);
        track->setPath({px,py});

    }else if(road.type==2){ // 圆形轨迹
        double ang=2*M_PI/100;
        for(double i=M_PI; i>=-M_PI; i-=ang){
            px.append( road.radius+road.radius*cos(i) );
            py.append( road.radius*sin(i) );
        }
        plot->plotDot(2*road.radius,0);
        plot->plotxy(px,py);
        track->setPath({px,py});
    }
}

/**
 * @brief 从里程计的获取局部坐标
 * @param x
 * @param y
 * @param yaw
 */
void MainWindow::local_coor(double x, double y, double yaw){
    imu_qual=true;
    if(!indoor) return ;
    char str[100];
//    qDebug
    posr={x,y,yaw};
    auto p = getXYT(posr);
    sprintf(str, "odom x:%0.3lf, y:%0.3lf, yaw:%0.3lf", p.x, p.y, p.t*180/M_PI);
    ui.label_4->setText(tr(str));
//    qDebug()<<  str;
}

int cnt=0;
void MainWindow::set_track_path(){
    if(param_fresh){
        param_fresh=false;
        slot_set_param(ui.selected_path->currentIndex());
    }
    if(!qnode.initFlag) return; //还未连接，不能刷新

    if(cnt++>10){ // 0.5秒更新一次消息
        cnt=0;
        changeComboex(ui.topics_vel,"geometry_msgs/Twist");
        changeComboex(ui.topics_img,"images");
//        updateMapTopicList();
    }

    if(!isTracking){ // 如果不是跟踪状态，启动遥控模式
        qnode.set_cmd_vel(vel.first, -vel.second);  // vel, angv
        return ;
    }
    if(!indoor&&gps_qual==false){    // GPS不可用，停车
        qnode.set_cmd_vel(0,0);
        slot_stopTrack();
        if(showtips==0){
            MessageTips *mMessageTips = new MessageTips(
                        "GPS不可用",this);
            mMessageTips->setStyleSheet("color:red;");
            mMessageTips->setCloseTimeSpeed();
            connect(mMessageTips,&MessageTips::close,[]{
                showtips=0;
            });
            mMessageTips->show();
        }
        else showtips=true;
    }
    if(indoor&&imu_qual==false){
        qnode.set_cmd_vel(0,0);
        slot_stopTrack();
        if(showtips==0){
            MessageTips *mMessageTips = new MessageTips(
                        "里程计不可用",this);
            mMessageTips->setStyleSheet("color:red;");
            mMessageTips->setCloseTimeSpeed();
            connect(mMessageTips,&MessageTips::close,[]{
                showtips=0;
            });
            mMessageTips->show();
        }
        else showtips=true;
    }

    auto p = getXYT(posr);
//    qDebug() << "p:" << p.x << " " << p.y << " " << p.t << endl;

//    cmd_time->timerId()
    if(!road.type){ // 跟踪直线路径的多个路径段
        if(st_state%2){
            qnode.set_cmd_vel(-0.5,0);
            if(p.x<fb[st_state].back())
                st_state++;
        }
        else{
            qnode.set_cmd_vel(0.5,0);
            if(p.x>fb[st_state].back())
                st_state++;
        }
        if(st_state >= fb.size()){
            isTracking=false;
            st_state=0;
            track_state=0;
            ui.track_path->setText("开始跟踪");
            ui.track_path->setChecked(false);
            ui.track_path->setStyleSheet("color:black;");
        }
        else {
//            qDebug()<<"test 0\n";
            plot->plotPath(p.x,st_state);    //
            plot->plotCar(p.x, st_state, 0);
        }
    }
    else if(road.type==1){
        qDebug()<<"test 1\n";
        plot->plotPath(p.x,p.y);    //
        plot->plotCar(p.x, p.y, p.t);
        auto [vx, va] = track->track_path({p.x, p.y, p.t});
        plot->plotDot(track->lookpoint.x(),track->lookpoint.y());
        qnode.set_cmd_vel(vx, va);  // vel, angv

    } else if(road.type==2){
//        qDebug()<<"test 2\n";
        plot->plotPath(p.x,p.y);    //
        plot->plotCar(p.x, p.y, p.t);
        if( st_state==0){
            qnode.set_cmd_vel(0,0.2);   //
            if(p.t >= M_PI/2)
                st_state++;
        } else if( st_state==1){
            QTime timedebuge;//声明一个时钟对象
                timedebuge.start();//开始计时
            auto [vx, va] = track->track_path({p.x, p.y, p.t});
            qDebug()<<"纯跟踪耗时: "<<timedebuge.elapsed()<<"ms";//输出计时
            plot->plotDot(track->lookpoint.x(),track->lookpoint.y());
            qnode.set_cmd_vel(vx, va);  // vel, angv
//            qDebug()<<"vel:" << vx << " " << va << endl;
        }
    }


}

void MainWindow::slot_set_param(int index){
    // qDebug() << "selected path type " << index << endl;
//    ui.track_path->setVisible(true);
//    ui.stop_track->setVisible(true);
    auto layout = ui.param_widget->layout();    
    for(auto var: pathWidgets){
        // qDebug() << "delete " <<  var->objectName()<< endl;
        layout->removeWidget(var);
        var->deleteLater();
        update();
    }
    while(!pathWidgets.empty()) pathWidgets.pop_back();
    if(!index){
//        ui.label_cur->setText("路径长度/m");
//        auto len_spinbox = set_spinbox<QDoubleSpinBox, double>(&road.st_road.len);
        auto label_st = new QLabel(ui.param_widget);
        label_st->setText("路径组合数");
        label_st->setObjectName("label_st");
        auto spin_st = set_spinbox<QSpinBox, int>(&road.st_road.num);
//        layout->addWidget(len_spinbox);
        layout->addWidget(label_st);
        layout->addWidget(spin_st);
//        pathWidgets.push_back(len_spinbox);
        pathWidgets.push_back(label_st);
        pathWidgets.push_back(spin_st);

        auto hlayout = new QHBoxLayout;//ui.widget_com->layout();
        auto blayout = new QHBoxLayout;
        if(road.st_road.combin.isEmpty()){
            QVector<QPair<double, double>> tmp(road.st_road.num);
            road.st_road.combin=tmp;
        }
        for (int i = 0; i < road.st_road.num; ++i) {
            if(road.st_road.combin.size()<= i)
                road.st_road.combin.append({0,0});
            auto label = new QLabel;
            label->setText("F"+QString::number(i));
            label->setMinimumWidth(30);
            auto spin_st = set_spinbox<QDoubleSpinBox, double>( &road.st_road.combin[i].first);
            hlayout->addWidget(label);
            hlayout->addWidget(spin_st);

            auto label2 = new QLabel;
            label2->setText("B"+QString::number(i));
            label2->setMinimumWidth(30);
            auto spin_st2 = set_spinbox<QDoubleSpinBox, double>(&road.st_road.combin[i].second);
            blayout->addWidget(label2);
            blayout->addWidget(spin_st2);

            pathWidgets.push_back(label);
            pathWidgets.push_back(label2);
            pathWidgets.push_back(spin_st);
            pathWidgets.push_back(spin_st2);
        }
        hlayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
        hlayout->setContentsMargins({9,1,9,1}); // left,  top,  right,  bottom
        blayout->setContentsMargins({9,1,9,1}); // left,  top,  right,  bottom
        blayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
        auto ly= ui.vertical_road;
        auto w=new QWidget;
        w->setLayout(hlayout);
        ly->addWidget(w);
        auto w2=new QWidget;
        w2->setLayout(blayout);
        ly->addWidget(w2);
        pathWidgets.push_back(w);
        pathWidgets.push_back(w2);
    }
    else if(index == 1){
        auto label = new QLabel(ui.param_widget);
        label->setText("路径长度/m");
        auto len_spinbox = set_spinbox<QDoubleSpinBox, double>(&road.c_road.len);
        auto spinbox_cur = set_spinbox<QDoubleSpinBox, double>(&road.c_road.cur);
        spinbox_cur->setDecimals(4);    // 小数点
        spinbox_cur->setSingleStep(0.0001);
        spinbox_cur->setValue(road.c_road.cur);
        auto label_cur = new QLabel(ui.param_widget);
        label_cur->setText("路径曲率/rad");
        label_cur->setObjectName("label_cur");
        layout->addWidget(label);
        layout->addWidget(len_spinbox);
        layout->addWidget(label_cur);
        layout->addWidget(spinbox_cur);
        pathWidgets.push_back(label);
        pathWidgets.push_back(len_spinbox);
        pathWidgets.push_back(label_cur);
        pathWidgets.push_back(spinbox_cur);
    }
    else if(index==2){  //
//        ui.label_cur->setText("半径/m");
        auto label = new QLabel("半径/m",ui.param_widget);
        auto len_spinbox = set_spinbox<QDoubleSpinBox,double>(&road.radius);
        pathWidgets.push_back(label);
        pathWidgets.push_back(len_spinbox);
        layout->addWidget(label);
        layout->addWidget(len_spinbox);
    }
    else if(index==3){  // 轨迹采点
//        ui.track_path->setVisible(false);
//        ui.stop_track->setVisible(false);

    }
    layout->removeItem(spacer);
    spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    layout->addItem(spacer);
    road.type=index;
    track->reset(); //
    plot->plotCar(0,0,0);
    road_value_set();
}

template <class T1,class T2>
T1* MainWindow::set_spinbox( T2 *value){
    auto len_spinbox = new T1;
    len_spinbox->setRange(0,1000);
    len_spinbox->setValue(*value);
    len_spinbox->setKeyboardTracking(false); // 全部输入再响应valueChanged
    // 当信号有重载时，需要用QOverload<double>::of来处理，否则无法使用lambda函数
//    qDebug() << "value change : " << *value<< endl;
    connect(len_spinbox,QOverload<T2>::of(&T1::valueChanged),[this,value](T2 val){
//        qDebug()  << "set value " << val;
        if(*value!=val){
            *value = val;
            param_fresh=true;
        }
    });
    return len_spinbox;
}

void MainWindow::changeComboex(QComboBox *combox, const QString& messagetype){
    QString selected= combox->currentText();
    combox->clear();
    QList<QString> topics;
    if(messagetype=="images")   // 如果是图像，需要特殊处理
        topics = qnode.getImgTopiclist();
    else
        topics = qnode.getTopics(messagetype);//

    for (QList<QString>::const_iterator it = topics.begin(); it != topics.end(); it++)
    {
        QString label(*it);
        if(topics.size()>1 && label==""){
          continue;
        }
      if(selected==""){
          selected = label;
      }
      label.replace(" ", "/");
      if(label.contains("UGV"+QString::number(qnode.car)))
          selected=label;
      combox->addItem(label, QVariant(*it));
    }
    // restore previous selection
    int index = combox->findText(selected);
  //  qDebug() << "combox_index:" <<index << endl;
    if (index == -1)
    {
      // add topic name to list if not yet in
      QString label(selected);
      label.replace(" ", "/");
      combox->addItem(label, QVariant(selected));
      index = combox->findText(selected);
    }
    combox->setCurrentIndex(index);
}

void MainWindow::updateMapTopicList(){
    //    qDebug() << "refresh image message" << endl;
    if(!qnode.initFlag) return; //还未连接，不能刷新
    changeComboex(ui.topics_map,"nav_msgs/OccupancyGrid");
    changeComboex(ui.topics_laser,"sensor_msgs/LaserScan");
    rpanel->robotModelDisplySlot();
    rpanel->showPath(qnode.pathList);
    rpanel->polyfootprint(qnode.polyList);
}

void MainWindow::updateImgTopicList()
{
    if(!qnode.initFlag) return; //还未连接，不能刷新
    changeComboex(ui.topics_img,"images");
}

void MainWindow::connectSuccess(int car){
    ui.label_link->setPixmap(
        QPixmap::fromImage(QImage("://images/online1.png")));
    ui.label_state->setStyleSheet("color:green;");
    ui.label_state->setText("在线");
//    qDebug() << "conncet car:" << car << " success!" << endl;
    if( car == 1){
        qnode.set_cmd_vel(0,0);
        ui.car1_connect->setChecked(false);
        ui.car1_connect->setStyleSheet("color:black;");
        ui.car0_connect->setStyleSheet("color:blue;");
    }else {
        qnode.set_cmd_vel(0,0);
        ui.car0_connect->setChecked(false);
        ui.car0_connect->setStyleSheet("color:black;");
        ui.car1_connect->setStyleSheet("color:blue;");
    }
    rpanel->initPanelSlot();
    updateMapTopicList();
    ui.rviz_img->initPanelSlot();   //
    updateImgTopicList();
    connectState = car;   //
    qnode.car=car-1;
    if( isTracking ) slot_stopTrack();   //

    ui.vel_slider->setValue(qnode.vmax[qnode.car]*100);
    ui.ang_slide->setValue(qnode.angmax[qnode.car]*100);
}

void MainWindow::connectFailed(int car){
    showNoMasterMessage();
    ui.label_link->setPixmap(
        QPixmap::fromImage(QImage("://images/offline1.png")));
    ui.label_state->setStyleSheet("color:red;");
    ui.label_state->setText("离线");
//    qDebug() << "conncet car:" << car << " failed!" << endl;
}

bool MainWindow::connectMaster(QString master_ip, QString ros_ip, int car) {
    if ( ! qnode.init(master_ip.toStdString(),
               ros_ip.toStdString(), car) ) {   // 如果roscore没打开，通过执行命令打开
        return false;
    }
    else
        connectSuccess(car);
    return true;
}

void MainWindow::slot_car_connect(int car){
    if(connectState==car) return ;    // has connect
    if(ui.local_ip->isChecked()){
        if ( !qnode.init(car) ) {   // 如果roscore没打开，通过执行命令打开
            return ;
        }
        else
            connectSuccess(car);
        return ;
    }
    QString master= car0_qMasterIp;
    if( car == 1){
        connectMaster(master, car0_qRosIp, 1);
    }
    else{        
        connectMaster(master, car1_qRosIp, 2);
    }
}

void MainWindow::slot_set_start_pose()
{
    rpanel->Set_Start_Pose();
}

bool trg=false;
void MainWindow::slot_update_power(float value)
{
    ui.label_voltage->setText(QString::number(value/10,'f',2)+"V");
    double n=(value-210)/(240-210);
    int val=n*100;
    val = val>100?100:val;
    ui.progressBar->setValue(val);

    if(val <= 10 && trg){
        trg=false;
        MessageTips *mMessageTips = new MessageTips(
                    "电量不足！请及时充电!"
                    ,this);
        mMessageTips->show();
    }

    //当电量过低时发出提示
    if (val <= 20 && (volState == 0||volState == 2)) {
        volState = 1;
      ui.progressBar->setStyleSheet(
          "QProgressBar::chunk {background-color: red;width: 20px;} "
          "QProgressBar {background: rgb(211, 215, 207);border: none;border-radius: 5px;text-align: center;}");
    } else if( val > 20 && (volState == 0||volState == 1)){
        volState = 2;trg=true;
      ui.progressBar->setStyleSheet(
            "QProgressBar{border-radius:5px;text-align:center;background: rgb(211, 215, 207); border: none; color: rgb(229, 229, 229); }"
            "QProgressBar:chunk{ background-color:rgb(115, 210, 22); }");
    }

}

void MainWindow::slot_update_dashboard(float x,float y)
{
    QString sx=" ",sy=" ";
    if(x<0) sx="-"; if(y<0) sy="-";
    ui.label_vel->setText(QString(sx+"%1").arg(abs(x),4,'f',2));
    ui.label_rad->setText(QString(sy+"%1").arg(abs(y),4,'f',2));
}

MainWindow::~MainWindow() {
    if(qnode.initFlag){ // 防止关闭界面时 控制命令还在执行
        qnode.set_cmd_vel(0,0);
    }
}

/*****************************************************************************
** Implementation [Slots]
*****************************************************************************/

void MainWindow::showNoMasterMessage() {
	QMessageBox msgBox;
	msgBox.setText("Couldn't find the ros master.");
	msgBox.exec();
    close();
}

/*****************************************************************************
** Implementation [Configuration]
*****************************************************************************/

void MainWindow::ReadSettings() {
    qRegisterMetaTypeStreamOperators<road_data>("road_data");//注册结构体的操作流,就是重写的输入输出流
    qRegisterMetaType<road_data>("road_data");//注册结构体
    QSettings settings("Qt-Ros Package", "robot_hmi");
    img_filepath = settings.value("img_filepath").toString();
    map_filepath = settings.value("map_filepath").toString();
    QVariant v = settings.value("road");
    road = v.value<road_data>();   // struct
    //
    qnode.vmax[0] = settings.value("vmax0").toFloat();
    qnode.vmax[1] = settings.value("vmax1").toFloat();
    qnode.angmax[0] = settings.value("angmax0").toFloat();
    qnode.angmax[1] = settings.value("angmax1").toFloat();
    QString ip = settings.value("master_ip").toString();
    if(ip!="") car0_qMasterIp = ip;
    ui.local_ip->setChecked(settings.value("isLocal").toBool());
}

void MainWindow::WriteSettings() {
    QSettings settings("Qt-Ros Package", "robot_hmi");
    settings.setValue("img_filepath",img_filepath);
    settings.setValue("map_filepath",map_filepath);
    settings.setValue("road",QVariant::fromValue(road));   // struct
    settings.setValue("vmax0",qnode.vmax[0]);
    settings.setValue("vmax1",qnode.vmax[1]);
    settings.setValue("angmax0",qnode.angmax[0]);
    settings.setValue("angmax1",qnode.angmax[1]);
    settings.setValue("master_ip",car0_qMasterIp);
    settings.setValue("isLocal",ui.local_ip->isChecked());
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	WriteSettings();
	QMainWindow::closeEvent(event);
}

}  // namespace robot_hmi

