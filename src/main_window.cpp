/**
 * @file /src/main_window.cpp
 *
 * @brief Implementation for the qt gui.
 *
 * @date February 2011
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include "../include/cyrobot_monitor/main_window.hpp"

#include <QMessageBox>
#include <QtGui>
#include <cstdio>
#include <iostream>
#include <string>

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace cyrobot_monitor {

using namespace Qt;

mission_parse::formationwithtask f_msg;
mission_parse::reconnoitrewithtask r_msg;

/*****************************************************************************
** Implementation [MainWindow]
*****************************************************************************/

MainWindow::MainWindow(int argc, char** argv, QWidget* parent)
    : QMainWindow(parent)
    , qnode(argc, argv)
{
    ui.setupUi(this); // Calling this incidentally connects all ui's triggers to
        // on_...() callbacks in this class.
    // QObject::connect(ui.actionAbout_Qt, SIGNAL(triggered(bool)), qApp,
    // SLOT(aboutQt())); // qApp is a global variable for the application
    initUis();
    //读取配置文件
    ReadSettings();
    initData();
    setWindowIcon(QIcon(":/images/robot.png"));
    ui.tab_manager->setCurrentIndex(
        0); // ensure the first tab is showing - qt-designer should have this
    // already hardwired, but often loses it (settings?).
    //    QObject::connect(&qnode, SIGNAL(rosShutdown()), this, SLOT(close()));

    /*********************
   ** Logging
   **********************/
    ui.view_logging_3->setModel(qnode.loggingModel());

    /*********************
  ** 自动连接master
  **********************/

    if (ui.checkbox_remember_settings->isChecked()) {
        on_button_connect_clicked(true);
    }
    //链接connect
    connections();
}
//订阅video话题
void MainWindow::initVideos()
{
    QSettings video_topic_setting("video_topic", "cyrobot_monitor");
    QStringList names = video_topic_setting.value("names").toStringList();
    QStringList topics = video_topic_setting.value("topics").toStringList();

    int leader_id = f_msg.leader_id;

    for (int i = 0; i < names.size(); i++) {
        // leader_id = 0 :  no need to change
        if (leader_id == 0) {
            ui.test_video->widgets.at(i)->setBgText(names[i]);
            ui.test_video->widgets.at(i)->setOSD2Text(
                names[i]); //设置视频窗口背景文字
            ui.test_video->widgets.at(i)->setOSD2FontSize(
                25); //设置视频窗口背景文字大小
        }
        // leader_id != 0 : need to change the text of (index)0 and (index)leader_id
        else {
            if (i == 0) {
                ui.test_video->widgets.at(i)->setBgText(names[leader_id]);
                ui.test_video->widgets.at(i)->setOSD2Text(
                    names[leader_id]); //设置视频窗口背景文字
                ui.test_video->widgets.at(i)->setOSD2FontSize(
                    25); //设置视频窗口背景文字大小
            } else if (i == leader_id) {
                ui.test_video->widgets.at(i)->setBgText(names[0]);
                ui.test_video->widgets.at(i)->setOSD2Text(
                    names[0]); //设置视频窗口背景文字
                ui.test_video->widgets.at(i)->setOSD2FontSize(
                    25); //设置视频窗口背景文字大小
            } else {
                ui.test_video->widgets.at(i)->setBgText(names[i]);
                ui.test_video->widgets.at(i)->setOSD2Text(
                    names[i]); //设置视频窗口背景文字
                ui.test_video->widgets.at(i)->setOSD2FontSize(
                    25); //设置视频窗口背景文字大小
            }
        }
    }
    for (int i = 0; i < topics.size(); i++) {
        //       qDebug() <<"我现在的状态~~~~~~~~~~~: "<< i;
        //       if(topics[i]!="")  qnode.Sub_Image(topics[i],i);

        if (topics[i] != "")
            qnode.Sub_Image(topics[i], i, leader_id);
    }

    //链接槽函数
    connect(&qnode, SIGNAL(Show_image(int, QImage)), this,
        SLOT(slot_show_image(int, QImage)));
}

void MainWindow::slot_show_image(int frame_id, QImage image)
{
    ui.test_video->widgets.at(frame_id)->receiveImage(image);
}

//初始化UI
void MainWindow::initUis()
{
    //     qDebug() << "我进入到 initUis 了!!!!";

    //    m_DashBoard_x = new CCtrlDashBoard(ui.widget_speed_x);
    //    m_DashBoard_x->setGeometry(ui.widget_speed_x->rect());
    //    m_DashBoard_x->setValue(0);
    //    m_DashBoard_y = new CCtrlDashBoard(ui.widget_speed_y);
    //    m_DashBoard_y->setGeometry(ui.widget_speed_y->rect());
    //    m_DashBoard_y->setValue(0);

    //    m_DashBoard_x_2 = new GaugePanel(ui.widget_speed_x_2);
    //    m_DashBoard_x_2->setGeometry(ui.widget_speed_x_2->rect());
    //    m_DashBoard_x_2->setUnit("cm/s");
    //    m_DashBoard_x_2->setText("");
    //    m_DashBoard_y_2 = new GaugePanel(ui.widget_speed_y_2);
    //    m_DashBoard_y_2->setGeometry(ui.widget_speed_y_2->rect());
    //    m_DashBoard_y_2->setUnit("cm/s");
    //    m_DashBoard_y_2->setText("");
    ui.widget_speed_x_2->setUnit("cm/s");
    ui.widget_speed_x_2->setText("");
    ui.widget_speed_y_2->setUnit("cm/s");
    ui.widget_speed_y_2->setText("");

    ui.tab_manager->setCurrentIndex(0);
    ui.tab_manager->setFixedIndex(0); //固定第一个标签页
    ui.tabWidget->setCurrentIndex(0);

    //    test_label = new QLabel();
    //    test_label->setText("TEST");
    //    ui.verticalLayout_js->addWidget(test_label);

    ui.car_control->setCurrentIndex(0); //默认是car0

    //图像旋转组件
    rotateLabel = new QButtonGroup(this);
    //    for(int i = 0; i < CARNUM;i++){
    //        rotateLabel->addButton(ui.test_video->widgets.at(i)->flowButton->button(3),i);
    //    }

    ui.pushButton_remove_topic->setEnabled(false);
    ui.pushButton_rename_topic->setEnabled(false);

    // qucik treewidget
    ui.treeWidget_quick_cmd->setHeaderLabels(QStringList() << "key"
                                                           << "values");
    ui.treeWidget_quick_cmd->setHeaderHidden(true);

    /**********openstreetmap地图加载 start ****************/
    //    QQuickWidget* m_quickWidget;
    //    m_quickWidget = new QQuickWidget(this);
    //    qmlRegisterType<FileOperate>("FileOperate", 1, 0,
    //        "FileOperate"); //注册C++类带qml
    //    m_quickWidget->setResizeMode(
    //        QQuickWidget::SizeRootObjectToView); //设置窗口大小为父窗口大小
    //    m_quickWidget->setFocus();
    //    m_quickWidget->setSource(
    //        QUrl::fromLocalFile("://qml/qosm.qml")); //加载qml资源

    /**********openstreetmap地图加载 end ****************/

    /******************图像显示 start**************************/
    for (int i = 0; i < ui.test_video->videoCount; i++) {
        //监听每个视频窗口的按键
        connect(ui.test_video->widgets.at(i), SIGNAL(btnClicked(QString)), this,
            SLOT(getbtnClicked(QString)));
        //监听每个视频窗口的编码下拉框
        connect(ui.test_video->widgets.at(i),
            SIGNAL(comboxCurrentChange(int, QString)), this,
            SLOT(getcomboxIndex(int, QString)));
        //        ui.test_video->widgets.at(i)->getButtonGroup()->button(0)->setCheckable(true);
        //        ui.test_video->widgets.at(i)->getButtonGroup()->button(0)->setChecked(true);
        //        ui.test_video->widgets.at(i)->getButtonGroup()->button(2)->setChecked(true);

        //        ui.test_video->widgets.at(i)->getButtonGroup()->button(0)->setAutoExclusive(true);
    }
    /******************图像显示 end ***************************/

    //    QPixmap *pixmap = new QPixmap(":/images/gear.png");
    //    pixmap->scaled(ui.vel_s->size(), Qt::KeepAspectRatio);
    //    ui.vel_s->setScaledContents(true);
    //    ui.vel_s->setPixmap(*pixmap);

    //    QPixmap fitpixmap = pixmap.scaled(Qt::IgnoreAspectRatio,
    //    Qt::SmoothTransformation);  // 饱满填充

    // QPixmap fitpixmap = pixmap.scaled(with, height, Qt::KeepAspectRatio,
    // Qt::SmoothTransformation);  // 按比例缩放

    //    ui.vel_s->setPixmap(fitpixmap);
    //    QLabel *abel=new QLabel();

    ////    ui->label->setPixmap(QPixmap::fromImage(*img));
    //    ui.vel_s->setPixmap(QPixmap::fromImage(*img));
    //    ui.vel_s->setScaleContents(true);

    //JoyStick TODO
    addJoyStick(ui.verticalLayout_js_2);
    ui.verticalLayout_js->setVisible(false);
    on_car_changed(0);

    QSettings road_setting("road_topic", "cyrobot_monitor");
    ui.road_topic_edit->setText(road_setting.value("road/topic", "").toString());
    ui.carpos_topic_edit->setText(road_setting.value("carpos/topic", "").toString());
}

