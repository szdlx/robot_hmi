#ifndef FILEOPERATE_HPP
#define FILEOPERATE_HPP

#include <QObject>
#include <QQuickItem>
#include <QFile>
#include <QQmlProperty>
#include <iostream>

class FileOperate: public QObject
{
    Q_OBJECT
    Q_PROPERTY(int pCnt READ getCnt WRITE setCnt)
    Q_PROPERTY(QPointF qpf READ getQPF WRITE writeQPF)
public:
    FileOperate();
    ~FileOperate();
    QObject *obj;
    void initFile();

    void getCoordinate();

    int pCnt = 110;           //记录数量
    QVector<QPointF> vCoor; //存储传输过来的标注点集合
    QPointF qpf;

    int getCnt(){return pCnt;}
    void setCnt(int cnt) { this->pCnt = cnt;}

    QPointF getQPF(){return qpf;}
    void writeQPF(QPointF qp) { vCoor.push_back(qp);}

    Q_INVOKABLE void writeCoorData();   //写入txt文件

public slots:
    void refresh()
    { getCoordinate(); qDebug() << 10 << "Click C++ slot<<endl";}



};

#endif // FILEOPERATE_HPP
