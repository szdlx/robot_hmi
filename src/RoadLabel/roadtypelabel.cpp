#include "./include/cyrobot_monitor/RoadLabel/roadtypelabel.h"
#include "ui_roadtypelabel.h"

RoadTypeLabel::RoadTypeLabel(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::RoadTypeLabel)
{
    ui->setupUi(this);
    ui->type_icon->setMaximumSize(60, 40); //TODO

    roadTypeIcon[0] = new QPixmap("://road_type_icon/sandstone_road.jpg");
    roadTypeIcon[1] = new QPixmap("://road_type_icon/earth_road.jpg");
    roadTypeIcon[2] = new QPixmap("://road_type_icon/ice_road.jpg");

    qDebug("IN Type"); //TODO
}

RoadTypeLabel::~RoadTypeLabel()
{
    qDebug("del Type"); //TODO
    for (int i = 0; i < 3; i++) {
        delete roadTypeIcon[i];
    }
    delete ui;
}

void RoadTypeLabel::setType(int type)
{
    switch (type) {
    case 0:
        ui->type_name->setText("砂石路");
        ui->type_icon->setPixmap(*roadTypeIcon[0]);
        break;
    case 1:
        ui->type_name->setText("土路");
        ui->type_icon->setPixmap(*roadTypeIcon[1]);
        break;
    case 2:
        ui->type_name->setText("冰雪路");
        ui->type_icon->setPixmap(*roadTypeIcon[2]);
        break;
    default:
        ui->type_name->setText("未知");
        ui->type_icon->clear();
        break;
    }
};
