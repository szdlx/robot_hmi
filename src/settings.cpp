#include "../include/cyrobot_monitor/settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::Settings)
{
    ui->setupUi(this);

    //rviztopic设置 TODO
    QSettings rviz_setting("rviz_topic", "cyrobot_monitor");
    ui->setting_e1->setText(rviz_setting.value("rviz/Image/topic", "").toString());
    ui->setting_e2->setText(rviz_setting.value("rviz/PC2Lidar/topic", "").toString());
    ui->setting_e3->setText(rviz_setting.value("rviz/PC2Colored/topic", "").toString());
    ui->setting_e4->setText(rviz_setting.value("rviz/GridMap/topic", "").toString());
    ui->setting_e1_2->setText(rviz_setting.value("rviz/Image/fixedframe", "").toString());
    ui->setting_e2_2->setText(rviz_setting.value("rviz/PC2Lidar/fixedframe", "").toString());
    ui->setting_e3_2->setText(rviz_setting.value("rviz/PC2Colored/fixedframe", "").toString());
    ui->setting_e4_2->setText(rviz_setting.value("rviz/GridMap/fixedframe", "").toString());

    QSettings video_topic_setting("video_topic", "cyrobot_monitor");
    QStringList names = video_topic_setting.value("names").toStringList();
    QStringList topics = video_topic_setting.value("topics").toStringList();
    if (names.size() == 5) {
        ui->video0_name_set->setText(names[0]);
        ui->video0_name_set_2->setText(names[1]);
        ui->video0_name_set_3->setText(names[2]);
        ui->video0_name_set_4->setText(names[3]);
        ui->video0_name_set_5->setText(names[4]);
    }
    if (topics.size() == 5) {
        ui->video0_topic_set->setText(topics[0]);
        ui->video0_topic_set_2->setText(topics[1]);
        ui->video0_topic_set_3->setText(topics[2]);
        ui->video0_topic_set_4->setText(topics[3]);
        ui->video0_topic_set_5->setText(topics[4]);
    }
    QSettings main_setting("topic_setting", "cyrobot_monitor");
    //car0
    ui->lineEdit_odm->setText(main_setting.value("topic_odom0", "raw_odom").toString());
    ui->lineEdit_vel->setText(main_setting.value("topic_vel0", "cmd_vel").toString());
    ui->msgType0->setCurrentIndex(main_setting.value("vel_type0", 0).toInt());
    //car1
    ui->lineEdit_odm_1->setText(main_setting.value("topic_odom1", "raw_odom1").toString());
    ui->lineEdit_vel_1->setText(main_setting.value("topic_vel1", "cmd_vel1").toString());
    ui->msgType1->setCurrentIndex(main_setting.value("vel_type1", 0).toInt());
    //car2
    ui->lineEdit_odm_2->setText(main_setting.value("topic_odom2", "raw_odom2").toString());
    ui->lineEdit_vel_2->setText(main_setting.value("topic_vel2", "cmd_vel2").toString());
    ui->msgType2->setCurrentIndex(main_setting.value("vel_type2", 0).toInt());
    //car3
    ui->lineEdit_odm_3->setText(main_setting.value("topic_odom3", "raw_odom3").toString());
    ui->lineEdit_vel_3->setText(main_setting.value("topic_vel3", "cmd_vel3").toString());
    ui->msgType3->setCurrentIndex(main_setting.value("vel_type3", 0).toInt());
    //car4
    ui->lineEdit_odm_4->setText(main_setting.value("topic_odom4", "raw_odom4").toString());
    ui->lineEdit_vel_4->setText(main_setting.value("topic_vel4", "cmd_vel4").toString());
    ui->msgType4->setCurrentIndex(main_setting.value("vel_type4", 0).toInt());

    ui->lineEdit_power->setText(main_setting.value("topic_power", "power").toString());
    ui->lineEdit_power_min->setText(main_setting.value("power_min", "min").toString());
    ui->lineEdit_power_max->setText(main_setting.value("power_max", "max").toString());

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(slot_ok_btn_click()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(slot_cancel_btn_click()));
    //    QWidget
    //    ui->scrollArea->addScrollBarWidget();
}

