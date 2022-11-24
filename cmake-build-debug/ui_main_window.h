/********************************************************************************
** Form generated from reading UI file 'main_window.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_WINDOW_H
#define UI_MAIN_WINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <SwitchButton.h>
#include "mypushbutton.h"
#include "plotpanel.h"
#include "rvizpanel.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindowDesign
{
public:
    QAction *action_Quit;
    QAction *action_Preferences;
    QAction *actionAbout;
    QAction *actionAbout_Qt;
    QAction *action1;
    QAction *action2;
    QAction *action;
    QAction *action_2;
    QAction *image_file;
    QAction *img_format;
    QAction *action_3;
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QWidget *info_widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLabel *label;
    QLabel *label_state;
    QLabel *label_link;
    QSpacerItem *horizontalSpacer;
    QLabel *label_7;
    QLabel *label_vel;
    QLabel *label_9;
    QLabel *label_11;
    QLabel *label_8;
    QLabel *label_rad;
    QLabel *label_13;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_5;
    QLabel *posqual;
    QLabel *headingqual;
    QLabel *gps_east;
    QLabel *gps_north;
    QLabel *gps_heading;
    QSpacerItem *horizontalSpacer_2;
    QProgressBar *progressBar;
    QLabel *label_18;
    QLabel *label_voltage;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *verticalSpacer_2;
    QWidget *verticalWidget_2;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_plat;
    QHBoxLayout *horizontalLayout_8;
    QGridLayout *gridLayout_15;
    MyPushButton *car0_connect;
    SwitchButton *car0_sw;
    QGridLayout *gridLayout_16;
    MyPushButton *outdoor;
    MyPushButton *indoor;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_14;
    QWidget *widget;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_16;
    QLabel *elevator_hight;
    QGridLayout *gridLayout_3;
    QPushButton *evelator_up;
    QGridLayout *gridLayout;
    QSlider *left_motor;
    QGridLayout *gridLayout_4;
    QPushButton *evelator_down;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_12;
    QLabel *label_17;
    QLabel *ang_val;
    QGridLayout *gridLayout_18;
    QPushButton *ang_up;
    QGridLayout *gridLayout_19;
    QSlider *ang_slide;
    QGridLayout *gridLayout_20;
    QPushButton *ang_down;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_13;
    QLabel *label_23;
    QLabel *vel_val;
    QGridLayout *gridLayout_21;
    QPushButton *vel_add;
    QGridLayout *gridLayout_22;
    QSlider *vel_slider;
    QGridLayout *gridLayout_23;
    QPushButton *vel_down;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_11;
    QLabel *label_19;
    SwitchButton *tmp_switch;
    QLabel *label_21;
    QComboBox *topics_vel;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *horizontalSpacer_4;
    QVBoxLayout *verticalLayout_9;
    QWidget *state_widget;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *topics_img;
    QPushButton *refresh;
    QSpacerItem *horizontalSpacer_5;
    QComboBox *select_format;
    QPushButton *snapshoot;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *verticalSpacer_5;
    RvizImage *rviz_img;
    QWidget *widget_plot;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *vertical_road;
    QWidget *param_widget;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *selected_path;
    QPushButton *track_path;
    QPushButton *stop_track;
    QSpacerItem *horizontalSpacer_14;
    QSpacerItem *space_path;
    PlotRoad *plot_road;
    QWidget *widget_5;
    QLabel *label_3;
    QPushButton *pushButton;
    QLabel *label_4;
    QLabel *label_6;
    QPushButton *pushButton_3;
    QPushButton *pushButton_5;
    QPushButton *slam;
    QPushButton *savemap;
    QPushButton *nav;
    QLineEdit *lineEdit;
    QWidget *rviz_widget;
    QHBoxLayout *horizontalLayout_10;
    QVBoxLayout *verticalLayout_6;
    QWidget *map_widget;
    QHBoxLayout *horizontalLayout_4;
    QComboBox *topics_laser;
    QPushButton *refresh_map;
    SwitchButton *map_switch;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *gmapping_btn;
    QPushButton *save_map;
    QPushButton *set_start;
    QPushButton *set_goal;
    QPushButton *screen_btn;
    QWidget *panel_widget;
    QHBoxLayout *horizontalLayout_13;
    RvizPanel *rviz_panel;
    QWidget *gridWidget;
    QGridLayout *grid_control;
    QWidget *omgControl;
    QSpacerItem *verticalSpacer;
    QWidget *horizontalWidget;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *menu_btn;
    QPushButton *img_path;
    QSpacerItem *horizontalSpacer_8;
    QLabel *label_10;
    QLineEdit *rosmasteruri;
    QCheckBox *local_ip;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *minumize;
    QPushButton *screen;
    QPushButton *shutdown;

    void setupUi(QMainWindow *MainWindowDesign)
    {
        if (MainWindowDesign->objectName().isEmpty())
            MainWindowDesign->setObjectName(QString::fromUtf8("MainWindowDesign"));
        MainWindowDesign->resize(1651, 915);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/robot_5.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindowDesign->setWindowIcon(icon);
        MainWindowDesign->setLocale(QLocale(QLocale::English, QLocale::Australia));
        action_Quit = new QAction(MainWindowDesign);
        action_Quit->setObjectName(QString::fromUtf8("action_Quit"));
        action_Quit->setShortcutContext(Qt::ApplicationShortcut);
        action_Preferences = new QAction(MainWindowDesign);
        action_Preferences->setObjectName(QString::fromUtf8("action_Preferences"));
        QFont font;
        action_Preferences->setFont(font);
        actionAbout = new QAction(MainWindowDesign);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionAbout_Qt = new QAction(MainWindowDesign);
        actionAbout_Qt->setObjectName(QString::fromUtf8("actionAbout_Qt"));
        action1 = new QAction(MainWindowDesign);
        action1->setObjectName(QString::fromUtf8("action1"));
        action2 = new QAction(MainWindowDesign);
        action2->setObjectName(QString::fromUtf8("action2"));
        action = new QAction(MainWindowDesign);
        action->setObjectName(QString::fromUtf8("action"));
        action_2 = new QAction(MainWindowDesign);
        action_2->setObjectName(QString::fromUtf8("action_2"));
        image_file = new QAction(MainWindowDesign);
        image_file->setObjectName(QString::fromUtf8("image_file"));
        img_format = new QAction(MainWindowDesign);
        img_format->setObjectName(QString::fromUtf8("img_format"));
        action_3 = new QAction(MainWindowDesign);
        action_3->setObjectName(QString::fromUtf8("action_3"));
        centralwidget = new QWidget(MainWindowDesign);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        info_widget = new QWidget(centralwidget);
        info_widget->setObjectName(QString::fromUtf8("info_widget"));
        horizontalLayout = new QHBoxLayout(info_widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(6, 0, -1, 0);
        label_2 = new QLabel(info_widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(32, 32));
        label_2->setMaximumSize(QSize(40, 40));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/images/robot3.png")));
        label_2->setScaledContents(true);

        horizontalLayout->addWidget(label_2);

        label = new QLabel(info_widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(0, 50));
        label->setMaximumSize(QSize(16777215, 50));

        horizontalLayout->addWidget(label);

        label_state = new QLabel(info_widget);
        label_state->setObjectName(QString::fromUtf8("label_state"));
        label_state->setLocale(QLocale(QLocale::Chinese, QLocale::China));

        horizontalLayout->addWidget(label_state);

        label_link = new QLabel(info_widget);
        label_link->setObjectName(QString::fromUtf8("label_link"));
        label_link->setMaximumSize(QSize(40, 40));
        label_link->setPixmap(QPixmap(QString::fromUtf8(":/images/offline1.png")));
        label_link->setScaledContents(true);

        horizontalLayout->addWidget(label_link);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_7 = new QLabel(info_widget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout->addWidget(label_7);

        label_vel = new QLabel(info_widget);
        label_vel->setObjectName(QString::fromUtf8("label_vel"));

        horizontalLayout->addWidget(label_vel);

        label_9 = new QLabel(info_widget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout->addWidget(label_9);

        label_11 = new QLabel(info_widget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setMinimumSize(QSize(10, 0));

        horizontalLayout->addWidget(label_11);

        label_8 = new QLabel(info_widget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout->addWidget(label_8);

        label_rad = new QLabel(info_widget);
        label_rad->setObjectName(QString::fromUtf8("label_rad"));

        horizontalLayout->addWidget(label_rad);

        label_13 = new QLabel(info_widget);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout->addWidget(label_13);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        label_5 = new QLabel(info_widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout->addWidget(label_5);

        posqual = new QLabel(info_widget);
        posqual->setObjectName(QString::fromUtf8("posqual"));

        horizontalLayout->addWidget(posqual);

        headingqual = new QLabel(info_widget);
        headingqual->setObjectName(QString::fromUtf8("headingqual"));

        horizontalLayout->addWidget(headingqual);

        gps_east = new QLabel(info_widget);
        gps_east->setObjectName(QString::fromUtf8("gps_east"));
        gps_east->setMinimumSize(QSize(60, 0));

        horizontalLayout->addWidget(gps_east);

        gps_north = new QLabel(info_widget);
        gps_north->setObjectName(QString::fromUtf8("gps_north"));
        gps_north->setMinimumSize(QSize(60, 0));

        horizontalLayout->addWidget(gps_north);

        gps_heading = new QLabel(info_widget);
        gps_heading->setObjectName(QString::fromUtf8("gps_heading"));
        gps_heading->setTextFormat(Qt::AutoText);

        horizontalLayout->addWidget(gps_heading);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        progressBar = new QProgressBar(info_widget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setMaximumSize(QSize(90, 16777215));
        progressBar->setStyleSheet(QString::fromUtf8("QProgressBar#progressBar\n"
"{\n"
"      border:none;   /*\346\227\240\350\276\271\346\241\206*/\n"
"      background:rgb(211, 215, 207);\n"
"      border-radius:5px;\n"
"      text-align:center;   /*\346\226\207\346\234\254\347\232\204\344\275\215\347\275\256*/\n"
"      color: rgb(229, 229, 229);  /*\346\226\207\346\234\254\351\242\234\350\211\262*/\n"
"}\n"
" \n"
"QProgressBar::chunk \n"
"{\n"
"      background-color:rgb(115, 210, 22);\n"
"      border-radius:4px;\n"
"}\n"
""));
        progressBar->setValue(59);

        horizontalLayout->addWidget(progressBar);

        label_18 = new QLabel(info_widget);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setPixmap(QPixmap(QString::fromUtf8(":/images/power-v.png")));

        horizontalLayout->addWidget(label_18);

        label_voltage = new QLabel(info_widget);
        label_voltage->setObjectName(QString::fromUtf8("label_voltage"));

        horizontalLayout->addWidget(label_voltage);


        gridLayout_2->addWidget(info_widget, 1, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        verticalSpacer_2 = new QSpacerItem(1, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        horizontalLayout_7->addItem(verticalSpacer_2);

        verticalWidget_2 = new QWidget(centralwidget);
        verticalWidget_2->setObjectName(QString::fromUtf8("verticalWidget_2"));
        verticalLayout_2 = new QVBoxLayout(verticalWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 6, -1);
        widget_plat = new QWidget(verticalWidget_2);
        widget_plat->setObjectName(QString::fromUtf8("widget_plat"));
        widget_plat->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_8 = new QHBoxLayout(widget_plat);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        gridLayout_15 = new QGridLayout();
        gridLayout_15->setObjectName(QString::fromUtf8("gridLayout_15"));
        car0_connect = new MyPushButton(widget_plat);
        car0_connect->setObjectName(QString::fromUtf8("car0_connect"));
        car0_connect->setMinimumSize(QSize(130, 70));
        car0_connect->setMaximumSize(QSize(160, 70));
        QFont font1;
        font1.setPointSize(15);
        font1.setBold(true);
        car0_connect->setFont(font1);
        car0_connect->setCheckable(true);
        car0_connect->setChecked(false);
        car0_connect->setAutoRepeat(true);
        car0_connect->setAutoExclusive(true);
        car0_connect->setFlat(true);

        gridLayout_15->addWidget(car0_connect, 0, 0, 1, 1);

        car0_sw = new SwitchButton(widget_plat);
        car0_sw->setObjectName(QString::fromUtf8("car0_sw"));
        car0_sw->setMinimumSize(QSize(0, 40));
        car0_sw->setMaximumSize(QSize(16777215, 60));

        gridLayout_15->addWidget(car0_sw, 1, 0, 1, 1);


        horizontalLayout_8->addLayout(gridLayout_15);

        gridLayout_16 = new QGridLayout();
        gridLayout_16->setObjectName(QString::fromUtf8("gridLayout_16"));
        gridLayout_16->setContentsMargins(-1, 0, -1, 0);
        outdoor = new MyPushButton(widget_plat);
        outdoor->setObjectName(QString::fromUtf8("outdoor"));
        outdoor->setMinimumSize(QSize(130, 70));
        outdoor->setMaximumSize(QSize(160, 70));
        outdoor->setFont(font1);
        outdoor->setAutoFillBackground(false);
        outdoor->setCheckable(true);

        gridLayout_16->addWidget(outdoor, 1, 0, 1, 1);

        indoor = new MyPushButton(widget_plat);
        indoor->setObjectName(QString::fromUtf8("indoor"));
        indoor->setMinimumSize(QSize(130, 70));
        indoor->setMaximumSize(QSize(160, 70));
        QFont font2;
        font2.setPointSize(15);
        font2.setBold(true);
        font2.setUnderline(false);
        indoor->setFont(font2);
        indoor->setAutoFillBackground(false);
        indoor->setCheckable(true);

        gridLayout_16->addWidget(indoor, 0, 0, 1, 1);


        horizontalLayout_8->addLayout(gridLayout_16);


        verticalLayout_2->addWidget(widget_plat);

        widget_4 = new QWidget(verticalWidget_2);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_14 = new QHBoxLayout(widget_4);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        widget = new QWidget(widget_4);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout_8 = new QVBoxLayout(widget);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        label_16 = new QLabel(widget);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        QFont font3;
        font3.setPointSize(13);
        font3.setBold(true);
        label_16->setFont(font3);
        label_16->setAlignment(Qt::AlignCenter);

        verticalLayout_8->addWidget(label_16);

        elevator_hight = new QLabel(widget);
        elevator_hight->setObjectName(QString::fromUtf8("elevator_hight"));
        elevator_hight->setMinimumSize(QSize(100, 0));
        elevator_hight->setMaximumSize(QSize(16777215, 16777215));
        elevator_hight->setAlignment(Qt::AlignCenter);

        verticalLayout_8->addWidget(elevator_hight);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        evelator_up = new QPushButton(widget);
        evelator_up->setObjectName(QString::fromUtf8("evelator_up"));
        evelator_up->setMaximumSize(QSize(30, 30));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        evelator_up->setIcon(icon1);

        gridLayout_3->addWidget(evelator_up, 0, 0, 1, 1);


        verticalLayout_8->addLayout(gridLayout_3);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        left_motor = new QSlider(widget);
        left_motor->setObjectName(QString::fromUtf8("left_motor"));
        left_motor->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(left_motor->sizePolicy().hasHeightForWidth());
        left_motor->setSizePolicy(sizePolicy);
        left_motor->setMinimumSize(QSize(0, 100));
        left_motor->setAcceptDrops(false);
        left_motor->setLayoutDirection(Qt::LeftToRight);
        left_motor->setAutoFillBackground(false);
        left_motor->setMaximum(500);
        left_motor->setTracking(true);
        left_motor->setOrientation(Qt::Vertical);
        left_motor->setTickPosition(QSlider::TicksAbove);

        gridLayout->addWidget(left_motor, 0, 0, 1, 1);


        verticalLayout_8->addLayout(gridLayout);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        evelator_down = new QPushButton(widget);
        evelator_down->setObjectName(QString::fromUtf8("evelator_down"));
        evelator_down->setMaximumSize(QSize(30, 30));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/reduce.png"), QSize(), QIcon::Normal, QIcon::Off);
        evelator_down->setIcon(icon2);

        gridLayout_4->addWidget(evelator_down, 0, 0, 1, 1);


        verticalLayout_8->addLayout(gridLayout_4);


        horizontalLayout_14->addWidget(widget);

        widget1 = new QWidget(widget_4);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        verticalLayout_12 = new QVBoxLayout(widget1);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        verticalLayout_12->setContentsMargins(0, 0, 0, 0);
        label_17 = new QLabel(widget1);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setFont(font3);
        label_17->setAlignment(Qt::AlignCenter);

        verticalLayout_12->addWidget(label_17);

        ang_val = new QLabel(widget1);
        ang_val->setObjectName(QString::fromUtf8("ang_val"));
        ang_val->setMinimumSize(QSize(100, 0));
        ang_val->setMaximumSize(QSize(16777215, 16777215));
        ang_val->setAlignment(Qt::AlignCenter);

        verticalLayout_12->addWidget(ang_val);

        gridLayout_18 = new QGridLayout();
        gridLayout_18->setObjectName(QString::fromUtf8("gridLayout_18"));
        ang_up = new QPushButton(widget1);
        ang_up->setObjectName(QString::fromUtf8("ang_up"));
        ang_up->setMaximumSize(QSize(30, 30));
        ang_up->setIcon(icon1);

        gridLayout_18->addWidget(ang_up, 0, 0, 1, 1);


        verticalLayout_12->addLayout(gridLayout_18);

        gridLayout_19 = new QGridLayout();
        gridLayout_19->setObjectName(QString::fromUtf8("gridLayout_19"));
        ang_slide = new QSlider(widget1);
        ang_slide->setObjectName(QString::fromUtf8("ang_slide"));
        ang_slide->setEnabled(true);
        sizePolicy.setHeightForWidth(ang_slide->sizePolicy().hasHeightForWidth());
        ang_slide->setSizePolicy(sizePolicy);
        ang_slide->setMinimumSize(QSize(0, 100));
        ang_slide->setAcceptDrops(false);
        ang_slide->setLayoutDirection(Qt::LeftToRight);
        ang_slide->setAutoFillBackground(false);
        ang_slide->setMaximum(100);
        ang_slide->setSingleStep(0);
        ang_slide->setTracking(true);
        ang_slide->setOrientation(Qt::Vertical);
        ang_slide->setTickPosition(QSlider::TicksAbove);

        gridLayout_19->addWidget(ang_slide, 0, 0, 1, 1);


        verticalLayout_12->addLayout(gridLayout_19);

        gridLayout_20 = new QGridLayout();
        gridLayout_20->setObjectName(QString::fromUtf8("gridLayout_20"));
        ang_down = new QPushButton(widget1);
        ang_down->setObjectName(QString::fromUtf8("ang_down"));
        ang_down->setMaximumSize(QSize(30, 30));
        ang_down->setIcon(icon2);

        gridLayout_20->addWidget(ang_down, 0, 0, 1, 1);


        verticalLayout_12->addLayout(gridLayout_20);


        horizontalLayout_14->addWidget(widget1);

        widget_2 = new QWidget(widget_4);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        verticalLayout_13 = new QVBoxLayout(widget_2);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        verticalLayout_13->setContentsMargins(0, 0, 0, 0);
        label_23 = new QLabel(widget_2);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setFont(font3);
        label_23->setAlignment(Qt::AlignCenter);

        verticalLayout_13->addWidget(label_23);

        vel_val = new QLabel(widget_2);
        vel_val->setObjectName(QString::fromUtf8("vel_val"));
        vel_val->setMinimumSize(QSize(100, 0));
        vel_val->setMaximumSize(QSize(16777215, 16777215));
        vel_val->setAlignment(Qt::AlignCenter);

        verticalLayout_13->addWidget(vel_val);

        gridLayout_21 = new QGridLayout();
        gridLayout_21->setObjectName(QString::fromUtf8("gridLayout_21"));
        vel_add = new QPushButton(widget_2);
        vel_add->setObjectName(QString::fromUtf8("vel_add"));
        vel_add->setMaximumSize(QSize(30, 30));
        vel_add->setIcon(icon1);

        gridLayout_21->addWidget(vel_add, 0, 0, 1, 1);


        verticalLayout_13->addLayout(gridLayout_21);

        gridLayout_22 = new QGridLayout();
        gridLayout_22->setObjectName(QString::fromUtf8("gridLayout_22"));
        vel_slider = new QSlider(widget_2);
        vel_slider->setObjectName(QString::fromUtf8("vel_slider"));
        vel_slider->setEnabled(true);
        sizePolicy.setHeightForWidth(vel_slider->sizePolicy().hasHeightForWidth());
        vel_slider->setSizePolicy(sizePolicy);
        vel_slider->setMinimumSize(QSize(0, 100));
        vel_slider->setAcceptDrops(false);
        vel_slider->setLayoutDirection(Qt::LeftToRight);
        vel_slider->setAutoFillBackground(false);
        vel_slider->setMaximum(100);
        vel_slider->setTracking(true);
        vel_slider->setOrientation(Qt::Vertical);
        vel_slider->setTickPosition(QSlider::TicksAbove);

        gridLayout_22->addWidget(vel_slider, 0, 0, 1, 1);


        verticalLayout_13->addLayout(gridLayout_22);

        gridLayout_23 = new QGridLayout();
        gridLayout_23->setObjectName(QString::fromUtf8("gridLayout_23"));
        vel_down = new QPushButton(widget_2);
        vel_down->setObjectName(QString::fromUtf8("vel_down"));
        vel_down->setMaximumSize(QSize(30, 30));
        vel_down->setIcon(icon2);

        gridLayout_23->addWidget(vel_down, 0, 0, 1, 1);


        verticalLayout_13->addLayout(gridLayout_23);


        horizontalLayout_14->addWidget(widget_2);

        widget_3 = new QWidget(widget_4);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        verticalLayout_11 = new QVBoxLayout(widget_3);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        verticalLayout_11->setContentsMargins(0, 0, 0, 0);
        label_19 = new QLabel(widget_3);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setFont(font3);
        label_19->setAlignment(Qt::AlignCenter);

        verticalLayout_11->addWidget(label_19);

        tmp_switch = new SwitchButton(widget_3);
        tmp_switch->setObjectName(QString::fromUtf8("tmp_switch"));
        tmp_switch->setMinimumSize(QSize(0, 40));
        tmp_switch->setMaximumSize(QSize(16777215, 60));

        verticalLayout_11->addWidget(tmp_switch);

        label_21 = new QLabel(widget_3);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setFont(font3);
        label_21->setAlignment(Qt::AlignCenter);

        verticalLayout_11->addWidget(label_21);

        topics_vel = new QComboBox(widget_3);
        topics_vel->setObjectName(QString::fromUtf8("topics_vel"));
        topics_vel->setMinimumSize(QSize(0, 30));

        verticalLayout_11->addWidget(topics_vel);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_11->addItem(verticalSpacer_3);


        horizontalLayout_14->addWidget(widget_3);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_4);


        verticalLayout_2->addWidget(widget_4);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        state_widget = new QWidget(verticalWidget_2);
        state_widget->setObjectName(QString::fromUtf8("state_widget"));
        state_widget->setAutoFillBackground(true);
        state_widget->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_3 = new QHBoxLayout(state_widget);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        topics_img = new QComboBox(state_widget);
        topics_img->setObjectName(QString::fromUtf8("topics_img"));
        topics_img->setMinimumSize(QSize(150, 30));
        topics_img->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);

        horizontalLayout_3->addWidget(topics_img);

        refresh = new QPushButton(state_widget);
        refresh->setObjectName(QString::fromUtf8("refresh"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        refresh->setIcon(icon3);

        horizontalLayout_3->addWidget(refresh);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        select_format = new QComboBox(state_widget);
        select_format->addItem(QString());
        select_format->addItem(QString());
        select_format->addItem(QString());
        select_format->addItem(QString());
        select_format->addItem(QString());
        select_format->addItem(QString());
        select_format->addItem(QString());
        select_format->addItem(QString());
        select_format->addItem(QString());
        select_format->setObjectName(QString::fromUtf8("select_format"));
        select_format->setMinimumSize(QSize(40, 0));
        select_format->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_3->addWidget(select_format);

        snapshoot = new QPushButton(state_widget);
        snapshoot->setObjectName(QString::fromUtf8("snapshoot"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/start.png"), QSize(), QIcon::Normal, QIcon::Off);
        snapshoot->setIcon(icon4);

        horizontalLayout_3->addWidget(snapshoot);


        verticalLayout_9->addWidget(state_widget);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        verticalSpacer_5 = new QSpacerItem(1, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        horizontalLayout_5->addItem(verticalSpacer_5);

        rviz_img = new RvizImage(verticalWidget_2);
        rviz_img->setObjectName(QString::fromUtf8("rviz_img"));
        rviz_img->setStyleSheet(QString::fromUtf8("QStackedWidget{\n"
"border-right: 10px solid qlineargradient(x0:0, x1:1,stop:  0 white, stop: 1 #ececef);\n"
"background-color: transparent;\n"
"}\n"
""));

        horizontalLayout_5->addWidget(rviz_img);

        horizontalLayout_5->setStretch(1, 1);

        verticalLayout_9->addLayout(horizontalLayout_5);

        verticalLayout_9->setStretch(1, 1);

        verticalLayout_2->addLayout(verticalLayout_9);

        verticalLayout_2->setStretch(2, 1);

        horizontalLayout_7->addWidget(verticalWidget_2);

        widget_plot = new QWidget(centralwidget);
        widget_plot->setObjectName(QString::fromUtf8("widget_plot"));
        verticalLayout_7 = new QVBoxLayout(widget_plot);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        vertical_road = new QVBoxLayout();
        vertical_road->setObjectName(QString::fromUtf8("vertical_road"));
        vertical_road->setContentsMargins(-1, 0, -1, -1);
        param_widget = new QWidget(widget_plot);
        param_widget->setObjectName(QString::fromUtf8("param_widget"));
        horizontalLayout_2 = new QHBoxLayout(param_widget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        selected_path = new QComboBox(param_widget);
        selected_path->addItem(QString());
        selected_path->addItem(QString());
        selected_path->addItem(QString());
        selected_path->addItem(QString());
        selected_path->setObjectName(QString::fromUtf8("selected_path"));
        selected_path->setMinimumSize(QSize(0, 30));

        horizontalLayout_2->addWidget(selected_path);

        track_path = new QPushButton(param_widget);
        track_path->setObjectName(QString::fromUtf8("track_path"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/track_path.png"), QSize(), QIcon::Normal, QIcon::Off);
        track_path->setIcon(icon5);
        track_path->setCheckable(true);
        track_path->setChecked(false);
        track_path->setAutoExclusive(true);

        horizontalLayout_2->addWidget(track_path);

        stop_track = new QPushButton(param_widget);
        stop_track->setObjectName(QString::fromUtf8("stop_track"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/images/end.png"), QSize(), QIcon::Normal, QIcon::Off);
        stop_track->setIcon(icon6);

        horizontalLayout_2->addWidget(stop_track);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_14);

        space_path = new QSpacerItem(398, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(space_path);


        vertical_road->addWidget(param_widget);


        verticalLayout_7->addLayout(vertical_road);

        plot_road = new PlotRoad(widget_plot);
        plot_road->setObjectName(QString::fromUtf8("plot_road"));

        verticalLayout_7->addWidget(plot_road);

        widget_5 = new QWidget(widget_plot);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        label_3 = new QLabel(widget_5);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(130, 20, 371, 20));
        pushButton = new QPushButton(widget_5);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(20, 20, 89, 25));
        label_4 = new QLabel(widget_5);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(120, 50, 341, 20));
        label_6 = new QLabel(widget_5);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(120, 80, 67, 17));
        pushButton_3 = new QPushButton(widget_5);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(20, 90, 89, 25));
        pushButton_5 = new QPushButton(widget_5);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(240, 100, 89, 25));
        slam = new QPushButton(widget_5);
        slam->setObjectName(QString::fromUtf8("slam"));
        slam->setGeometry(QRect(20, 140, 89, 25));
        savemap = new QPushButton(widget_5);
        savemap->setObjectName(QString::fromUtf8("savemap"));
        savemap->setGeometry(QRect(130, 140, 89, 25));
        nav = new QPushButton(widget_5);
        nav->setObjectName(QString::fromUtf8("nav"));
        nav->setGeometry(QRect(250, 140, 89, 25));
        lineEdit = new QLineEdit(widget_5);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(20, 180, 281, 25));

        verticalLayout_7->addWidget(widget_5);

        verticalLayout_7->setStretch(1, 2);
        verticalLayout_7->setStretch(2, 1);

        horizontalLayout_7->addWidget(widget_plot);

        rviz_widget = new QWidget(centralwidget);
        rviz_widget->setObjectName(QString::fromUtf8("rviz_widget"));
        horizontalLayout_10 = new QHBoxLayout(rviz_widget);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(-1, 0, 0, -1);
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        map_widget = new QWidget(rviz_widget);
        map_widget->setObjectName(QString::fromUtf8("map_widget"));
        horizontalLayout_4 = new QHBoxLayout(map_widget);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        topics_laser = new QComboBox(map_widget);
        topics_laser->setObjectName(QString::fromUtf8("topics_laser"));

        horizontalLayout_4->addWidget(topics_laser);

        refresh_map = new QPushButton(map_widget);
        refresh_map->setObjectName(QString::fromUtf8("refresh_map"));
        refresh_map->setIcon(icon3);

        horizontalLayout_4->addWidget(refresh_map);

        map_switch = new SwitchButton(map_widget);
        map_switch->setObjectName(QString::fromUtf8("map_switch"));
        map_switch->setMinimumSize(QSize(100, 30));
        map_switch->setMaximumSize(QSize(16777215, 60));

        horizontalLayout_4->addWidget(map_switch);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);

        gmapping_btn = new QPushButton(map_widget);
        gmapping_btn->setObjectName(QString::fromUtf8("gmapping_btn"));
        gmapping_btn->setMinimumSize(QSize(0, 30));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/images/scan-laser.png"), QSize(), QIcon::Normal, QIcon::Off);
        gmapping_btn->setIcon(icon7);

        horizontalLayout_4->addWidget(gmapping_btn);

        save_map = new QPushButton(map_widget);
        save_map->setObjectName(QString::fromUtf8("save_map"));

        horizontalLayout_4->addWidget(save_map);

        set_start = new QPushButton(map_widget);
        set_start->setObjectName(QString::fromUtf8("set_start"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/images/classes/SetInitialPose.png"), QSize(), QIcon::Normal, QIcon::Off);
        set_start->setIcon(icon8);

        horizontalLayout_4->addWidget(set_start);

        set_goal = new QPushButton(map_widget);
        set_goal->setObjectName(QString::fromUtf8("set_goal"));
        set_goal->setMinimumSize(QSize(0, 30));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/images/classes/Pose.png"), QSize(), QIcon::Normal, QIcon::Off);
        set_goal->setIcon(icon9);

        horizontalLayout_4->addWidget(set_goal);

        screen_btn = new QPushButton(map_widget);
        screen_btn->setObjectName(QString::fromUtf8("screen_btn"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/images/\345\205\250\345\261\217.png"), QSize(), QIcon::Normal, QIcon::Off);
        screen_btn->setIcon(icon10);

        horizontalLayout_4->addWidget(screen_btn);


        verticalLayout_6->addWidget(map_widget);

        panel_widget = new QWidget(rviz_widget);
        panel_widget->setObjectName(QString::fromUtf8("panel_widget"));
        horizontalLayout_13 = new QHBoxLayout(panel_widget);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        rviz_panel = new RvizPanel(panel_widget);
        rviz_panel->setObjectName(QString::fromUtf8("rviz_panel"));

        horizontalLayout_13->addWidget(rviz_panel);


        verticalLayout_6->addWidget(panel_widget);

        gridWidget = new QWidget(rviz_widget);
        gridWidget->setObjectName(QString::fromUtf8("gridWidget"));
        grid_control = new QGridLayout(gridWidget);
        grid_control->setObjectName(QString::fromUtf8("grid_control"));
        omgControl = new QWidget(gridWidget);
        omgControl->setObjectName(QString::fromUtf8("omgControl"));
        omgControl->setMinimumSize(QSize(150, 150));
        omgControl->setMaximumSize(QSize(300, 300));
        omgControl->setAcceptDrops(true);
        omgControl->setStyleSheet(QString::fromUtf8("background-color: rgb(250, 250, 250);\n"
"border-top-color: rgb(250, 250, 250);\n"
"border-right-color: rgb(250, 250, 250);\n"
"border-bottom-color: rgb(250, 250, 250);\n"
"border-left-color: rgb(250, 250, 250);"));

        grid_control->addWidget(omgControl, 0, 0, 1, 1);


        verticalLayout_6->addWidget(gridWidget);

        verticalLayout_6->setStretch(1, 1);

        horizontalLayout_10->addLayout(verticalLayout_6);


        horizontalLayout_7->addWidget(rviz_widget);

        verticalSpacer = new QSpacerItem(1, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        horizontalLayout_7->addItem(verticalSpacer);

        horizontalLayout_7->setStretch(2, 3);
        horizontalLayout_7->setStretch(3, 3);

        gridLayout_2->addLayout(horizontalLayout_7, 2, 0, 1, 1);

        horizontalWidget = new QWidget(centralwidget);
        horizontalWidget->setObjectName(QString::fromUtf8("horizontalWidget"));
        horizontalWidget->setAcceptDrops(true);
        horizontalLayout_6 = new QHBoxLayout(horizontalWidget);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setSizeConstraint(QLayout::SetMaximumSize);
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        menu_btn = new QPushButton(horizontalWidget);
        menu_btn->setObjectName(QString::fromUtf8("menu_btn"));

        horizontalLayout_6->addWidget(menu_btn);

        img_path = new QPushButton(horizontalWidget);
        img_path->setObjectName(QString::fromUtf8("img_path"));

        horizontalLayout_6->addWidget(img_path);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_8);

        label_10 = new QLabel(horizontalWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_6->addWidget(label_10);

        rosmasteruri = new QLineEdit(horizontalWidget);
        rosmasteruri->setObjectName(QString::fromUtf8("rosmasteruri"));
        rosmasteruri->setMaximumSize(QSize(250, 16777215));
        rosmasteruri->setReadOnly(false);
        rosmasteruri->setClearButtonEnabled(false);

        horizontalLayout_6->addWidget(rosmasteruri);

        local_ip = new QCheckBox(horizontalWidget);
        local_ip->setObjectName(QString::fromUtf8("local_ip"));
        local_ip->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_6->addWidget(local_ip);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_7);

        minumize = new QPushButton(horizontalWidget);
        minumize->setObjectName(QString::fromUtf8("minumize"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/images/minimize.png"), QSize(), QIcon::Normal, QIcon::Off);
        minumize->setIcon(icon11);

        horizontalLayout_6->addWidget(minumize);

        screen = new QPushButton(horizontalWidget);
        screen->setObjectName(QString::fromUtf8("screen"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/images/minscreen.png"), QSize(), QIcon::Normal, QIcon::Off);
        screen->setIcon(icon12);

        horizontalLayout_6->addWidget(screen);

        shutdown = new QPushButton(horizontalWidget);
        shutdown->setObjectName(QString::fromUtf8("shutdown"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/images/close.png"), QSize(), QIcon::Normal, QIcon::Off);
        shutdown->setIcon(icon13);

        horizontalLayout_6->addWidget(shutdown);


        gridLayout_2->addWidget(horizontalWidget, 0, 0, 1, 1);

        MainWindowDesign->setCentralWidget(centralwidget);

        retranslateUi(MainWindowDesign);
        QObject::connect(action_Quit, SIGNAL(triggered()), MainWindowDesign, SLOT(close()));

        car0_connect->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindowDesign);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowDesign)
    {
        MainWindowDesign->setWindowTitle(QApplication::translate("MainWindowDesign", "QRosApp", nullptr));
        action_Quit->setText(QApplication::translate("MainWindowDesign", "&Quit", nullptr));
#ifndef QT_NO_SHORTCUT
        action_Quit->setShortcut(QApplication::translate("MainWindowDesign", "Ctrl+Q", nullptr));
#endif // QT_NO_SHORTCUT
        action_Preferences->setText(QApplication::translate("MainWindowDesign", "&Preferences", nullptr));
        actionAbout->setText(QApplication::translate("MainWindowDesign", "&About", nullptr));
        actionAbout_Qt->setText(QApplication::translate("MainWindowDesign", "About &Qt", nullptr));
        action1->setText(QApplication::translate("MainWindowDesign", "1#\347\247\273\345\212\250\345\271\263\345\217\260\n"
"\n"
"", nullptr));
        action2->setText(QApplication::translate("MainWindowDesign", "2#\347\247\273\345\212\250\345\271\263\345\217\260\n"
"\n"
"", nullptr));
        action->setText(QApplication::translate("MainWindowDesign", "\345\256\244\345\206\205", nullptr));
        action_2->setText(QApplication::translate("MainWindowDesign", "\345\256\244\345\244\226", nullptr));
        image_file->setText(QApplication::translate("MainWindowDesign", "\346\210\252\345\233\276\350\267\257\345\276\204", nullptr));
        img_format->setText(QApplication::translate("MainWindowDesign", "\345\233\276\347\211\207\346\240\274\345\274\217", nullptr));
        action_3->setText(QApplication::translate("MainWindowDesign", "\345\234\260\345\233\276\350\267\257\345\276\204", nullptr));
        label_2->setText(QString());
        label->setText(QApplication::translate("MainWindowDesign", "\346\234\272\345\231\250\344\272\272\347\212\266\346\200\201 : ", nullptr));
        label_state->setText(QApplication::translate("MainWindowDesign", "\347\246\273\347\272\277", nullptr));
        label_link->setText(QString());
        label_7->setText(QApplication::translate("MainWindowDesign", "\351\200\237\345\272\246\357\274\232", nullptr));
        label_vel->setText(QApplication::translate("MainWindowDesign", "0.99", nullptr));
        label_9->setText(QApplication::translate("MainWindowDesign", "m/s", nullptr));
        label_11->setText(QString());
        label_8->setText(QApplication::translate("MainWindowDesign", "\350\247\222\351\200\237\345\272\246\357\274\232", nullptr));
        label_rad->setText(QApplication::translate("MainWindowDesign", "0.11", nullptr));
        label_13->setText(QApplication::translate("MainWindowDesign", "rad/s", nullptr));
        label_5->setText(QApplication::translate("MainWindowDesign", "GPS: ", nullptr));
        posqual->setText(QApplication::translate("MainWindowDesign", "\345\233\272\345\256\232\350\247\243", nullptr));
        headingqual->setText(QApplication::translate("MainWindowDesign", "\345\233\272\345\256\232\350\247\243", nullptr));
        gps_east->setText(QApplication::translate("MainWindowDesign", "\344\270\234: 0.00", nullptr));
        gps_north->setText(QApplication::translate("MainWindowDesign", "\345\214\227: 0.00", nullptr));
        gps_heading->setText(QApplication::translate("MainWindowDesign", "\346\234\235\345\220\221:0.00\302\260", nullptr));
        label_18->setText(QString());
        label_voltage->setText(QApplication::translate("MainWindowDesign", "21.1V", nullptr));
        car0_connect->setText(QApplication::translate("MainWindowDesign", "1#\347\247\273\345\212\250\345\271\263\345\217\260", nullptr));
        outdoor->setText(QApplication::translate("MainWindowDesign", "\345\256\244\345\244\226", nullptr));
        indoor->setText(QApplication::translate("MainWindowDesign", "\345\256\244\345\206\205", nullptr));
        label_16->setText(QApplication::translate("MainWindowDesign", "\345\215\207\351\231\215\346\234\272\346\216\247\345\210\266", nullptr));
        elevator_hight->setText(QApplication::translate("MainWindowDesign", "\351\253\230\345\272\246:0mm", nullptr));
        evelator_up->setText(QString());
        evelator_down->setText(QString());
        label_17->setText(QApplication::translate("MainWindowDesign", "\350\247\222\351\200\237\345\272\246\350\214\203\345\233\264", nullptr));
        ang_val->setText(QApplication::translate("MainWindowDesign", "0 rad/s", nullptr));
        ang_up->setText(QString());
        ang_down->setText(QString());
        label_23->setText(QApplication::translate("MainWindowDesign", "\347\272\277\351\200\237\345\272\246\350\214\203\345\233\264", nullptr));
        vel_val->setText(QApplication::translate("MainWindowDesign", "0 m/s", nullptr));
        vel_add->setText(QString());
        vel_down->setText(QString());
        label_19->setText(QApplication::translate("MainWindowDesign", "\346\270\251\345\272\246\345\274\200\345\205\263", nullptr));
        label_21->setText(QApplication::translate("MainWindowDesign", "\351\200\237\345\272\246\346\216\247\345\210\266", nullptr));
        refresh->setText(QApplication::translate("MainWindowDesign", " \345\210\267\346\226\260", nullptr));
        select_format->setItemText(0, QApplication::translate("MainWindowDesign", "PNG", nullptr));
        select_format->setItemText(1, QApplication::translate("MainWindowDesign", "JPG", nullptr));
        select_format->setItemText(2, QApplication::translate("MainWindowDesign", "JPEG", nullptr));
        select_format->setItemText(3, QApplication::translate("MainWindowDesign", "BMP", nullptr));
        select_format->setItemText(4, QApplication::translate("MainWindowDesign", "PBM", nullptr));
        select_format->setItemText(5, QApplication::translate("MainWindowDesign", "PGM", nullptr));
        select_format->setItemText(6, QApplication::translate("MainWindowDesign", "PPM", nullptr));
        select_format->setItemText(7, QApplication::translate("MainWindowDesign", "XBM", nullptr));
        select_format->setItemText(8, QApplication::translate("MainWindowDesign", "XPM", nullptr));

        snapshoot->setText(QApplication::translate("MainWindowDesign", " \345\274\200\345\247\213\346\210\252\345\233\276", nullptr));
        selected_path->setItemText(0, QApplication::translate("MainWindowDesign", "\347\233\264\347\272\277\350\267\257\345\276\204", nullptr));
        selected_path->setItemText(1, QApplication::translate("MainWindowDesign", "S\345\236\213\350\267\257\345\276\204", nullptr));
        selected_path->setItemText(2, QApplication::translate("MainWindowDesign", "\345\234\206\345\275\242\350\267\257\345\276\204", nullptr));
        selected_path->setItemText(3, QApplication::translate("MainWindowDesign", "\350\275\250\350\277\271\351\207\207\347\202\271", nullptr));

        track_path->setText(QApplication::translate("MainWindowDesign", "\345\274\200\345\247\213\350\267\237\350\270\252", nullptr));
        stop_track->setText(QApplication::translate("MainWindowDesign", "\345\201\234\346\255\242", nullptr));
        label_3->setText(QApplication::translate("MainWindowDesign", "TextLabel", nullptr));
        pushButton->setText(QApplication::translate("MainWindowDesign", "PushButton", nullptr));
        label_4->setText(QApplication::translate("MainWindowDesign", "TextLabel", nullptr));
        label_6->setText(QApplication::translate("MainWindowDesign", "TextLabel", nullptr));
        pushButton_3->setText(QApplication::translate("MainWindowDesign", "PushButton", nullptr));
        pushButton_5->setText(QApplication::translate("MainWindowDesign", "close", nullptr));
        slam->setText(QApplication::translate("MainWindowDesign", "slam", nullptr));
        savemap->setText(QApplication::translate("MainWindowDesign", "save map", nullptr));
        nav->setText(QApplication::translate("MainWindowDesign", "nav", nullptr));
        refresh_map->setText(QApplication::translate("MainWindowDesign", " \345\210\267\346\226\260", nullptr));
        gmapping_btn->setText(QApplication::translate("MainWindowDesign", "\345\274\200\345\247\213\345\273\272\345\233\276", nullptr));
        save_map->setText(QApplication::translate("MainWindowDesign", "\344\277\235\345\255\230\345\234\260\345\233\276", nullptr));
        set_start->setText(QApplication::translate("MainWindowDesign", "\344\275\215\345\247\277\344\274\260\350\256\241", nullptr));
        set_goal->setText(QApplication::translate("MainWindowDesign", " \345\257\274\350\210\252", nullptr));
        screen_btn->setText(QApplication::translate("MainWindowDesign", "\346\224\276\345\244\247", nullptr));
        menu_btn->setText(QApplication::translate("MainWindowDesign", "\350\256\276\347\275\256", nullptr));
        img_path->setText(QApplication::translate("MainWindowDesign", "\346\210\252\345\233\276\350\267\257\345\276\204", nullptr));
        label_10->setText(QApplication::translate("MainWindowDesign", "\344\270\273\346\234\272\345\234\260\345\235\200", nullptr));
        local_ip->setText(QApplication::translate("MainWindowDesign", "\346\234\254\346\234\272", nullptr));
        minumize->setText(QString());
        screen->setText(QString());
        shutdown->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindowDesign: public Ui_MainWindowDesign {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_WINDOW_H
