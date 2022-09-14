#include <QColor>
#include <QVBoxLayout>
#include <QPushButton>

#include "./include/RvizPanel/rvizpanel.h"
#include "QDebug"

//RvizPanel base class for pc2 & gridmap
RvizPanel::RvizPanel(QWidget* parent)
    : QWidget(parent)
    , settings("rviz_topic", "robot_hmi")
    , inited(false)
{
}

RvizPanel::~RvizPanel()
{
    qDebug("del Panel"); //TODO
    delete manager;
    delete render_panel;
}

void RvizPanel::setTopicSlot(QString topic)
{
    if (!inited)
        return;
    if (display->subProp("Topic")->getValue().toString() != topic) {
        display->subProp("Topic")->setValue(topic);
    }
}
void RvizPanel::setFixedFrameSlot(QString fixedframe)
{
    if (!inited)
        return;
    if (manager->getFixedFrame() != fixedframe) {
        manager->setFixedFrame(fixedframe);
    }
}

void RvizPanel::initPanelSlot()
{
    if (inited)
        return;

    qDebug("IN Panel"); //TODO

    // Construct and lay out render panel.
    render_panel = new rviz::RenderPanel();
//    if(main_layout==NULL)
        main_layout = new QVBoxLayout;
    main_layout->setMargin(0);
    main_layout->setSpacing(1);
    main_layout->addWidget(render_panel);

    //    setLayout(main_layout);
    this->setLayout(main_layout);

    // Next we initialize the main RViz classes.
    //
    // The VisualizationManager is the container for Display objects,
    // holds the main Ogre scene, holds the ViewController, etc.  It is
    // very central and we will probably need one in every usage of
    // librviz.
    manager = new rviz::VisualizationManager(render_panel);
    render_panel->initialize(manager->getSceneManager(), manager);  //
    manager->initialize();
    manager->startUpdate();
    manager->removeAllDisplays();


    auto viewManager= manager->getViewManager();
    viewManager->setRenderPanel(render_panel);
    viewManager->setCurrentViewControllerType("rviz/Orbit");
    viewManager->getCurrent()->subProp("Target Frame")->setValue("map");
//    viewManager->setCurrentViewControllerType("rviz/FPS");
    view = manager->getViewManager()->getCurrent();
    view->reset();      // 重新回到初始位置
//    view->lookAt()    // 改变视角
    inited=true;

    // 获取Display组
    display_group_ = manager->getRootDisplayGroup();
}

void RvizPanel::deinitPanelSlot()
{
    if (!inited)
        return;

    view = nullptr;
    delete manager;
    delete render_panel;
    delete layout();

    inited = false;
}



int cnt=0;
void RvizPanel::mapDisplaySlot(const QVector<std::string>& topic){
    if(topic.empty())return ;
    if(cnt) return ;
    cnt++;

    for(auto str:topic){
        auto md=manager->createDisplay("rviz/Map","myMap",true);
        ROS_ASSERT(md!=NULL);
        md->subProp("Topic")->setValue(str.c_str());
        if(str.find("local_costmap")!=std::string::npos){
            md->subProp("Color Scheme")->setValue("costmap");
            md->subProp("Alpha")->setValue("0.4");
        }else if(str.find("global_costmap")!=std::string::npos){
            md->subProp("Color Scheme")->setValue("costmap");
            md->subProp("Alpha")->setValue("0.2");
        }else {
            md->subProp("Color Scheme")->setValue("map");
            md->subProp("Alpha")->setValue("0.9");
        }
    }


}
void RvizPanel::LaserDisplaySlot(const QString& topic){
    if(laserScanDisplay!=NULL)
    {
//        auto a = laserScanDisplay->subProp("Topic")->getValue();
//        if(topic==a)    // topic not change
//            return;
        delete laserScanDisplay;
        laserScanDisplay=NULL;
    }
    laserScanDisplay=manager->createDisplay("rviz/LaserScan","myLaser",true);
    laserScanDisplay->subProp("Topic")->setValue(topic);
    laserScanDisplay->subProp("Size (m)")->setValue(0.1);
    ROS_ASSERT(laserScanDisplay!=NULL);
}

void RvizPanel::robotModelDisplySlot(){
    if(robotModelDisplay!=NULL)
    {
        delete robotModelDisplay;
        robotModelDisplay=NULL;
    }
    robotModelDisplay=manager->createDisplay("rviz/RobotModel","myRobotModel",true);
    ROS_ASSERT(robotModelDisplay!=NULL);
}

void RvizPanel::Set_Start_Pose()
{
    rviz::ToolManager* tool_manager_=manager->getToolManager();
    rviz::Tool* current_tool_= tool_manager_->addTool("rviz/SetInitialPose");
    //设置当前使用的工具
    tool_manager_->setCurrentTool(current_tool_);
    manager->startUpdate();
}
void RvizPanel::Set_Goal_Pose()
{
    rviz::ToolManager* tool_manager_=manager->getToolManager();
    //添加工具
    rviz::Tool* current_tool= tool_manager_->addTool("rviz/SetGoal");
    //设置goal的话题
    rviz::Property* pro= current_tool->getPropertyContainer();
    pro->subProp("Topic")->setValue("/move_base_simple/goal");
    //设置当前frame
    manager->setFixedFrame("/map");
    //设置当前使用的工具为SetGoal（实现在地图上标点）
    tool_manager_->setCurrentTool( current_tool );

    goal=manager->createDisplay("rviz/Pose","myGoal",true);
    goal->subProp("Topic")->setValue("/move_base_simple/goal");
    ROS_ASSERT(goal!=NULL);
    manager->startUpdate();

}