void MainWindow::getbtnClicked(QString str)
{
    VideoWidget* videoWidget = (VideoWidget*)sender();
    QString tr = QString("当前单击了窗口 %1 的按钮 %2")
                     .arg(videoWidget->objectName())
                     .arg(str);
    qDebug() << tr;
    QString objName = videoWidget->objectName();
    QChar a = objName.at(0);
    int b = a.toLatin1() - '0';

    // which button => index
    int index;
    for (int i = 0; i < ui.test_video->widgets[0]->video_btns.count(); i++) {
        if (str == ui.test_video->widgets[0]->video_btns[i]) {
            index = i;
        }
    }
    // which videoWidget => id
    int id = videoWidget->objectName().toInt();
    if (index == 1) {
        qnode.videoSet[id].horMir = ui.test_video->widgets[id]->video_ischecked[index];
        qDebug() << "horizontal mirrored check states:"
                 << qnode.videoSet[id].horMir;
    } else if (index == 2) {
        qnode.videoSet[id].verMir = ui.test_video->widgets[id]->video_ischecked[index];
        qDebug() << "vertical mirrored check states:" << qnode.videoSet[id].verMir;
    } else if (index == 3) {
        qnode.videoSet[id].rotate = ui.test_video->widgets[id]->rotate_id;
    }

    qDebug() << b;
    qDebug() << "status:"
             << videoWidget->getButtonGroup()->button(0)->isChecked();
}

void MainWindow::getcomboxIndex(int index, QString objName)
{
    VideoWidget* videoWidget = (VideoWidget*)sender();
    QString tr = QString("当前单击了窗口 %1 的按钮 %2,现在是%3")
                     .arg(videoWidget->objectName())
                     .arg(objName)
                     .arg(index);
    qDebug() << tr;
    QString obj = videoWidget->objectName();
    int it = obj.at(0).toLatin1() - '0'; //获取窗口的id
    if (it < CARNUM)
        qnode.videoSet[it].id = index;
}

void MainWindow::initRviz()
{
    // ui->label_rvizShow->hide();
    addtopic_form = new AddTopics();
    connect(addtopic_form, SIGNAL(Topic_choose(QTreeWidgetItem*, QString)), this,
        SLOT(slot_choose_topic(QTreeWidgetItem*, QString)));

    map_rviz = new QRviz(ui.verticalLayout_build_map, "qrviz");
    connect(map_rviz, &QRviz::ReturnModelSignal, this, &MainWindow::RvizGetModel);
    map_rviz->GetDisplayTreeModel();
    QMap<QString, QVariant> namevalue;
    namevalue.insert("Line Style", "Billboards");
    namevalue.insert("Color", QColor(160, 160, 160));
    namevalue.insert("Plane Cell Count", 10);
    map_rviz->DisplayInit(RVIZ_DISPLAY_GRID, "Grid", true, namevalue);

    ui.pushButton_add_topic->setEnabled(true);
}

void MainWindow::connections()
{
    QObject::connect(&qnode, SIGNAL(loggingUpdated()), this,
        SLOT(updateLoggingView()));
    QObject::connect(&qnode, SIGNAL(rosShutdown()), this,
        SLOT(slot_rosShutdown()));
    QObject::connect(&qnode, SIGNAL(Master_shutdown()), this,
        SLOT(slot_rosShutdown()));
    // connect速度的信号
    connect(&qnode, SIGNAL(speed_x(double)), this, SLOT(slot_speed_x(double)));
    connect(&qnode, SIGNAL(speed_y(double)), this, SLOT(slot_speed_y(double)));
    connect(&qnode, SIGNAL(flag_error(char)), this, SLOT(slot_flag_err(char)));
    //电源的信号
    //    connect(&qnode, SIGNAL(power(float)), ui.road_l, SLOT(setType(int)));

    //    connect(&qnode,SIGNAL())

    //道路类型信号
    connect(&qnode, SIGNAL(getTypeValue(int)), ui.road_l, SLOT(setType(int)));
    //    connect(&qnode, SIGNAL(getCurvValue(double)), ui.road_plot_1, SLOT(addValueSlot(double)));
    //    connect(&qnode, SIGNAL(getSlopeValue(double)), ui.road_plot_2, SLOT(addValueSlot(double)));
    connect(&qnode, SIGNAL(updateCarPos(double, double)), ui.road_plot, SLOT(update_focusmap_slots(double, double)));
    connect(ui.road_topic_button, SIGNAL(pressed()), this, SLOT(on_road_topic_changed()));
    connect(ui.carpos_topic_button, SIGNAL(pressed()), this, SLOT(on_carpos_topic_changed()));

    //机器人位置信号
    connect(&qnode, SIGNAL(position(QString, double, double, double, double)),
        this,
        SLOT(slot_position_change(QString, double, double, double, double)));
    //绑定快捷按钮相关函数
    connect(ui.quick_cmd_add_btn, SIGNAL(clicked()), this, SLOT(quick_cmd_add()));
    connect(ui.quick_cmd_remove_btn, SIGNAL(clicked()), this,
        SLOT(quick_cmd_remove()));
    //绑定slider的函数
    connect(ui.horizontalSlider_raw, SIGNAL(valueChanged(int)), this,
        SLOT(on_Slider_raw_valueChanged(int)));
    connect(ui.horizontalSlider_linear, SIGNAL(valueChanged(int)), this,
        SLOT(on_Slider_linear_valueChanged(int)));
    //设置界面
    connect(ui.action_2, SIGNAL(triggered(bool)), this,
        SLOT(slot_setting_frame()));
    ui.action_2->setShortcut(tr("F1"));
    connect(ui.setFilePath, SIGNAL(triggered(bool)), this,
        SLOT(slot_setting_filepath()));
    ui.setFilePath->setShortcut(tr("F2"));
    //   ui.menu_help->setShortcutEnabled()
    //绑定速度控制按钮
    connect(ui.pushButton_s, SIGNAL(clicked()), this, SLOT(slot_cmd_control()));
    connect(ui.pushButton_i, SIGNAL(clicked()), this, SLOT(slot_cmd_control()));
    connect(ui.pushButton_u, SIGNAL(clicked()), this, SLOT(slot_cmd_control()));
    connect(ui.pushButton_o, SIGNAL(clicked()), this, SLOT(slot_cmd_control()));
    connect(ui.pushButton_j, SIGNAL(clicked()), this, SLOT(slot_cmd_control()));
    connect(ui.pushButton_l, SIGNAL(clicked()), this, SLOT(slot_cmd_control()));
    connect(ui.pushButton_m, SIGNAL(clicked()), this, SLOT(slot_cmd_control()));
    connect(ui.pushButton_back, SIGNAL(clicked()), this,
        SLOT(slot_cmd_control()));
    connect(ui.pushButton_backr, SIGNAL(clicked()), this,
        SLOT(slot_cmd_control()));

    //更换控制车辆
    connect(ui.car_control, SIGNAL(currentIndexChanged(int)), this, SLOT(on_car_changed(int)));

    ////////////////////////rviz UI界面设置 --start ///////////////////
    //设置2D Pose
    connect(ui.set_pos_btn, SIGNAL(clicked()), this, SLOT(slot_set_2D_Pos()));
    //设置2D goal
    connect(ui.set_goal_btn, SIGNAL(clicked()), this, SLOT(slot_set_2D_Goal()));
    //设置MoveCamera
    connect(ui.move_camera_btn, SIGNAL(clicked()), this,
        SLOT(slot_move_camera_btn()));
    //设置Select
    connect(ui.set_select_btn, SIGNAL(clicked()), this, SLOT(slot_set_select()));
    //设置返航点
    connect(ui.set_return_btn, SIGNAL(clicked()), this,
        SLOT(slot_set_return_point()));
    //返航
    connect(ui.return_btn, SIGNAL(clicked()), this, SLOT(slot_return_point()));
    //左工具栏tab索引改变
    connect(ui.tab_manager, SIGNAL(currentChanged(int)), this,
        SLOT(slot_tab_manage_currentChanged(int)));
    //右工具栏索引改变
    connect(ui.tabWidget, SIGNAL(currentChanged(int)), this,
        SLOT(slot_tab_Widget_currentChanged(int)));
    //
    connect(ui.refreash_topic_btn, SIGNAL(clicked()), this,
        SLOT(refreashTopicList()));

    // RVIZ 开关
    connect(ui.switch_rviz, SIGNAL(statusChanged(bool)), this,
        SLOT(on_switchRviz_changed(bool)));

    //在set创建处连接
    //    //rviz topic 更新 TODO
    //    connect(set, SIGNAL(rviz_topic_changed()), this, SLOT(slot_rviz_topic_changed()));
    //    //车辆name更新
    //    connect(set, SIGNAL(button_name_changed()), this, SLOT(slot_button_name_changed()));
}

