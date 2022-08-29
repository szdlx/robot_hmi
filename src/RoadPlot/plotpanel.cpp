
#include "./include/cyrobot_monitor/RoadPlot/plotpanel.h"
#include <Eigen/Core>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <fstream>
#include <iostream>
#include<QDebug>

PlotPanel::PlotPanel(QWidget* parent)
    : QWidget(parent)
    , mPlot(0)
    , mTag(0)
{
    qDebug("IN Plot"); //TODO

    mPlot = new QCustomPlot(this);
    title = new QLabel(this);
    title->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    QVBoxLayout* main_layout = new QVBoxLayout;
    main_layout->addWidget(title);
    main_layout->addWidget(mPlot);
    setLayout(main_layout);

    // configure plot to have two right axes:
    mPlot->yAxis->setTickLabels(false);
    connect(mPlot->yAxis2, SIGNAL(rangeChanged(QCPRange)), mPlot->yAxis, SLOT(setRange(QCPRange))); // left axis only mirrors inner right axis
    mPlot->yAxis2->setVisible(true);
    mPlot->axisRect()->axis(QCPAxis::atRight, 0)->setPadding(30); // add some padding to have space for tags

    // create graphs:
    mGraph = mPlot->addGraph(mPlot->xAxis, mPlot->axisRect()->axis(QCPAxis::atRight, 0));
    mGraph->setPen(QPen(QColor(250, 120, 0)));

    // create tags with newly introduced AxisTag class (see axistag.h/.cpp):
    mTag = new AxisTag(mGraph->valueAxis());
    mTag->setPen(mGraph->pen());

    //    connect(&mDataTimer, SIGNAL(timeout()), this, SLOT(timerSlot()));
    //    mDataTimer.start(40);
}

PlotPanel::~PlotPanel()
{
    qDebug("del Plot"); //TODO
    delete title;
    delete mTag;
    delete mPlot;
}

void PlotPanel::timerSlot()
{
    // calculate and add a new data point to each graph:
    mGraph->addData(mGraph->dataCount(), qSin(mGraph->dataCount() / 50.0) + qSin(mGraph->dataCount() / 50.0 / 0.3843) * 0.25);

    // make key axis range scroll with the data:
    mPlot->xAxis->rescale();
    mGraph->rescaleValueAxis(false, true);
    mPlot->xAxis->setRange(mPlot->xAxis->range().upper, 100, Qt::AlignRight);

    // update the vertical axis tag positions and texts to match the rightmost data point of the graphs:
    double graph1Value = mGraph->dataMainValue(mGraph->dataCount() - 1);
    mTag->updatePosition(graph1Value);
    mTag->setText(QString::number(graph1Value, 'f', 2));

    mPlot->replot();
}

void PlotPanel::addValueSlot(double value)
{
    // add a new data point to each graph:
    mGraph->addData(mGraph->dataCount(), value);

    // make key axis range scroll with the data:
    mPlot->xAxis->rescale();
    mGraph->rescaleValueAxis(false, true);
    mPlot->xAxis->setRange(mPlot->xAxis->range().upper, 100, Qt::AlignRight);

    // update the vertical axis tag positions and texts to match the rightmost data point of the graphs:
    double graph1Value = mGraph->dataMainValue(mGraph->dataCount() - 1);
    mTag->updatePosition(graph1Value);
    mTag->setText(QString::number(graph1Value, 'f', 2));

    mPlot->replot();
};

PlotRoadCurv::PlotRoadCurv(QWidget* parent)
    : PlotPanel(parent)
{
    title->setText("道路曲率：");
}

PlotRoadCurv::~PlotRoadCurv()
{
}

PlotRoadSlope::PlotRoadSlope(QWidget* parent)
    : PlotPanel(parent)
{
    title->setText("道路斜率：");
}

PlotRoadSlope::~PlotRoadSlope()
{
}

