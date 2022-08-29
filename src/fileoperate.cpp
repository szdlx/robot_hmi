#include "../include/cyrobot_monitor/fileoperate.hpp"
//#include <iostream>
#include <QQmlProperty>

/*
//[virtual] bool QFile::open(OpenMode mode);
*OpenMode mode 打开方式，是一个枚举类型
*QIODevice::NotOpen 不打开
*QIODevice::ReadOnly 只读方式
*QIODevice::WriteOnly 读写方式
*QIODevice::ReadWrite 读写方式
*QIODevice::Append   追加方式
*QIODevice::Truncate 阶段方式
*QIODevice::Text     转换不同平台的换行，读的时候把所有换行转成'\n',写的时候再把'\n'转换对应平台的换行
*QIODevice::Unbuffered 不使用缓冲区
*/

FileOperate::FileOperate()
{
    //initFile();
}

FileOperate::~FileOperate()
{

}

/*
QByteArray QIODevice::readLine(qint64 maxSize = 0) //读取一行，但是这一行不能超过maxSize字节，maxSize = 0代表不限制行字节数。
qint64 QIODevice::write(const QByteArray &byteArray); //将byteArray写入文件，写完内部位置指针后移

*/
void FileOperate::initFile()    //测试用的
{
    QFile file("/home/liangrongmin/123.txt");
    file.open(QIODevice::ReadWrite);
    file.resize(0);     //文件内容清零
    if( file.isOpen() == false  )
        qDebug() << "sucess:" << file.readLine(14) << endl;
//    QByteArray byte("helloword");
//    file.write(byte);
//    file.write("\n");
//    byte.append("\t0123\t");
//    //file.open(QIODevice::Append);
//    file.write(byte);
//    qDebug() << "read:" << file.readAll() << endl;

//    QDataStream stream(&file);

    int a[5] = {1,2,3,4,10};
    int num = sizeof (a)/sizeof (int);

//    qDebug() << "num:" << num << endl;
//    QString str = "helloworld";
//    stream << num;
//    for ( int i=0; i<num; i++) {
//        stream << a[i];
//    }
//    stream  << str ;
//    const char *strp = str.toStdString().data();
//    stream.writeRawData(strp,str.length());
    QTextStream qts(&file);
    for(int i=0; i< 4; i++)
    {
        qts << i << " " << 30.00+i/100 << " "<< 'N'
            << " "<< 80.00+i/100 << " "<< 'E' << endl ;
//        char str[1000];
////        QString str;
//        sprintf(str,"%d %lf %c %lf %c",i,30.00+i/100, 'N', 80.00+i/100, 'E');
//        if( qts.writeRawData(str,1000) == -1 )
//            break;
//        qDebug() << str ;
    }


//    int a[5];
//    QString str;
//    int num;
//    stream >> num;
//    for(int i=0; i< num; i++)
//    {
//        stream >> a[i];
//        qDebug() << "a[" << i << "]" << ":" << a[i];
//    }
//    stream >> str;
//    qDebug() << endl <<"str:" << str << endl;
    //stream >> a >> str;
    //qDebug() << "a:" << a << "str:" << str << endl;

    file.close();
}

void FileOperate::writeCoorData()
{
//    pCnt = obj->property("pCnt").toInt();
    if(pCnt == 0)
        return;
    QFile file("data.txt");
    file.open(QIODevice::ReadWrite);
    file.resize(0);     //文件内容清零
    if( file.isOpen() == false  )
        qDebug() << "sucess:" << file.readLine(14) << endl;


    QTextStream qts(&file);
    for(int i=0; i< pCnt; i++)
    {
        qts << i << " " << QString("%1").arg(vCoor[i].rx(),0,'g',16)
            << " "<< QString("%1").arg(vCoor[i].ry(),0,'g',16) << endl ;
    }
}

//int count = 0;
void FileOperate::getCoordinate()
{
    QPointF qpf;
    qpf = obj->property("dataCoor").toPointF();
    vCoor.push_back(qpf);


//    qDebug() << "coor:" << qpf;
//    double a = qpf.rx();
//    double b = qpf.ry();
//    //测试传输过来的数据精度
//    qDebug() << "x:" << QString("%1").arg(a,0,'g',20) <<
//                " y:" << QString("%1").arg(b,0,'g',20) << endl;
//    qDebug() << "tt:" << obj->property("tt").toReal() << endl;
//    double te = 14.182572021471799;
//    qDebug() << "te:" << 14.182572021471799;


//    qDebug() << "longitude:" << obj->property("getCoordinateX").toDouble();
////    obj->property("getCoordinateX").toList()
////    QVector()
//    obj->setProperty("someNumber",300+count++);
}