void MainWindow::initRvizPanel()
{
    ui.rviz_image->initPanelSlot();
    ui.rviz_pc2_1->initPanelSlot();
    ui.rviz_pc2_2->initPanelSlot();
    ui.rviz_gridmap->initPanelSlot();
}
void MainWindow::deinitRvizPanel()
{
    ui.rviz_image->deinitPanelSlot();
    ui.rviz_pc2_1->deinitPanelSlot();
    ui.rviz_pc2_2->deinitPanelSlot();
    ui.rviz_gridmap->deinitPanelSlot();
}
//rviz topic 更新 TODO
void MainWindow::slot_rviz_topic_changed()
{
    QSettings rviz_setting("rviz_topic", "cyrobot_monitor");
    ui.rviz_image->setTopicSlot(rviz_setting.value("rviz/Image/topic", "").toString());
    ui.rviz_pc2_1->setTopicSlot(rviz_setting.value("rviz/PC2Lidar/topic", "").toString());
    ui.rviz_pc2_2->setTopicSlot(rviz_setting.value("rviz/PC2Colored/topic", "").toString());
    ui.rviz_gridmap->setTopicSlot(rviz_setting.value("rviz/GridMap/topic", "").toString());

    ui.rviz_pc2_1->setFixedFrameSlot(rviz_setting.value("rviz/PC2Lidar/fixedframe", "").toString());
    ui.rviz_pc2_2->setFixedFrameSlot(rviz_setting.value("rviz/PC2Colored/fixedframe", "").toString());
    ui.rviz_gridmap->setFixedFrameSlot(rviz_setting.value("rviz/GridMap/fixedframe", "").toString());
}

//车辆name更新
void MainWindow::slot_button_name_changed()
{
    QSettings video_topic_setting("video_topic", "cyrobot_monitor");
    QStringList names = video_topic_setting.value("names").toStringList();
    QStringList topics = video_topic_setting.value("topics").toStringList();

    int num = names.size();
    for (int i = 0; i < num; i++) {
        ui.car_control->setItemText(i, names[i]);
    }
}

//设置界面
void MainWindow::slot_setting_frame()
{
    if (set != NULL) {
        delete set;
        set = new Settings();
        set->setWindowModality(Qt::ApplicationModal);
        set->show();
    } else {
        set = new Settings();
        set->setWindowModality(Qt::ApplicationModal);
        set->show();
    }
    //绑定set确认按钮点击事件
    //rviz topic 更新 TODO
    connect(set, SIGNAL(rviz_topic_changed()), this, SLOT(slot_rviz_topic_changed()));
    //车辆name更新
    connect(set, SIGNAL(button_name_changed()), this, SLOT(slot_button_name_changed()));
}

void MainWindow::slot_setting_filepath()
{
    QMessageBox::information(this, QString::fromLocal8Bit("警告"),
        QString::fromLocal8Bit("请耐心等待开发"));
}
//刷新当前坐标
void MainWindow::slot_position_change(QString frame, double x, double y,
    double z, double w)
{
    //更新ui显示
    ui.label_frame->setText(frame);
    ui.label_x->setText(QString::number(x));
    ui.label_y->setText(QString::number(y));
    ui.label_z->setText(QString::number(z));
    ui.label_w->setText(QString::number(w));
}
//刷新返航地点
void MainWindow::slot_set_return_point()
{
    //更新ui返航点显示
    ui.label_return_x->setText(ui.label_x->text());
    ui.label_return_y->setText(ui.label_y->text());
    ui.label_return_z->setText(ui.label_z->text());
    ui.label_return_w->setText(ui.label_w->text());
    //写入setting
    QSettings settings("return-position", "cyrobot_monitor");
    settings.setValue("x", ui.label_x->text());
    settings.setValue("y", ui.label_y->text());
    settings.setValue("z", ui.label_z->text());
    settings.setValue("w", ui.label_w->text());
    //发出声音提醒
    if (media_player != NULL) {
        delete media_player;
        media_player = NULL;
    }
    media_player = new QSoundEffect;
    media_player->setSource(QUrl::fromLocalFile("://media/refresh_return.wav"));
    media_player->play();
}
//返航
void MainWindow::slot_return_point()
{
    qnode.set_goal(ui.label_frame->text(), ui.label_return_x->text().toDouble(),
        ui.label_return_y->text().toDouble(),
        ui.label_return_z->text().toDouble(),
        ui.label_return_w->text().toDouble());
    if (media_player != NULL) {
        delete media_player;
        media_player = NULL;
    }
    media_player = new QSoundEffect;
    media_player->setSource(QUrl::fromLocalFile("://media/start_return.wav"));
    media_player->play();
}
//设置导航当前位置按钮的槽函数
void MainWindow::slot_set_2D_Pos()
{
    map_rviz->Set_Pos();
    // ui.label_map_msg->setText("请在地图中选择机器人的初始位置");
}
//设置导航目标位置按钮的槽函数
void MainWindow::slot_set_2D_Goal()
{
    map_rviz->Set_Goal();
    //  ui.label_map_msg->setText("请在地图中选择机器人导航的目标位置");
}
void MainWindow::slot_move_camera_btn()
{
    map_rviz->Set_MoveCamera();
    qDebug() << "move camera";
}
void MainWindow::slot_set_select() { map_rviz->Set_Select(); }

///
/// \brief 检查重名
/// \param name
/// \return
///
QString MainWindow::JudgeDisplayNewName(QString name)
{
    if (m_modelRvizDisplay != nullptr) {
        bool same = true;
        while (same) {
            same = false;
            for (int i = 0; i < m_modelRvizDisplay->rowCount(); i++) {
                // m_sRvizDisplayChooseName = index.data().value<QString>();
                if (m_modelRvizDisplay->index(i, 0).data().value<QString>() == name) {
                    if (name.indexOf("_") != -1) {
                        int num = name.section("_", -1, -1).toInt();
                        name = name.left(name.length() - name.section("_", -1, -1).length() - 1);
                        if (num <= 1) {
                            num = 2;
                        } else {
                            num++;
                        }
                        name = name + "_" + QString::number(num);
                    } else {
                        name = name + "_2";
                    }
                    same = true;
                    break;
                }
            }
        }
    }
    return name;
}