PlotRoad::PlotRoad(QWidget* parent)
{

    button = new QPushButton(this);
    button->setText("选择文件");
    button->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    connect(button, SIGNAL(clicked()), this, SLOT(read_data_slots()));

    label = new QLabel(this);

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(button);
    layout->addWidget(label);

    mPlotFocus = new QCustomPlot(this);
    mPlotFocus->setInteraction(QCP::iRangeDrag, true);
    mPlotFocus->setInteraction(QCP::iRangeZoom, true);
    mPlotFocus->xAxis->setTickLabels(false);
    mPlotFocus->yAxis->setTickLabels(false);
    mPlotFocus->xAxis2->setVisible(true);
    mPlotFocus->yAxis2->setVisible(true);
    mPlotFocus->xAxis2->setTickLabels(false);
    mPlotFocus->yAxis2->setTickLabels(false);

    mPlotMain = new QCustomPlot(this);
    mPlotMain->setInteraction(QCP::iRangeDrag, true);
    mPlotMain->setInteraction(QCP::iRangeZoom, true);
    mPlotMain->xAxis->setTickLabels(false);
    mPlotMain->yAxis->setTickLabels(false);
    mPlotMain->xAxis2->setVisible(true);
    mPlotMain->yAxis2->setVisible(true);
    mPlotMain->xAxis2->setTickLabels(false);
    mPlotMain->yAxis2->setTickLabels(false);

    QVBoxLayout* main_layout = new QVBoxLayout;
    main_layout->addLayout(layout);
    main_layout->addWidget(mPlotFocus);
    main_layout->addWidget(mPlotMain);
    main_layout->setStretch(0, 0);
    main_layout->setStretch(1, 1);
    main_layout->setStretch(2, 1);
    setLayout(main_layout);

    // configure plot to have two right axes:
    //    mPlotMain->yAxis->setTickLabels(false);
    //    connect(mPlotMain->yAxis2, SIGNAL(rangeChanged(QCPRange)), mPlot->yAxis, SLOT(setRange(QCPRange))); // left axis only mirrors inner right axis
    //    mPlotMain->yAxis2->setVisible(true);
    //    mPlotMain->axisRect()->axis(QCPAxis::atRight, 0)->setPadding(30); // add some padding to have space for tags

    // create graphs:
    mCurveMain = new QCPCurve(mPlotMain->xAxis, mPlotMain->yAxis);
    mDotMain = new QCPCurve(mPlotMain->xAxis, mPlotMain->yAxis);
    mCurveSide1 = new QCPCurve(mPlotFocus->xAxis, mPlotFocus->yAxis);
    mCurveSide2 = new QCPCurve(mPlotFocus->xAxis, mPlotFocus->yAxis);
    //    mCurveSide1 = new QCPCurve(mPlotMain->xAxis, mPlotMain->yAxis);
    //    mCurveSide2 = new QCPCurve(mPlotMain->xAxis, mPlotMain->yAxis);
    mDotSide = new QCPCurve(mPlotFocus->xAxis, mPlotFocus->yAxis);

    QPen pen;
    pen.setColor(QColor(46, 204, 250));
    pen.setWidthF(10);
    mCurveMain->setPen(pen);
    pen.setColor(QColor(255, 215, 0));
    pen.setWidthF(5);
    mDotMain->setPen(pen);
    mDotMain->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));

    pen.setColor(QColor(0, 0, 0));
    pen.setWidthF(5);
    mCurveSide1->setPen(pen);
    mCurveSide2->setPen(pen);
    pen.setColor(QColor(255, 215, 0));
    mDotSide->setPen(pen);
    mDotSide->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));

    //data init
    data.clear();
    data.push_back(QVector<double>({}));
    data.push_back(QVector<double>({}));
    data.push_back(QVector<double>({}));
    data_side1.clear();
    data_side1.push_back(QVector<double>({}));
    data_side1.push_back(QVector<double>({}));
    data_side2.clear();
    data_side2.push_back(QVector<double>({}));
    data_side2.push_back(QVector<double>({}));
}
PlotRoad::~PlotRoad()
{
}

