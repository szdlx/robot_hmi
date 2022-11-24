#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    this->setWindowTitle("设置");

    ReadSettings();
    connect_init();

}

void Settings::connect_init(){
    connect(ui->ensure, &QPushButton::clicked, this,[this]{
        WriteSettings();
        emit velRangChanged(velmax/100.0,angmax/100.0);
        this->close();
    });
    connect(ui->cancel, &QPushButton::clicked, this,[this]{
        this->close();
    });
    connect(ui->ang_silder, &QSlider::valueChanged, this, [this](int val){
        angmax=val;
        ui->ang_label->setText(QString::number(angmax/100.0,'f',3)+"rad/s" );
    });
    connect(ui->vel_slider,&QSlider::valueChanged, this, [this](int val){
        velmax=val;
        ui->vel_label->setText(QString::number(velmax/100.0,'f',3)+"m/s  " );
    });
//    connect(ui->pushButton, &QPushButton::clicked,this, [this]{
//        tenable = !tenable;
//        emit testEnable(tenable);
//    });
}

void Settings::ReadSettings(){
    QSettings settings("menu set", "robot_hmi");
    angmax=settings.value("angmax").toFloat();
    if(int(angmax)==0) angmax=100;
    velmax=settings.value("velmax").toFloat();
    if(int(velmax)==0) velmax=100;
    ui->ang_silder->setValue(angmax);
    ui->ang_label->setText(QString::number(angmax/100.0,'f',3)+"rad/s" );
    ui->vel_slider->setValue(velmax);
    ui->vel_label->setText(QString::number(velmax/100.0,'f',3)+"m/s  " );
}

void Settings::WriteSettings(){
    QSettings settings("menu set", "robot_hmi");
    settings.setValue("angmax",angmax);
    settings.setValue("velmax",velmax);
}


Settings::~Settings()
{
    delete ui;
}
