/**
 * @file /include/cyrobot_monitor/main_window.hpp
 *
 * @brief Qt based gui for cyrobot_monitor.
 *
 * @date November 2010
 **/
#ifndef cyrobot_monitor_MAIN_WINDOW_H
#define cyrobot_monitor_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/

//#include <QtGui/QMainWindow>
#include "addtopics.h"
#include "qnode.hpp"
#include "qrviz.hpp"
#include "settings.h"
#include "ui_main_window.h"

#include "qosm.hpp"
//仪表盘头文件
#include "CCtrlDashBoard.h"
#include "fileoperate.hpp"
#include "gaugepanel.h" //TODO

#include "QProcess"
#include <QComboBox>
#include <QHBoxLayout>
#include <QQuickView>
#include <QSoundEffect>
#include <QSpinBox>
#include <QStandardItemModel>
#include <QTreeWidgetItem>
#include <QVBoxLayout>
#include <QVariant>
#include <QtQuickWidgets/QQuickWidget>

#include <QInputDialog>
#include <map>
// rviz
#include <rviz/display.h>
#include <rviz/render_panel.h>
#include <rviz/tool.h>
#include <rviz/tool_manager.h>
#include <rviz/visualization_manager.h>

#include <rqt_image_view/ratio_layouted_frame.h>

//编队消息
#include "formationwithtask.h"
#include "reconnoitrewithtask.h"

/*****************************************************************************
** Namespace
*****************************************************************************/
namespace cyrobot_monitor {

extern mission_parse::formationwithtask f_msg;
extern mission_parse::reconnoitrewithtask r_msg;

/*****************************************************************************
** Interface [MainWindow]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(int argc, char** argv, QWidget* parent = 0);
    ~MainWindow();

    void ReadSettings(); // Load up qt program settings at startup
    void WriteSettings(); // Save qt program settings when closing

    void closeEvent(QCloseEvent* event); // Overloaded function
    void keyPressEvent(QKeyEvent* event); //键盘检测

    void showNoMasterMessage();
    void initRviz();
    void initUis();
    void initVideos();
    void initRvizPanel(); //TODO
    void deinitRvizPanel(); //TODO
    void initTopicList();

    void addJoyStick(QVBoxLayout* layout_); //摇杆界面

public slots:
    /******************************************
   ** Auto-connections (connectSlotsByName())
   *******************************************/
    void on_actionAbout_triggered();
    void on_button_connect_clicked(bool check);
    void on_checkbox_use_environment_stateChanged(int state);
    void slot_speed_x(double x);
    void slot_speed_y(double y);
    void slot_power(float p);
    void slot_flag_err(char flag);
    void slot_rosShutdown();
    void quick_cmds_check_change(int);
    void cmd_output();
    void cmd_error_output();

    void refreashTopicList();
    void RvizGetModel(QAbstractItemModel* model);
    /******************************************
   ** Manual connections
   *******************************************/
    void updateLoggingView(); // no idea why this can't connect automatically
    void on_Slider_raw_valueChanged(int value);
    void on_Slider_linear_valueChanged(int value);
    void slot_cmd_control();
    void slot_tab_manage_currentChanged(int);
    void slot_tab_Widget_currentChanged(int);
    void slot_choose_topic(QTreeWidgetItem* choose, QString name);
    void slot_set_2D_Goal();
    void slot_set_2D_Pos();
    void slot_set_select();
    void slot_move_camera_btn();
    //设置界面
    void slot_setting_frame();
    void slot_setting_filepath();
    //设置返航点
    void slot_set_return_point();
    //返航
    void slot_return_point();
    //机器人位置
    void slot_position_change(QString, double, double, double, double);
    void quick_cmd_add();
    void quick_cmd_remove();
    //显示图像
    //显示图像
    void slot_show_image(int, QImage);
    //    void on_horizontalSlider_raw_valueChanged(int value);

    void slot_rviz_topic_changed(); //TODO
    void slot_button_name_changed();

    void joystick_draw(double x, double y); //接收摇杆位置信息

    //更改道路信息话题名
    void on_road_topic_changed();
    void on_carpos_topic_changed();

    //速度控制更改车辆
    void on_car_changed(int);

private slots:
    void on_comboBox_v4_2_currentIndexChanged(int index);
    void on_comboBox_v3_3_currentIndexChanged(int index);
    void on_comboBox_v2_2_currentIndexChanged(int index);
    void on_comboBox_v1_2_currentIndexChanged(int index);
    void on_comboBox_v0_2_currentIndexChanged(int index);

    //******编队 start**********//
    void slot_formation_save_click();
    void slot_leader_choose(QAbstractButton* button);
    void slot_follower_choose(QAbstractButton* button);
    void slot_send_formation();
    //******编队 end*************//

    //******镜像 start ***********//
    void slot_horMirror_set(QAbstractButton* button);
    void slot_verMirror_set(QAbstractButton* button);
    void slot_rotate(QAbstractButton* button);
    //******镜像 end ***********//

    //******图像 ***************//
    void getbtnClicked(QString str);
    void getcomboxIndex(int index, QString objName);
    //******图像 ***************//

    void on_pushButton_add_topic_clicked();
    void on_pushButton_remove_topic_clicked();
    void on_pushButton_rename_topic_clicked();

    void on_treeView_rviz_clicked(const QModelIndex& index);
    void on_disconnect_clicked();

    void on_switchRviz_changed(bool bChecked); // rviz开关的信号

private:
    Ui::MainWindowDesign ui;

    QString JudgeDisplayNewName(QString name);

    void connections();
    void add_quick_cmd(QString name, QString shell);

    void inform(QString);
    bool AskInform(QString);
    void initData();

    QNode qnode;
    qosm* osm_map = NULL;
    //    Settings settings;
    CCtrlDashBoard* m_DashBoard_x;
    CCtrlDashBoard* m_DashBoard_y;
    GaugePanel* m_DashBoard_x_2;
    GaugePanel* m_DashBoard_y_2;

    QProcess* quick_cmd = NULL;
    QProcess* close_remote_cmd = NULL;
    QProcess* base_cmd = NULL;
    QRviz* map_rviz = NULL;
    QStandardItemModel* treeView_rviz_model = NULL;
    AddTopics* addtopic_form = NULL;
    //存放rviz treewidget当前显示的控件及控件的父亲的地址
    QMap<QWidget*, QTreeWidgetItem*> widget_to_parentItem_map;
    //存放状态栏的对应关系 display名 状态item
    QMap<QString, QTreeWidgetItem*> tree_rviz_stues;
    //存放display的当前值 item名，参数名称和值
    QMap<QTreeWidgetItem*, QMap<QString, QString>> tree_rviz_values;
    Settings* set = NULL;
    QSoundEffect* media_player = NULL;

    //编队控件
    QButtonGroup* gLeaderId;
    QButtonGroup* gFollowerId;
    QButtonGroup* gTaskChoose;

    //图像控件
    QButtonGroup* horMirror;
    QButtonGroup* verMirror;
    QComboBox* enCombox[CARNUM]; //编码选择按键
    QButtonGroup* rotateLabel; //旋转角度

    struct formatInfo {
        char id;
        bool isChecked;
        float distance;
        float angle;
    } fCarInfo[CARNUM];

    QAbstractItemModel* m_modelRvizDisplay;

    QMap<QString, QString> m_mapRvizDisplays;

    QString m_sRvizDisplayChooseName_;
    bool ros_states = false;
    bool rviz_states = false;

    double power_min; //电池电量
    double power_max;
};

} // namespace cyrobot_monitor

#endif // cyrobot_monitor_MAIN_WINDOW_H