void PlotRoad::read_data_slots()
{
    QString fileName = QFileDialog::getOpenFileName(this, QStringLiteral("选择文件"), "", tr("*.csv"));
    qDebug() << fileName;
    if (fileName.isEmpty())
        return;
    label->setText(fileName);

    using namespace std;
    ifstream file;
    file.open(fileName.toStdString());

    double temp;
    QVector<double> x;
    QVector<double> y;
    QVector<double> width;
    int i = 0;
    //<
    //    while (!file.eof()) {
    //        file >> temp; //x
    //        x.push_back(temp);
    //        file >> temp; //y
    //        y.push_back(temp);
    //        file >> temp;
    //        file >> temp;
    //        file >> temp; //width
    //        width.push_back(temp);
    //        i++;
    //    }
    //>
    //<
    string line;
    string number;
    getline(file, line);
    double x0,y0;
    if (getline(file, line)) {
        istringstream readstr(line); //string数据流化
        //将一行数据按','分割
        getline(readstr, number, ',');
        x0=stod(number);
        getline(readstr, number, ',');
        y0=stod(number);
        x.push_back(0);
        y.push_back(0);
        width.push_back(10); //TODO
    }
    while (getline(file, line)) { //循环读取每行数据
        istringstream readstr(line); //string数据流化
        //将一行数据按','分割
        getline(readstr, number, ',');
        x.push_back(stod(number)-x0);
        getline(readstr, number, ',');
        y.push_back(stod(number)-y0);
        width.push_back(10); //TODO
        i++;
    }
    //>
    data.clear();
    data.push_back(x);
    data.push_back(y);
    data.push_back(width);

    using namespace Eigen;
    Matrix2d leftRotate;
    leftRotate << 0, -1, 1, 0;
    Matrix2d rightRotate;
    rightRotate << 0, 1, -1, 0;

    QVector<double> x1;
    QVector<double> y1;
    QVector<double> x2;
    QVector<double> y2;
    for (int j = 0; j < i - 1; j++) {
        Vector2d base;
        base << x[j], y[j];
        Vector2d direction;
        direction << x[j + 1] - x[j], y[j + 1] - y[j];
        if (direction.norm() < 1e-2)
            continue;
        direction.normalize();
        x1.push_back(((leftRotate * direction * (width[j] / 2.0)) + base)[0]);
        y1.push_back(((leftRotate * direction * (width[j] / 2.0)) + base)[1]);
        x2.push_back(((rightRotate * direction * (width[j] / 2.0)) + base)[0]);
        y2.push_back(((rightRotate * direction * (width[j] / 2.0)) + base)[1]);
    }
    data_side1.clear();
    data_side1.push_back(x1);
    data_side1.push_back(y1);
    data_side2.clear();
    data_side2.push_back(x2);
    data_side2.push_back(y2);

    update_mainmap_slots();
    update_focusmap_slots(x[0], y[0]); //TODO 处理没有点的情况
    qDebug() << "First Position: " << x[0] << y[0]; //TODO
}

void PlotRoad::update_mainmap_slots()
{
    // add a new data point to each graph:
    mCurveMain->setData(data[0], data[1]);

    // make key axis range scroll with the data:
    mPlotMain->xAxis->rescale();
    mPlotMain->yAxis->rescale();
    mCurveMain->rescaleValueAxis(true, true);

    QCPRange range;
    range = mPlotMain->xAxis->range();
    range.lower -= 20;
    range.upper += 20;
    mPlotMain->xAxis->setRange(range);
    range = mPlotMain->yAxis->range();
    range.lower -= 20;
    range.upper += 20;
    mPlotMain->yAxis->setRange(range);

    mPlotMain->replot();
}

void PlotRoad::update_focusmap_slots(double x, double y)
{
    double x_=-y,y_=x;

    //fix position
    double minDistance = 0x3f3f3f3f;
    double tempDistance;
    double x__ = x_, y__ = y_;
    for (int i = 0; i < data[0].size(); i++) {
        tempDistance = abs(data[0][i] - x_) + abs(data[1][i] - y_);
        if (tempDistance < minDistance) {
            minDistance = tempDistance;
            x__ = data[0][i];
            y__ = data[1][i];
        }
    }

    // draw dots to main and side graph
    mDotMain->setData(QVector<double>({ x__ }), QVector<double>({ y__ }));
    mDotSide->setData(QVector<double>({ x_ }), QVector<double>({ y_ }));
    // qDebug()<<"CARPOS::"<<x<<y;

    // add a new data point to each graph:
    mCurveSide1->setData(data_side1[0], data_side1[1]);
    mCurveSide2->setData(data_side2[0], data_side2[1]);

    //    mCurveSide1->rescaleValueAxis(true, true);
    //    mCurveSide2->rescaleValueAxis(true, true);

    mPlotFocus->xAxis->setRange(x_ - 10, x_ + 10);
    mPlotFocus->yAxis->setRange(y_ - 10, y_ + 10);

    mPlotMain->replot();
    mPlotFocus->replot();
}