//选中要添加的话题的槽函数
void MainWindow::slot_choose_topic(QTreeWidgetItem* choose, QString name)
{
    QString ClassID = choose->text(0);
    // 检查重名
    name = JudgeDisplayNewName(name);

    qDebug() << "choose topic ClassID:" << ClassID << ", name:" << name;
    QMap<QString, QVariant> namevalue;
    namevalue.clear();
    map_rviz->DisplayInit(m_mapRvizDisplays[ClassID], name, true, namevalue);
}

//左工具栏索引改变
void MainWindow::slot_tab_manage_currentChanged(int index)
{
    switch (index) {
    case 0:

        break;
    case 1:

        //        ui.tabWidget->setCurrentIndex(1);
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        //        ui.tabWidget->setCurrentIndex(4);
        break;
    }
}

//右工具栏索引改变
void MainWindow::slot_tab_Widget_currentChanged(int index)
{
    switch (index) {
    case 0:

        break;
    case 1:
        //        ui.tab_manager->setCurrentIndex(1);
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        //        ui.tab_manager->setCurrentIndex(4);
        break;
    }
}

//速度控制相关按钮处理槽函数
void MainWindow::slot_cmd_control()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());

    if (!qnode.isWork)
        return;

    char key; //=btn->text().toStdString()[0];
    if (ui.pushButton_s->objectName().toStdString() == btn->objectName().toStdString())
        key = 'K';
    else if (ui.pushButton_i->objectName().toStdString() == btn->objectName().toStdString())
        key = 'i';
    else if (ui.pushButton_j->objectName().toStdString() == btn->objectName().toStdString())
        key = 'j';
    else if (ui.pushButton_u->objectName().toStdString() == btn->objectName().toStdString())
        key = 'u';
    else if (ui.pushButton_l->objectName().toStdString() == btn->objectName().toStdString())
        key = 'l';
    else if (ui.pushButton_o->objectName().toStdString() == btn->objectName().toStdString())
        key = 'o';
    else if (ui.pushButton_m->objectName().toStdString() == btn->objectName().toStdString())
        key = 'm';
    else if (ui.pushButton_backr->objectName().toStdString() == btn->objectName().toStdString())
        key = '.';
    else if (ui.pushButton_back->objectName().toStdString() == btn->objectName().toStdString())
        key = ',';

    // if( getCar == "pu")

    char curCar = ui.car_control->currentIndex();

    //速度
    float liner = ui.horizontalSlider_linear->value() * 0.01;
    float turn = ui.horizontalSlider_raw->value() * 0.01;
    bool is_all = ui.checkBox_use_all->isChecked();
    switch (key) {
    case 'u':
        qnode.move_base(is_all ? 'U' : 'u', liner, turn, curCar);
        break;
    case 'i':
        qnode.move_base(is_all ? 'I' : 'i', liner, turn, curCar);
        break;
    case 'o':
        qnode.move_base(is_all ? 'O' : 'o', liner, turn, curCar);
        break;
    case 'j':
        qnode.move_base(is_all ? 'J' : 'j', liner, turn, curCar);
        break;
    case 'l':
        qnode.move_base(is_all ? 'L' : 'l', liner, turn, curCar);
        break;
    case 'm':
        qnode.move_base(is_all ? 'M' : 'm', liner, turn, curCar);
        break;
    case ',':
        qnode.move_base(is_all ? '<' : ',', liner, turn, curCar);
        break;
    case '.':
        qnode.move_base(is_all ? '>' : '.', liner, turn, curCar);
        break;
    case 'K':
        qnode.move_base(is_all ? 'k' : 'K', liner, turn, curCar);
        break;
    }
}

//数字键盘控制车辆
void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (!qnode.isWork)
        return;

    switch (event->key()) {
    case Qt::Key_0:
        break;
    case Qt::Key_Up:
        qDebug() << "press up";
        break;
    case Qt::Key_Down:
        qDebug() << "press down";
        break;
    case Qt::Key_Left:
        qDebug() << "press left";
        break;
    case Qt::Key_Right:
        qDebug() << "press right";
        break;
    }

    char curCar = ui.car_control->currentIndex();

    //速度
    float liner = ui.horizontalSlider_linear->value() * 0.01;
    float turn = ui.horizontalSlider_raw->value() * 0.01;
    bool is_all = ui.checkBox_use_all->isChecked();
    switch (event->key()) {
    case Qt::Key_7: //↖
        qnode.move_base(is_all ? 'U' : 'u', liner, turn, curCar);
        break;
    case Qt::Key_8: // up
        qnode.move_base(is_all ? 'I' : 'i', liner, turn, curCar);
        break;
    case Qt::Key_9: //↗
        qnode.move_base(is_all ? 'O' : 'o', liner, turn, curCar);
        break;
    case Qt::Key_4: // left
        qnode.move_base(is_all ? 'J' : 'j', liner, turn, curCar);
        break;
    case Qt::Key_6: // right
        qnode.move_base(is_all ? 'L' : 'l', liner, turn, curCar);
        break;
    case Qt::Key_1: //↙
        qnode.move_base(is_all ? 'M' : 'm', liner, turn, curCar);
        break;
    case Qt::Key_2: //
        qnode.move_base(is_all ? '<' : ',', liner, turn, curCar);
        break;
    case Qt::Key_3: //
        qnode.move_base(is_all ? '>' : '.', liner, turn, curCar);
        break;
    case Qt::Key_0: // 0按键停车
        qnode.move_base('t', liner, turn, curCar);
        break;
    case Qt::Key_5:
        qnode.move_base(is_all ? 'k' : 'K', liner, turn, curCar);
        break;
    }
}

//滑动条处理槽函数
void MainWindow::on_Slider_raw_valueChanged(int v)
{
    ui.label_raw->setText(QString::number(v));
}
//滑动条处理槽函数
void MainWindow::on_Slider_linear_valueChanged(int v)
{
    ui.label_linear->setText(QString::number(v));
}
//快捷指令删除按钮
void MainWindow::quick_cmd_remove()
{
    QTreeWidgetItem* curr = ui.treeWidget_quick_cmd->currentItem();
    //没有选择节点
    if (curr == NULL)
        return;
    //获取父节点
    QTreeWidgetItem* parent = curr->parent();
    //如果当前节点就为父节点
    if (parent == NULL) {
        ui.treeWidget_quick_cmd->takeTopLevelItem(
            ui.treeWidget_quick_cmd->indexOfTopLevelItem(curr));
        delete curr;
    } else {
        ui.treeWidget_quick_cmd->takeTopLevelItem(
            ui.treeWidget_quick_cmd->indexOfTopLevelItem(parent));
        delete parent;
    }
}
//快捷指令添加按钮
void MainWindow::quick_cmd_add()
{
    QWidget* w = new QWidget;
    //阻塞其他窗体
    w->setWindowModality(Qt::ApplicationModal);
    QLabel* name = new QLabel;
    name->setText("名称:");
    QLabel* content = new QLabel;
    content->setText("脚本:");
    QLineEdit* name_val = new QLineEdit;
    QTextEdit* shell_val = new QTextEdit;
    QPushButton* ok_btn = new QPushButton;
    ok_btn->setText("ok");
    ok_btn->setIcon(QIcon("://images/ok.png"));
    QPushButton* cancel_btn = new QPushButton;
    cancel_btn->setText("cancel");
    cancel_btn->setIcon(QIcon("://images/false.png"));
    QHBoxLayout* lay1 = new QHBoxLayout;
    lay1->addWidget(name);
    lay1->addWidget(name_val);
    QHBoxLayout* lay2 = new QHBoxLayout;
    lay2->addWidget(content);
    lay2->addWidget(shell_val);
    QHBoxLayout* lay3 = new QHBoxLayout;
    lay3->addWidget(ok_btn);
    lay3->addWidget(cancel_btn);
    QVBoxLayout* v1 = new QVBoxLayout;
    v1->addLayout(lay1);
    v1->addLayout(lay2);
    v1->addLayout(lay3);

    w->setLayout(v1);
    w->show();

    connect(ok_btn, &QPushButton::clicked, [this, w, name_val, shell_val] {
        this->add_quick_cmd(name_val->text(), shell_val->toPlainText());
        w->close();
    });
}

