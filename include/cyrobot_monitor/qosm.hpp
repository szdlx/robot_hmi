#ifndef QOSM_HPP
#define QOSM_HPP

#include <QWidget>
#include <QThread>
#include <QDebug>
//#include <QQuickWidget>

#include <QVector>

namespace Ui {
class qosm;
}

class qosm : public QWidget//, public QThread
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)

public:
    explicit qosm(QWidget *parent = nullptr);
    ~qosm();
    //void run();

    Q_INVOKABLE void qTest()
    { qDebug() << "sucess: ssss" << endl;}
    //qml
    QObject *obj;
    int pCnt = 0;           //记录数量
    QVector<QPointF> vCoor; //存储传输过来的标注点集合


    void setName(const QString &name)
    {
        if( this->name != name)
        {
            this->name = name;
            emit nameChanged();
        }

    }
    QString getName(){return this->name;}

private:
    Ui::qosm *ui;
    void initOSM();
    QString name = "liangrongmin";

signals:
    void nameChanged();

public slots:
    void getCoordinate();   // 每次点击获取的坐标
    void writeCoorData();   //写入txt文件
};

#endif // QOSM_HPP