int RvizPanel::GetDisplayNum(QString ClassID)
{
    int num = -1;
    for (int i = 0; i < display_group_->numDisplays(); i++)
    {
        if (display_group_->getDisplayAt(i) != nullptr)
        {
            if (ClassID == display_group_->getDisplayAt(i)->getClassId())
            {
                num = i;
                break;
            }
        }
    }
    return num;
}

void RvizPanel::polyfootprint(const QVector<std::string>& poly){
    if(poly.empty()) return ;
    QString color[]={"255;00;255;","255;0;0;","0;0;255","0;255;255","0;0;0"};
    int cnt=0;
    for (std::string topic : poly) {
        auto poly=manager->createDisplay("rviz/Polygon","mypoly",true);
        poly->subProp("Topic")->setValue(topic.c_str());
        poly->subProp("Color")->setValue(color[cnt++]);
        ROS_ASSERT(poly!=NULL);
//        path->subProp("")
    }
    manager->startUpdate();
}

void RvizPanel::showPath(const QVector<std::string>& pathList){
    if(pathList.empty()) return ;
    QString color[]={"255;00;255;","255;0;0;","0;0;255","0;255;255","0;0;0"};
    int cnt=0;
    for (std::string topic : pathList) {
        auto path=manager->createDisplay("rviz/Path","mypath",true);
        path->subProp("Topic")->setValue(topic.c_str());
        path->subProp("Color")->setValue(color[cnt++]);
        ROS_ASSERT(path!=NULL);
//        path->subProp("")
    }
    manager->startUpdate();
}


void RvizPanel::showCarPose(const QString& topic, int car){

    int num = GetDisplayNum("rviz/Marker");
    qDebug()<< "num:" << num << endl;

//    if(marker1!=NULL){
//        delete marker1;
//        marker1=NULL;
//    }
    if(num==-1){
        marker1=manager->createDisplay("rviz/Marker","",true);
        marker1->subProp("Topic")->setValue(topic);
        ROS_ASSERT(marker1!=NULL);
    }

//    if(num==-1){
//        if(car==1){
//            marker1=manager->createDisplay("rviz/Marker","",true);
//            marker1->subProp("Topic")->setValue(topic);
//            ROS_ASSERT(marker1!=NULL);
//        }
//        else {
//            marker2=manager->createDisplay("rviz/Marker","",true);
//            marker2->subProp("Topic")->setValue(topic);
//            ROS_ASSERT(marker2!=NULL);
//        }
//    }


}


void RvizPanel::resizeEvent(QResizeEvent*)
{
    //重新设置顶部工具栏的位置和宽高,可以自行设置顶部显示或者底部显示
//    int height = 20;
//    flow->setGeometry(borderWidth, borderWidth, this->width() - (borderWidth * 2), height);
    //flowPanel->setGeometry(borderWidth, this->height() - height - borderWidth, this->width() - (borderWidth * 2), height);
}

void RvizPanel::enterEvent(QEvent*)
{
    //这里还可以增加一个判断,是否获取了焦点的才需要显示
    //if (this->hasFocus()) {}
//    if (flowEnable) {
//        flow->setVisible(true);
//    }
}

void RvizPanel::leaveEvent(QEvent*)
{
//    if (flowEnable) {
//        flow->setVisible(false);
//    }
}




//ImageView class for camera
RvizImage::RvizImage(QWidget* parent)
    : QWidget(parent)
    , settings("rviz_topic", "cyrobot_monitor")
    , inited(false)
{
}

RvizImage::~RvizImage()
{
    qDebug("del Cam"); //TODO
    //    delete imageview;
}

void RvizImage::setTopicSlot(QString newtopic)
{
    if (!inited)
        return;
    imageview->setTopic(newtopic);
    //    settings.setValue("rviz/Image/topic", newtopic);
}

const sensor_msgs::Image::ConstPtr& RvizImage::getImage(){
//    cv_bridge::CvImagePtr cv_ptr;
    return imageview->getImage();
}

void RvizImage::initPanelSlot()
{
    if (inited)
        return;

    qDebug("IN Cam"); //TODO

    topic = settings.value("rviz/Image/topic").toString();
    //    imageview = new ImageView(0, "/rgb_front/image_raw");
    imageview = new ImageView(0, topic);

    QVBoxLayout* main_layout = new QVBoxLayout();

    main_layout->setMargin(0);
    main_layout->setSpacing(1);

    main_layout->addWidget(imageview);
    imageview->setEnabled(true);

    //    setLayout(main_layout);
    this->setLayout(main_layout);
    inited = true;
}

void RvizImage::deinitPanelSlot()
{
    if (!inited)
        return;
    delete imageview;
    delete layout();

    inited = false;
}