//向treeWidget添加快捷指令
void MainWindow::add_quick_cmd(QString name, QString val)
{
    if (name == "")
        return;
    QTreeWidgetItem* head = new QTreeWidgetItem(QStringList() << name);
    this->ui.treeWidget_quick_cmd->addTopLevelItem(head);
    QCheckBox* check = new QCheckBox;
    //记录父子关系
    this->widget_to_parentItem_map[check] = head;
    //连接checkbox选中的槽函数
    connect(check, SIGNAL(stateChanged(int)), this,
        SLOT(quick_cmds_check_change(int)));
    this->ui.treeWidget_quick_cmd->setItemWidget(head, 1, check);
    QTreeWidgetItem* shell_content = new QTreeWidgetItem(QStringList() << "shell");
    QTextEdit* shell_val = new QTextEdit;
    shell_val->setMaximumWidth(150);
    shell_val->setMaximumHeight(40);
    head->addChild(shell_content);
    shell_val->setText(val);
    this->ui.treeWidget_quick_cmd->setItemWidget(shell_content, 1, shell_val);
}
//快捷指令按钮处理的函数
void MainWindow::quick_cmds_check_change(int state)
{
    QCheckBox* check = qobject_cast<QCheckBox*>(sender());
    QTreeWidgetItem* parent = widget_to_parentItem_map[check];
    QString bash = ((QTextEdit*)ui.treeWidget_quick_cmd->itemWidget(parent->child(0), 1))
                       ->toPlainText();
    bool is_checked = state > 1 ? true : false;
    if (is_checked) {
        quick_cmd = new QProcess;
        quick_cmd->start("bash");
        qDebug() << bash;
        quick_cmd->write(bash.toLocal8Bit() + '\n');
        connect(quick_cmd, SIGNAL(readyReadStandardOutput()), this,
            SLOT(cmd_output()));
        connect(quick_cmd, SIGNAL(readyReadStandardError()), this,
            SLOT(cmd_error_output()));
    } else {
    }
}
//执行一些命令的回显
void MainWindow::cmd_output()
{
    ui.cmd_output->append(quick_cmd->readAllStandardOutput());
}
//执行一些命令的错误回显
void MainWindow::cmd_error_output()
{
    ui.cmd_output->append("<font color=\"#FF0000\">" + quick_cmd->readAllStandardError() + "</font> ");
}

//析构函数
MainWindow::~MainWindow()
{
    if (base_cmd) {
        delete base_cmd;
        base_cmd = NULL;
    }
    if (map_rviz) {
        delete map_rviz;
        map_rviz = NULL;
    }
}

/*****************************************************************************
** Implementation [Slots]
*****************************************************************************/

void MainWindow::showNoMasterMessage()
{
    QMessageBox msgBox;
    msgBox.setText("Couldn't find the ros master.");
    msgBox.exec();
    close();
}

/*
 * These triggers whenever the button is clicked, regardless of whether it
 * is already checked or not.
 */

void MainWindow::on_button_connect_clicked(bool check)
{
    //如果使用环境变量
    if (ui.checkbox_use_environment->isChecked()) {
        if (!qnode.init()) {
            // showNoMasterMessage();
            QMessageBox::warning(NULL, "失败",
                "连接ROS Master失败！请检查你的网络或连接字符串！",
                QMessageBox::Yes, QMessageBox::Yes);
            ui.label_robot_staue_img->setPixmap(
                QPixmap::fromImage(QImage("://images/offline.png")));
            ui.label_statue_text->setStyleSheet("color:red;");
            ui.label_statue_text->setText("离线");
        } else {
            //            //初始化rviz
            //            initRviz();
            ros_states = true;
            ui.button_connect->setEnabled(false);
            ui.disconnect->setEnabled(true);
            ui.label_robot_staue_img->setPixmap(
                QPixmap::fromImage(QImage("://images/online.png")));
            ui.label_statue_text->setStyleSheet("color:green;");
            ui.label_statue_text->setText("在线");
            //初始化视频订阅的显示
            initVideos();
            //显示话题列表
            initTopicList();
            //rviz消息显示
            initRvizPanel();
            //刷新控制页
            ui.tabWidget->setCurrentIndex(1);
            ui.tabWidget->setCurrentIndex(0);
        }
    }
    //如果不使用环境变量
    else {
        if (!qnode.init(ui.line_edit_master->text().toStdString(),
                ui.line_edit_host->text().toStdString())) {
            QMessageBox::warning(NULL, "失败",
                "连接ROS Master失败！请检查你的网络或连接字符串！",
                QMessageBox::Yes, QMessageBox::Yes);
            ui.label_robot_staue_img->setPixmap(
                QPixmap::fromImage(QImage("://images/offline.png")));
            ui.label_statue_text->setStyleSheet("color:red;");
            ui.label_statue_text->setText("离线");
            // ui.treeWidget_rviz->setEnabled(false);
            // showNoMasterMessage();
        } else {
            ros_states = true;
            ui.button_connect->setEnabled(false);
            ui.disconnect->setEnabled(true);
            ui.line_edit_master->setReadOnly(true);
            ui.line_edit_host->setReadOnly(true);
            ui.line_edit_topic->setReadOnly(true);
            ui.label_robot_staue_img->setPixmap(
                QPixmap::fromImage(QImage("://images/online.png")));
            ui.label_statue_text->setStyleSheet("color:green;");
            ui.label_statue_text->setText("在线");
            //初始化视频订阅的显示
            initVideos();
            //显示话题列表
            initTopicList();
            //rviz消息显示
            initRvizPanel();
            //刷新控制页
            ui.tabWidget->setCurrentIndex(1);
            ui.tabWidget->setCurrentIndex(0);
        }
    }
}
void MainWindow::initTopicList()
{
    ui.topic_listWidget_3->addItem(QString("%1   (%2)").arg("Name", "Type"));
    QMap<QString, QString> topic_list = qnode.get_topic_list();
    for (QMap<QString, QString>::iterator iter = topic_list.begin();
         iter != topic_list.end(); iter++) {
        ui.topic_listWidget_3->addItem(
            QString("%1   (%2)").arg(iter.key(), iter.value()));
    }
}
//当ros与master的连接断开时
void MainWindow::slot_rosShutdown()
{
    ui.label_robot_staue_img->setPixmap(
        QPixmap::fromImage(QImage("://images/offline.png")));
    ui.label_statue_text->setStyleSheet("color:red;");
    ui.label_statue_text->setText("离线");
    ui.button_connect->setEnabled(true);
    ui.line_edit_master->setReadOnly(false);
    ui.line_edit_host->setReadOnly(false);
    ui.line_edit_topic->setReadOnly(false);
}
void MainWindow::slot_power(float p)
{
    //    qDebug()<<" POWER~~~~~~~~~~~~~~~!";
    double power = power_min + (power_max - power_min) * p / 100;
    ui.label_power->setText(QString::number(power).mid(0, 5) + "V");
    //    double n=(p-10)/1.5;
    //    int value=n*100;
    double n = p;
    double value = n; //插入的p是百分比；
    ui.progressBar->setValue(value > 100 ? 100 : value);
    //当电量过低时发出提示
    if (value <= 20) {
        ui.progressBar->setStyleSheet(
            "QProgressBar::chunk {background-color: red;width: 20px;} QProgressBar "
            "{border: 2px solid grey;border-radius: 5px;text-align: center;}");
        // QMessageBox::warning(NULL, "电量不足", "电量不足，请及时充电！",
        // QMessageBox::Yes , QMessageBox::Yes);
    } else {
        ui.progressBar->setStyleSheet(
            "QProgressBar {border: 2px solid grey;border-radius: 5px;text-align: "
            "center;}");
    }
}
void MainWindow::slot_speed_x(double x)
{
    if (x >= 0)
        ui.label_dir_x->setText("正向");
    else
        ui.label_dir_x->setText("反向");

    //        m_DashBoard_x->setValue(abs(x * 100));
    //        m_DashBoard_x_2->setValue(abs(x * 100));
    ui.widget_speed_x_2->setValue(abs(x * 100));
}
void MainWindow::slot_speed_y(double x)
{
    if (x >= 0)
        ui.label_dir_y->setText("正向");
    else
        ui.label_dir_y->setText("反向");
    //    m_DashBoard_y->setValue(abs(x * 100));
    //    m_DashBoard_y_2->setValue(abs(x * 100));
    ui.widget_speed_y_2->setValue(abs(x * 100));
}

