#include "../include/cyrobot_monitor/qosm.hpp"
#include "../include/cyrobot_monitor/fileoperate.hpp"
#include "ui_qosm.h"
#include <QObject>
#include <QQmlComponent>
#include <QQmlContext>
#include <QQuickItem>
#include <QQuickWidget>
#include <QVBoxLayout>
#include <QtQuick>

qosm::qosm(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::qosm)
{
    ui->setupUi(this);
    initOSM();
    //run();
}

qosm::~qosm()
{
    delete ui;
}

void qosm::initOSM()
{
    FileOperate qm;
    QQuickWidget* m_quickWidget;
    m_quickWidget = new QQuickWidget(this);
    //    m_quickWidget->engine()->rootContext()->setContextProperty("qo",qo);
    //    m_quickWidget->engine()->rootContext()->setContextProperty("qm",&qm);
    qmlRegisterType<FileOperate>("FileOperate", 1, 0, "FileOperate");
    m_quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    m_quickWidget->setFocus();
    m_quickWidget->setSource(QUrl::fromLocalFile("://qml/qosm.qml"));
    //    m_quickWidget->setWindowTitle("hhhhh");

    //    qm->obj = m_quickWidget->rootObject();       //获取qosm.qml的QObject
    //    ui->verticalLayout_osm->setParent(this);
    //    ui->verticalLayout_osm->la
    //    ui->verticalLayout_osm->addWidget(m_quickWidget);
    QVBoxLayout* main_layout = new QVBoxLayout;
    main_layout->addWidget(m_quickWidget);
    setLayout(main_layout);

    //    int a =  qm.obj->property("pCnt").toInt();
    //    qDebug() << "a:" << a;

    //    QVBoxLayout boxL;
    //    QQuickView *view = new QQuickView;
    //    FileOperate qm;
    //    view->setSource(QUrl::fromLocalFile("://qml/qosm.qml"));
    //    view->engine()->rootContext()->setContextProperty("qm", &qm);
    //    view->setWidth(500);
    //    view->setHeight(900);
    //    view->show();

    //    QWidget *container = QWidget::createWindowContainer(view, this);

    //////    container->setMinimumSize(200, 200);
    //////    container->setMaximumSize(200, 200);
    ////    container->show();
    ////    container->setFocusPolicy(Qt::TabFocus);
    //////    boxL.addWidget(view);
    //    ui->verticalLayout_osm->addWidget(container);
}

void qosm::getCoordinate()
{
    QPointF qpf;
    qpf = obj->property("dataCoor").toPointF();
    vCoor.push_back(qpf);
}

void qosm::writeCoorData() //将标注点全部写入txt文件
{
    pCnt = obj->property("pCnt").toInt(); //获取
    if (pCnt == 0)
        return;
    QFile file("123.txt");
    file.open(QIODevice::ReadWrite);
    file.resize(0); //文件内容清零
    if (file.isOpen() == false)
        qDebug() << "sucess:" << file.readLine(14) << endl;

    QTextStream qts(&file);
    for (int i = 0; i < pCnt; i++) {
        qts << i << " " << QString("%1").arg(vCoor[i].rx(), 0, 'g', 16)
            << " " << QString("%1").arg(vCoor[i].ry(), 0, 'g', 16) << endl;
    }
}

//void qosm::run()
//{
//   //initOSM();
//}
