#include <QColor>
#include <QVBoxLayout>

#include "./include/cyrobot_monitor/RvizPanel/rvizpanel.h"

//RvizPanel base class for pc2 & gridmap
RvizPanel::RvizPanel(QWidget* parent)
    : QWidget(parent)
    , settings("rviz_topic", "cyrobot_monitor")
    , inited(false)
{
    //    main_layout = new QVBoxLayout;
}

RvizPanel::~RvizPanel()
{
    qDebug("del Panel"); //TODO
    delete manager;
    delete render_panel;
}

void RvizPanel::setTopicSlot(QString topic)
{
    if (not inited)
        return;
    if (display->subProp("Topic")->getValue().toString() != topic) {
        display->subProp("Topic")->setValue(topic);
    }
}
void RvizPanel::setFixedFrameSlot(QString fixedframe)
{
    if (not inited)
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

    QVBoxLayout* main_layout = new QVBoxLayout;

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

    render_panel->initialize(manager->getSceneManager(), manager);
    manager->initialize();
    manager->startUpdate();

    view = manager->getViewManager()->getCurrent();
}

void RvizPanel::deinitPanelSlot()
{
    if (not inited)
        return;

    view = nullptr;
    delete manager;
    delete render_panel;
    delete layout();

    inited = false;
}

//RvizPC2Lidar
RvizPC2Lidar::RvizPC2Lidar(QWidget* parent)
    : RvizPanel(parent)
{
}

RvizPC2Lidar::~RvizPC2Lidar()
{
    qDebug("del PC2"); //TODO
}

void RvizPC2Lidar::initPanelSlot()
{
    RvizPanel::initPanelSlot();
    if (inited)
        return;

    type_name = "PC2Lidar";

    // Create a PC2 display.
    qDebug("IN PC2"); //TODO
    display = manager->createDisplay("rviz/PointCloud2", "PC2Lidar", true);
    ROS_ASSERT(display != NULL);

    // Configure the PC2Display the way we like it.
    //    manager->setFixedFrame("vehicle_frame");
    manager->setFixedFrame(settings.value("rviz/PC2Lidar/fixedframe").toString());
    //    pc2->subProp("Topic")->setValue("/lidar_cloud_calibrated");
    display->subProp("Topic")->setValue(settings.value("rviz/PC2Lidar/topic"));
    display->subProp("Size (m)")->setValue(0.1);

    inited = true;

    //    RvizPanel::initPanelSlot();
    //    if (inited)
    //        return;

    //    type_name = "PC2Lidar";

    //    // Create a image display.
    //    qDebug("IN image"); //TODO
    //    display = manager->createDisplay("my_image_display/Image", "Image", true);
    //    ROS_ASSERT(display != NULL);

    //    // Configure the PC2Display the way we like it.
    //    display->subProp("Image Topic")->setValue("/car/image");
    //    display->subProp("Transport Hint")->setValue("compressed");

    //    inited = true;
}

//RvizPC2Colored
RvizPC2Colored::RvizPC2Colored(QWidget* parent)
    : RvizPanel(parent)
{
}

RvizPC2Colored::~RvizPC2Colored()
{
    qDebug("del PC2"); //TODO
}

void RvizPC2Colored::initPanelSlot()
{
    RvizPanel::initPanelSlot();
    if (inited)
        return;

    type_name = "PC2Colored";

    // Create a PC2 display.
    qDebug("IN PC2"); //TODO
    display = manager->createDisplay("rviz/PointCloud2", "PC2Colored", true);
    ROS_ASSERT(display != NULL);

    // Configure the PC2Display the way we like it.
    //    manager->setFixedFrame("vehicle_frame");
    manager->setFixedFrame(settings.value("rviz/PC2Colored/fixedframe").toString());
    //    display->subProp("Topic")->setValue("/colored_cloud_toshow");
    display->subProp("Topic")->setValue(settings.value("rviz/PC2Colored/topic"));
    display->subProp("Size (m)")->setValue(0.1);

    inited = true;
}

//RvizGridMap
RvizGridMap::RvizGridMap(QWidget* parent)
    : RvizPanel(parent)
{
}

RvizGridMap::~RvizGridMap()
{
    qDebug("del GM"); //TODO
}

void RvizGridMap::initPanelSlot()
{
    RvizPanel::initPanelSlot();
    if (inited)
        return;

    type_name = "GridMap";

    qDebug("IN GM"); //TODO
    //    gridmap = manager->createDisplay("grid_map_rviz_plugin/GridMap", "GridMap", true);
    display = manager->createDisplay("grid_map_rviz_plugin/GridMap", "GridMap", true);
    ROS_ASSERT(display != NULL);

    //    manager->setFixedFrame("odom");
    manager->setFixedFrame(settings.value("rviz/GridMap/fixedframe").toString());
    view->subProp("Target Frame")->setValue("vehicle_frame");
    //    manager->getViewManager()->getCurrent()->setProperty("Target Frame", "vehicle_frame");

    //    display->subProp("Topic")->setValue("/elevation_mapping/elevation_map");
    display->subProp("Topic")->setValue(settings.value("rviz/GridMap/topic"));
    display->subProp("History Length")->setValue(100);

    inited = true;
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
    if (not inited)
        return;
    imageview->setTopic(newtopic);
    //    settings.setValue("rviz/Image/topic", newtopic);
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
    if (not inited)
        return;
    delete imageview;
    delete layout();

    inited = false;
}