void MainWindow::slot_flag_err(char flag)
{
    ui.label_error->setText(QString::number(flag));
    qDebug() << "error_flag";
}

void MainWindow::on_checkbox_use_environment_stateChanged(int state)
{
    bool enabled;
    if (state == 0) {
        enabled = true;
    } else {
        enabled = false;
    }
    ui.line_edit_master->setEnabled(enabled);
    ui.line_edit_host->setEnabled(enabled);
    // ui.line_edit_topic->setEnabled(enabled);
}

/*****************************************************************************
** Implemenation [Slots][manually connected]
*****************************************************************************/

/**
 * This function is signalled by the underlying model. When the model changes,
 * this will drop the cursor down to the last line in the QListview to ensure
 * the user can always see the latest log message.
 */
void MainWindow::updateLoggingView() { ui.view_logging_3->scrollToBottom(); }

/*****************************************************************************
** Implementation [Menu]
*****************************************************************************/

void MainWindow::on_actionAbout_triggered()
{
    // QMessageBox::about(this, tr("About ..."),tr("<h2>PACKAGE_NAME Test Program
    // 0.10</h2><p>Copyright Yujin Robot</p><p>This package needs an about
    // description.</p>"));
}

/*****************************************************************************
** Implementation [Configuration]
*****************************************************************************/

void MainWindow::ReadSettings()
{
    //    qDebug() << "我进入到 readsetting 了!!!!";

    QSettings settings("Qt-Ros Package", "cyrobot_monitor");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
    QString master_url = settings.value("master_url", QString("http://127.0.0.1:11311/"))
                             .toString();
    QString host_url = settings.value("host_url", QString("127.0.0.1")).toString();
    // QString topic_name = settings.value("topic_name",
    // QString("/chatter")).toString();
    ui.line_edit_master->setText(master_url);
    ui.line_edit_host->setText(host_url);
    // ui.line_edit_topic->setText(topic_name);
    bool remember = settings.value("remember_settings", false).toBool();
    ui.checkbox_remember_settings->setChecked(remember);
    bool checked = settings.value("use_environment_variables", false).toBool();
    ui.checkbox_use_environment->setChecked(checked);
    if (checked) {
        ui.line_edit_master->setEnabled(false);
        ui.line_edit_host->setEnabled(false);
        // ui.line_edit_topic->setEnabled(false);
    }

    QSettings return_pos("return-position", "cyrobot_monitor");
    ui.label_return_x->setText(return_pos.value("x", QString("0")).toString());
    ui.label_return_y->setText(return_pos.value("y", QString("0")).toString());
    ui.label_return_z->setText(return_pos.value("z", QString("0")).toString());
    ui.label_return_w->setText(return_pos.value("w", QString("0")).toString());

    //读取快捷指令的setting
    QSettings quick_setting("quick_setting", "cyrobot_monitor");
    QStringList ch_key = quick_setting.childKeys();
    for (auto c : ch_key) {
        add_quick_cmd(c, quick_setting.value(c, QString("")).toString());
    }

    // read 64个videowidget的每4个按钮的状态 0 - 63
    QSettings video_btn_setting("btnlist", "cyrobot_monitor");
    for (int i = 0; i < ui.test_video->videoCount; i++) {
        for (int j = 0; j < 4; j++) {
            QString key_btn_name = "button" + QString::number(i) + QString::number(j);
            if (j == 3) {
                ui.test_video->widgets[i]->rotate_id = video_btn_setting.value(key_btn_name).toInt();
            } else {
                ui.test_video->widgets[i]->video_ischecked[j] = video_btn_setting.value(key_btn_name).toBool();
            }
        }
    }

    // read 64个videowidget的每4个按钮的状态 0 - 63
    //     for(int i = 0;i < ui.test_video->videoCount;i++){
    //         QString key_list_name = "btnlist" + QString::number(i);
    //         video[i] = new QSettings(key_list_name,"cyrobot_monitor");
    //        for(int j = 0;j < 4; j++){
    //            QString key_btn_name = "button" + QString::number(j);
    //             = video[i]->value(key_btn_name).toBool();
    //        }
    //    }

    qDebug() << "status(第一个窗后第二个按钮) :  "
             << video_btn_setting.value("button01").toBool();

    QSettings topic_setting("topic_setting", "cyrobot_monitor");
    power_min = topic_setting.value("power_min", "min").toDouble();
    power_max = topic_setting.value("power_max", "max").toDouble();
}

void MainWindow::WriteSettings()
{
    QSettings settings("Qt-Ros Package", "cyrobot_monitor");
    settings.setValue("master_url", ui.line_edit_master->text());
    settings.setValue("host_url", ui.line_edit_host->text());
    // settings.setValue("topic_name",ui.line_edit_topic->text());
    settings.setValue("use_environment_variables",
        QVariant(ui.checkbox_use_environment->isChecked()));
    settings.setValue("geometry", saveGeometry());
    // settings.setValue("windowState", saveState());
    settings.setValue("remember_settings",
        QVariant(ui.checkbox_remember_settings->isChecked()));

    //存下快捷指令的setting
    QSettings quick_setting("quick_setting", "cyrobot_monitor");
    quick_setting.clear();
    for (int i = 0; i < ui.treeWidget_quick_cmd->topLevelItemCount(); i++) {
        QTreeWidgetItem* top = ui.treeWidget_quick_cmd->topLevelItem(i);
        QTextEdit* cmd_val = (QTextEdit*)ui.treeWidget_quick_cmd->itemWidget(top->child(0), 1);
        quick_setting.setValue(top->text(0), cmd_val->toPlainText());
    }

    //记录64个videowidget的每4个按钮的状态 0 - 63
    QSettings video_btn_setting("btnlist", "cyrobot_monitor");
    for (int i = 0; i < ui.test_video->videoCount; i++) {
        for (int j = 0; j < 4; j++) {
            QString key_btn_name = "button" + QString::number(i) + QString::number(j);
            if (j == 3) {
                video_btn_setting.setValue(
                    key_btn_name,
                    QString::number(ui.test_video->widgets[i]->rotate_id));
            } else {
                video_btn_setting.setValue(
                    key_btn_name, ui.test_video->widgets[i]->video_ischecked[j]);
            }
        }
    }

    //    for(int i = 0;i < ui.test_video->videoCount;i++){
    //        QString key_list_name = "btnlist" + QString::number(i);
    //        video[i] = new QSettings(key_list_name,"cyrobot_monitor");
    //        qDebug() << video[i]->fileName();
    //        for(int j = 0;j < 4; j++){
    //            QString key_btn_name = "button" + QString::number(j);
    //            video[i]->setValue(key_btn_name,ui.test_video->widgets[i]->video_ischecked[j]);
    //        }
    //    }
    qDebug() << "结束后我记录下了(第一个窗后第二个按钮) status:  "
             << video_btn_setting
                    .value("btnlist01",
                        ui.test_video->widgets[0]->video_ischecked[1])
                    .toBool();

    //<220416调试：关闭窗口时崩溃
    //    QSettings videoSetting("video_setting", "cyrobot_monitor");
    //    for (int i = 0; i < CARNUM; i++) {
    //        char str[100];
    //        sprintf(str, "horizontal%d", i);
    //        videoSetting.setValue(str, qnode.videoSet[i].horMir);
    //        sprintf(str, "vetical%d", i);
    //        videoSetting.setValue(str, qnode.videoSet[i].verMir);
    //        sprintf(str, "encodeId%d", i);
    //        videoSetting.setValue(str, enCombox[i]->currentIndex());
    //        sprintf(str, "rotate%d", i);
    //        videoSetting.setValue(str, qnode.videoSet[i].rotate);
    //    }
    //220416调试：关闭窗口时崩溃>

    slot_formation_save_click();
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    //关闭时释放内存
    this->setAttribute(Qt::WA_DeleteOnClose);
    WriteSettings();
    QMainWindow::closeEvent(event);
}

