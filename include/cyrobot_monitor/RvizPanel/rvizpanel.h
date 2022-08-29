#ifndef RVIZPANEL_H
#define RVIZPANEL_H

#include "imageview.h"
#include "rviz/display.h"
#include "rviz/render_panel.h"
#include "rviz/view_manager.h"
#include "rviz/visualization_manager.h"
#include <QSettings>
#include <QVBoxLayout>

namespace rviz {
class Display;
class RenderPanel;
class VisualizationManager;
class ViewController;
} // namespace rviz

class RvizPanel : public QWidget {
    Q_OBJECT

public:
    RvizPanel(QWidget* parent = 0);
    virtual ~RvizPanel();
public slots:
    void setTopicSlot(QString topic);
    void setFixedFrameSlot(QString fixedframe);
    void initPanelSlot();
    void deinitPanelSlot();

protected:
    //    QVBoxLayout* main_layout;

    rviz::VisualizationManager* manager;
    rviz::RenderPanel* render_panel;
    rviz::Display* display;
    rviz::ViewController* view;

    QSettings settings;
    QString type_name;
    bool inited;
};

//
class RvizPC2Lidar : public RvizPanel {
    Q_OBJECT

public:
    RvizPC2Lidar(QWidget* parent);
    virtual ~RvizPC2Lidar();
public slots:
    void initPanelSlot();
};
//
class RvizPC2Colored : public RvizPanel {
    Q_OBJECT

public:
    RvizPC2Colored(QWidget* parent);
    virtual ~RvizPC2Colored();
public slots:
    void initPanelSlot();
};
//
class RvizGridMap : public RvizPanel {
    Q_OBJECT

public:
    RvizGridMap(QWidget* parent);
    virtual ~RvizGridMap();
public slots:
    void initPanelSlot();
};

//
class RvizImage : public QWidget {
    Q_OBJECT

public:
    RvizImage(QWidget* parent);
    virtual ~RvizImage();
public slots:
    void setTopicSlot(QString topic);
    void initPanelSlot();
    void deinitPanelSlot();

private:
    //    QVBoxLayout* main_layout;

    ImageView* imageview;
    QString topic;
    QSettings settings;
    bool inited;
};

#endif // RVIZPANEL_H