void Settings::slot_ok_btn_click()
{

    //rviztopic设置 TODO
    QSettings rviz_setting("rviz_topic", "cyrobot_monitor");
    rviz_setting.setValue("rviz/Image/topic", ui->setting_e1->text());
    rviz_setting.setValue("rviz/PC2Lidar/topic", ui->setting_e2->text());
    rviz_setting.setValue("rviz/PC2Colored/topic", ui->setting_e3->text());
    rviz_setting.setValue("rviz/GridMap/topic", ui->setting_e4->text());
    rviz_setting.setValue("rviz/Image/fixedframe", ui->setting_e1_2->text());
    rviz_setting.setValue("rviz/PC2Lidar/fixedframe", ui->setting_e2_2->text());
    rviz_setting.setValue("rviz/PC2Colored/fixedframe", ui->setting_e3_2->text());
    rviz_setting.setValue("rviz/GridMap/fixedframe", ui->setting_e4_2->text());
    emit rviz_topic_changed();

    QSettings main_setting("topic_setting", "cyrobot_monitor");
    //car0
    main_setting.setValue("topic_odom0", ui->lineEdit_odm->text()); //保存
    main_setting.setValue("topic_vel0", ui->lineEdit_vel->text()); //保存速度控制话题
    main_setting.setValue("vel_type0", ui->msgType0->currentIndex());

    //car1
    main_setting.setValue("topic_odom1", ui->lineEdit_odm_1->text()); //保存
    main_setting.setValue("topic_vel1", ui->lineEdit_vel_1->text()); //保存速度控制话题
    main_setting.setValue("vel_type1", ui->msgType1->currentIndex());
    //car2
    main_setting.setValue("topic_odom2", ui->lineEdit_odm_2->text()); //保存
    main_setting.setValue("topic_vel2", ui->lineEdit_vel_2->text()); //保存速度控制话题
    main_setting.setValue("vel_type2", ui->msgType2->currentIndex());
    //car3
    main_setting.setValue("topic_odom3", ui->lineEdit_odm_3->text()); //保存
    main_setting.setValue("topic_vel3", ui->lineEdit_vel_3->text()); //保存速度控制话题
    main_setting.setValue("vel_type3", ui->msgType3->currentIndex());
    //car4
    main_setting.setValue("topic_odom4", ui->lineEdit_odm_4->text()); //保存
    main_setting.setValue("topic_vel4", ui->lineEdit_vel_4->text()); //保存速度控制话题
    main_setting.setValue("vel_type4", ui->msgType4->currentIndex());

    main_setting.setValue("topic_power", ui->lineEdit_power->text());
    main_setting.setValue("power_min", ui->lineEdit_power_min->text());
    main_setting.setValue("power_max", ui->lineEdit_power_max->text());

    QSettings video_topic_setting("video_topic", "cyrobot_monitor");
    QStringList name_data;
    QStringList topic_data;
    QStringList format_data;
    name_data.append(ui->video0_name_set->text());
    name_data.append(ui->video0_name_set_2->text());
    name_data.append(ui->video0_name_set_3->text());
    name_data.append(ui->video0_name_set_4->text());
    name_data.append(ui->video0_name_set_5->text());

    //    topic_data.append(QString::number(0) + ui->video0_topic_set->text());
    //    topic_data.append(QString::number(1) + ui->video0_topic_set_2->text());
    //    topic_data.append(QString::number(2) + ui->video0_topic_set_3->text());
    //    topic_data.append(QString::number(3) + ui->video0_topic_set_4->text());
    //    topic_data.append(QString::number(4) + ui->video0_topic_set_5->text());

    topic_data.append(ui->video0_topic_set->text());
    topic_data.append(ui->video0_topic_set_2->text());
    topic_data.append(ui->video0_topic_set_3->text());
    topic_data.append(ui->video0_topic_set_4->text());
    topic_data.append(ui->video0_topic_set_5->text());

    video_topic_setting.setValue("names", name_data);
    video_topic_setting.setValue("topics", topic_data);
    QMessageBox::critical(NULL, "保存成功！", "保存成功，部分功能需重启后生效！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

    emit button_name_changed();

    this->close();
}
void Settings::slot_cancel_btn_click()
{
    this->close();
}
Settings::~Settings()
{
    delete ui;
}