void MainWindow::slot_leader_choose(QAbstractButton* button)
{
    switch (gLeaderId->checkedId()) {
    case 0:
        f_msg.leader_id = 0;
        break;
    case 1:
        f_msg.leader_id = 1;
        break;
    case 2:
        f_msg.leader_id = 2;
        break;
    case 3:
        f_msg.leader_id = 3;
        break;
    case 4:
        f_msg.leader_id = 4;
        break;
    }
    //    initVideos();
}
void MainWindow::slot_follower_choose(QAbstractButton* button)
{
    qDebug() << QString("Clicked Button:%1").arg(button->text());

    //遍历按钮，获取选中状态
    QList<QAbstractButton*> list = gFollowerId->buttons();

    short int getId[10];
    short int count = 0;
    foreach (QAbstractButton* pCheckBox, list) {
        int a = gFollowerId->id(pCheckBox);
        if (pCheckBox->isChecked() && a != f_msg.leader_id) {
            getId[count++] = a - 1;
            qDebug() << QString("Button id: %1").arg(a);
        }
    }

    std::vector<short int> array(getId, getId + count);
    f_msg.follower_id = array;
    f_msg.follower_num = count;
    qDebug() << QString("fNum:%1").arg(f_msg.follower_id.size());
    qDebug() << QString("fNum:%1").arg(f_msg.follower_num);

    getId[count++] = f_msg.leader_id;
    std::vector<short int> array1(getId, getId + count);
    r_msg.robot_num = count;
    r_msg.robot_id = array1;
    qDebug() << QString("reconNum:%1").arg(r_msg.robot_id.size());
    qDebug() << QString("reconNum:%1").arg(r_msg.robot_num);

    // qDebug() << QString("distance:%1").arg(ui.spaced->value());
    // formation_task_pub.publish(f_msg);
    //    initVideos();
}

void MainWindow::slot_horMirror_set(QAbstractButton* button)
{
    char horm_id = horMirror->id(button);
    qnode.videoSet[horm_id].horMir = button->isChecked();

    qDebug() << "horizontal mirrored check Id:" << horMirror->id(button);
    qDebug() << "horizontal mirrored check states:" << button->isChecked();
}

void MainWindow::slot_verMirror_set(QAbstractButton* button)
{
    char verm_id = verMirror->id(button);
    qnode.videoSet[verm_id].verMir = button->isChecked();
    qDebug() << "vertical mirrored check Id:" << verMirror->id(button);
    qDebug() << "vertical mirrored check states:" << button->isChecked();
}

//旋转图像
void MainWindow::slot_rotate(QAbstractButton* button)
{
    char rotateId = rotateLabel->id(button);
    char a = (qnode.videoSet[rotateId].rotate + 1) % 4;
    qnode.videoSet[rotateId].rotate = a;
    switch (a) {
    case ROTATE_0:
        button->setText("0°");
        break;
    case ROTATE_90:
        button->setText("90°");
        break;
    case ROTATE_180:
        button->setText("180°");
        break;
    case ROTATE_270:
        button->setText("270°");
        break;
    }
}

void MainWindow::initData()
{
    // rviz数据初始化
    m_mapRvizDisplays.insert("Axes", RVIZ_DISPLAY_AXES);
    m_mapRvizDisplays.insert("Camera", RVIZ_DISPLAY_CAMERA);
    m_mapRvizDisplays.insert("DepthCloud", RVIZ_DISPLAY_DEPTHCLOUD);
    m_mapRvizDisplays.insert("Effort", RVIZ_DISPLAY_EFFORT);
    m_mapRvizDisplays.insert("FluidPressure", RVIZ_DISPLAY_FLUIDPRESSURE);
    m_mapRvizDisplays.insert("Grid", RVIZ_DISPLAY_GRID);
    m_mapRvizDisplays.insert("GridCells", RVIZ_DISPLAY_GRIDCELLS);
    m_mapRvizDisplays.insert("Group", RVIZ_DISPLAY_GROUP);
    m_mapRvizDisplays.insert("Illuminance", RVIZ_DISPLAY_ILLUMINANCE);
    m_mapRvizDisplays.insert("Image", RVIZ_DISPLAY_IMAGE);
    m_mapRvizDisplays.insert("InterativerMarker", RVIZ_DISPLAY_INTERATIVEMARKER);
    m_mapRvizDisplays.insert("LaserScan", RVIZ_DISPLAY_LASERSCAN);
    m_mapRvizDisplays.insert("Map", RVIZ_DISPLAY_MAP);
    m_mapRvizDisplays.insert("Marker", RVIZ_DISPLAY_MARKER);
    m_mapRvizDisplays.insert("MarkerArray", RVIZ_DISPLAY_MARKERARRAY);
    m_mapRvizDisplays.insert("Odometry", RVIZ_DISPLAY_ODOMETRY);
    m_mapRvizDisplays.insert("Path", RVIZ_DISPLAY_PATH);
    m_mapRvizDisplays.insert("PointCloud", RVIZ_DISPLAY_POINTCLOUD);
    m_mapRvizDisplays.insert("PointCloud2", RVIZ_DISPLAY_POINTCLOUD2);
    m_mapRvizDisplays.insert("PointStamped", RVIZ_DISPLAY_POINTSTAMPED);
    m_mapRvizDisplays.insert("Polygon", RVIZ_DISPLAY_POLYGON);
    m_mapRvizDisplays.insert("Pose", RVIZ_DISPLAY_POSE);
    m_mapRvizDisplays.insert("PoseArray", RVIZ_DISPLAY_POSEARRAY);
    m_mapRvizDisplays.insert("PoseWithCovariance",
        RVIZ_DISPLAY_POSEWITHCOVARIANCE);
    m_mapRvizDisplays.insert("Range", RVIZ_DISPLAY_RANGE);
    m_mapRvizDisplays.insert("RelativeHumidity", RVIZ_DISPLAY_RELATIVEHUMIDITY);
    m_mapRvizDisplays.insert("RobotModel", RVIZ_DISPLAY_ROBOTMODEL);
    m_mapRvizDisplays.insert("TF", RVIZ_DISPLAY_TF);
    m_mapRvizDisplays.insert("Temperature", RVIZ_DISPLAY_TEMPERATURE);
    m_mapRvizDisplays.insert("WrenchStamped", RVIZ_DISPLAY_WRENCHSTAMPED);

    QSettings video_topic_setting("video_topic", "cyrobot_monitor");
    QStringList names = video_topic_setting.value("names").toStringList();
    QStringList topics = video_topic_setting.value("topics").toStringList();

    int num = names.size();
    for (int i = 0; i < num; i++) {
        ui.car_control->setItemText(i, names[i]);
    }
}

void MainWindow::slot_formation_save_click()
{
    // int distance[5];
    QSettings fInfo_setting("formationInfo", "cyrobot_monitor");
}

void MainWindow::slot_send_formation()
{
    char a = gTaskChoose->checkedId(); //选择发布的任务
    if (!qnode.isWork)
        return;

    if (f_msg.goal.position.x == f_msg.goal.position.y && f_msg.goal.position.y == f_msg.goal.position.z && !f_msg.goal.position.x)
        QMessageBox::warning(NULL, "失败", "请先在rviz设置目标点！",
            QMessageBox::Yes, QMessageBox::Yes);
    qnode.formationPub(a);
    initVideos();
}

void MainWindow::RvizGetModel(QAbstractItemModel* model)
{
    m_modelRvizDisplay = model;
    ui.treeView_rviz->setModel(model);
}

void MainWindow::refreashTopicList()
{
    ui.topic_listWidget_3->clear();
    initTopicList();
}

void MainWindow::inform(QString strdata)
{
    QMessageBox m_r;
    m_r.setWindowTitle("提示");
    m_r.setText(strdata);
    m_r.exec();
}

