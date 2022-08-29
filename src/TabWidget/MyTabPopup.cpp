#include "./include/cyrobot_monitor/TabWidget/MyTabPopup.h"

#include <QDebug>
#include <QMouseEvent>
#include <QVBoxLayout>

MyTabPopup::MyTabPopup(QWidget* parent)
    : QWidget(parent)
{
    this->installEventFilter(this); //安装事件过滤器
}

void MyTabPopup::setContentWidget(QWidget* page)
{
    if (!page)
        return;
    content = page;
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->addWidget(page);
}

QWidget* MyTabPopup::getContentWidget()
{
    return content;
}
int count = 0;
//bool MyTabPopup::event(QEvent *event)
//{
//    switch(event->type())
//    {
//    case QEvent::MouseButtonRelease:
//    case QEvent::NonClientAreaMouseButtonRelease:
//    {
//        QMouseEvent *e=static_cast<QMouseEvent*>(event);
//        if(e&&e->button()==Qt::LeftButton)
//        {
//            emit dragRelease(e->globalPos());
//        }
//    }
//        break;
//    case QEvent::NonClientAreaMouseButtonDblClick:
//        showFullScreen();

//        break;
//    case QEvent::Close:
//        emit backToTabWidget();
//        break;
//    }
////    qDebug() << "test"<<count++;
//    return QDialog::event(event);
//}

bool MyTabPopup::eventFilter(QObject* obj, QEvent* event)
{
    switch (event->type()) {
    case QEvent::MouseButtonRelease:
    case QEvent::NonClientAreaMouseButtonRelease: {
        QMouseEvent* e = static_cast<QMouseEvent*>(event);
        if (e && e->button() == Qt::LeftButton) {
            emit dragRelease(e->globalPos());
        }
    } break;
    case QEvent::MouseButtonDblClick:
        //        if( content->windowState() == Qt::WindowNoState)
        //        {
        //            content->setWindowFlags(Qt::Dialog);
        //            content->setWindowState(Qt::WindowMaximized);
        //            content->showMaximized();
        //        }
        //        else if( content->windowState() == Qt::WindowMaximized )
        //        {
        //            content->setWindowFlags(Qt::SubWindow);
        //            content->setWindowState(Qt::WindowNoState);
        //            content->showNormal();
        //        }
        break;
    case QEvent::Close:
        emit backToTabWidget();
        break;
    case QEvent::Enter:
        break;
    default:
        break;
    }

    return QObject::eventFilter(obj, event);
}
