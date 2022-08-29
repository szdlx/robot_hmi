#ifndef PLOTPANEL_H
#define PLOTPANEL_H

#include "./include/cyrobot_monitor/RoadPlot/axistag.h"
#include "./include/cyrobot_monitor/RoadPlot/qcustomplot.h"
#include <QWidget>

class PlotPanel : public QWidget {
    Q_OBJECT

public:
    explicit PlotPanel(QWidget* parent = nullptr);
    ~PlotPanel();

public slots:
    void timerSlot();
    void addValueSlot(double);

protected:
    QCustomPlot* mPlot;
    QLabel* title;
    QPointer<QCPGraph> mGraph;
    AxisTag* mTag;
    QTimer mDataTimer;
};

class PlotRoadCurv : public PlotPanel {
    Q_OBJECT
public:
    explicit PlotRoadCurv(QWidget* parent = nullptr);
    ~PlotRoadCurv();
};

class PlotRoadSlope : public PlotPanel {
    Q_OBJECT
public:
    explicit PlotRoadSlope(QWidget* parent = nullptr);
    ~PlotRoadSlope();
};

//
class PlotRoad : public QWidget {
    Q_OBJECT
public:
    explicit PlotRoad(QWidget* parent = nullptr);
    ~PlotRoad();

public slots:
    void update_mainmap_slots();
    void update_focusmap_slots(double x, double y);
    void read_data_slots();

protected:
    QPushButton* button;
    QLabel* label;
    QCustomPlot* mPlotMain;
    QCustomPlot* mPlotFocus;
    QPointer<QCPCurve> mCurveMain;
    QPointer<QCPCurve> mDotMain;
    QPointer<QCPCurve> mCurveSide1;
    QPointer<QCPCurve> mCurveSide2;
    QPointer<QCPCurve> mDotSide;

    QVector<QVector<double>> data;
    QVector<QVector<double>> data_side1;
    QVector<QVector<double>> data_side2;
};

#endif // PLOTPANEL_H