bool MainWindow::AskInform(QString strdata)
{
    QMessageBox m_r;

    m_r.setWindowTitle("提示");
    m_r.setText(strdata);
    m_r.addButton(tr("确认"), QMessageBox::ActionRole);
    m_r.addButton(tr("取消"), QMessageBox::ActionRole);

    int isok = m_r.exec();
    if (isok == 1) {
        return false;
    } else {
        return true;
    }
}

void MainWindow::on_switchRviz_changed(bool bChecked)
{
    qDebug() << "Switch States:" << bChecked;
    if (bChecked) //当rviz开启时
    {
        if (ros_states && !rviz_states) {
            rviz_states = true;
            initRviz(); //初始化rviz
        } else if (!ros_states)
            QMessageBox::warning(NULL, "失败", "请先连接ROS Master！",
                QMessageBox::Yes,
                QMessageBox::Yes); //警告信息
    } else if (rviz_states) //当rviz开关关闭并且已经打开了rviz
    {
        //关闭rviz
        map_rviz->quit();
        delete map_rviz;
        map_rviz = nullptr;
        rviz_states = false;
        qDebug() << "rviz 已关闭";
    }
}

void MainWindow::on_comboBox_v0_2_currentIndexChanged(int index)
{
    qnode.videoSet[0].id = index;
}

void MainWindow::on_comboBox_v1_2_currentIndexChanged(int index)
{
    qnode.videoSet[1].id = index;
}

void MainWindow::on_comboBox_v2_2_currentIndexChanged(int index)
{
    qnode.videoSet[2].id = index;
}

void MainWindow::on_comboBox_v3_3_currentIndexChanged(int index)
{
    qnode.videoSet[3].id = index;
}

void MainWindow::on_comboBox_v4_2_currentIndexChanged(int index)
{
    qnode.videoSet[4].id = index;
}

void MainWindow::addJoyStick(QVBoxLayout* layout_)
{
    //    QQuickWidget* m_quickWidget = new QQuickWidget();

    //    m_quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    //    //设置窗口大小为父窗口大小 m_quickWidget->setFocus();
    //    m_quickWidget->setSource(QUrl::fromLocalFile("://qml/virtual_joystick.qml"));
    //    //加载qml资源
    //    //创建QVBoxLayout类，装载widget类
    //    //    layout_->addWidget(m_quickwidget);

    //    layout_->addWidget(m_quickWidget);

    QQuickView* view = new QQuickView();
    /* NB: We load the QML from a .qrc file becuase the Qt build step
       * that packages the final .app on Mac forgets to add the QML
       * if you reference it directly
       */
    view->setSource(QUrl::fromLocalFile("://qml/virtual_joystick.qml"));

    /* Enable transparent background on the QQuickView
   * Note that this currently does not work on Windows
   */
    //#ifndef _WIN32
    //    view->setClearBeforeRendering(true);
    //    view->setColor(QColor(Qt::transparent));
    //#endif

    //    // Attach to the 'mouse moved' signal
    auto* root = view->rootObject();

    QObject::connect(root, SIGNAL(joystick_moved(double, double)), //
        this, SLOT(joystick_draw(double, double)));

    // Create a container widget for the QQuickView
    QWidget* container = QWidget::createWindowContainer(view, this);
    container->setMinimumSize(160, 160);
    container->setMaximumSize(160, 160);
    container->setFocusPolicy(Qt::TabFocus);
    layout_->addWidget(container);
}

/**
 * @brief MainWindow::mouse_moved Called when the virtual joystick is moved
 * @param x Mouse x position
 * @param y Mouse y position
 */
void MainWindow::joystick_draw(double angle, double vel)
{
    qDebug() << angle << ", " << vel;
    if (qnode.isWork) //TODO
    {
        char curCar = ui.car_control->currentIndex();
        qnode.ackerman_control(vel, angle, curCar);
    }
}

void MainWindow::on_road_topic_changed()
{
    QSettings road_setting("road_topic", "cyrobot_monitor");
    road_setting.setValue("road/topic", ui.road_topic_edit->text());
}
void MainWindow::on_carpos_topic_changed()
{
    QSettings road_setting("road_topic", "cyrobot_monitor");
    road_setting.setValue("carpos/topic", ui.carpos_topic_edit->text());
}

void MainWindow::on_car_changed(int curCar)
{

    QString key("vel_type");
    QString num = QString::number(curCar);
    QSettings topic_setting("topic_setting", "cyrobot_monitor");

    int carType = topic_setting.value(key + num, 0).toInt();
    if (carType == 0) {
        qDebug("carType0");
        ui.gridLayout_arrow->setVisible(true);
        ui.verticalLayout_js->setVisible(false);
    }
    if (carType == 1) {
        qDebug("carType1");
        ui.gridLayout_arrow->setVisible(false);
        ui.verticalLayout_js->setVisible(true);
    }
}
} // namespace cyrobot_monitor

void cyrobot_monitor::MainWindow::on_pushButton_add_topic_clicked()
{
    addtopic_form->show();
}

void cyrobot_monitor::MainWindow::on_pushButton_rename_topic_clicked()
{
    if (ui.treeView_rviz->currentIndex().row() < 0) {
        inform("请选择Display后再执行此操作");
        return;
    }
    QString dlgTitle = "重命名";
    QString txtlabel = "请输入名字：";
    QString defaultInupt = m_sRvizDisplayChooseName_;
    QLineEdit::EchoMode echoMode = QLineEdit::Normal;
    bool ok = false;
    QString newname = QInputDialog::getText(this, dlgTitle, txtlabel, echoMode,
        defaultInupt, &ok);
    if (ok && !newname.isEmpty()) {
        if (newname != defaultInupt) {
            QString nosamename = JudgeDisplayNewName(newname);
            map_rviz->RenameDisplay(defaultInupt, nosamename);
            m_sRvizDisplayChooseName_ = nosamename;
            if (nosamename != newname) {
                inform("命名重复！命名已自动更改为" + nosamename);
            }
        }
    } else if (ok) {
        inform("输入内容为空，重命名失败");
    }
}

void cyrobot_monitor::MainWindow::on_pushButton_remove_topic_clicked()
{
    if (ui.treeView_rviz->currentIndex().row() >= 0) {
        m_sRvizDisplayChooseName_ = ui.treeView_rviz->currentIndex().data().value<QString>();
        map_rviz->RemoveDisplay(m_sRvizDisplayChooseName_);
        if (ui.treeView_rviz->currentIndex().row() >= 0) {
            on_treeView_rviz_clicked(ui.treeView_rviz->currentIndex());
        } else {
            m_sRvizDisplayChooseName_.clear();
        }
    } else {
        inform("请选择Display后再执行此操作");
    }
}

void cyrobot_monitor::MainWindow::on_treeView_rviz_clicked(
    const QModelIndex& index)
{
    m_sRvizDisplayChooseName_ = index.data().value<QString>();
    if (index.parent().row() == -1) // Display 的根节点
    {
        if (index.row() > 1) {
            ui.pushButton_remove_topic->setEnabled(true);
            ui.pushButton_rename_topic->setEnabled(true);
        } else {
            ui.pushButton_remove_topic->setEnabled(false);
            ui.pushButton_rename_topic->setEnabled(false);
        }
    } else {
        ui.pushButton_remove_topic->setEnabled(false);
        ui.pushButton_rename_topic->setEnabled(false);
    }
}

void cyrobot_monitor::MainWindow::on_disconnect_clicked()
{
    if (rviz_states) {
        map_rviz->quit();
        delete map_rviz;
        map_rviz = nullptr;
        rviz_states = false;
    }

    deinitRvizPanel();

    qnode.disinit();
    ui.pushButton_add_topic->setEnabled(false);
    ui.pushButton_remove_topic->setEnabled(false);
    ui.pushButton_rename_topic->setEnabled(false);
    // ui.pushButton_rvizReadDisplaySet->setEnabled(false);
    // ui.pushButton_rvizSaveDisplaySet->setEnabled(false);
    // ui.label_rvizShow->show();
    ui.disconnect->setEnabled(false);
    ui.button_connect->setEnabled(true);
}
