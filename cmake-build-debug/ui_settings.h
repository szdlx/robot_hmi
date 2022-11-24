/********************************************************************************
** Form generated from reading UI file 'settings.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_H
#define UI_SETTINGS_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Settings
{
public:
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_3;
    QSlider *vel_slider;
    QLabel *vel_label;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_2;
    QSlider *ang_silder;
    QLabel *ang_label;
    QSpacerItem *horizontalSpacer_3;
    QFrame *line;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout;
    QPushButton *cancel;
    QSpacerItem *horizontalSpacer;
    QPushButton *ensure;

    void setupUi(QWidget *Settings)
    {
        if (Settings->objectName().isEmpty())
            Settings->setObjectName(QString::fromUtf8("Settings"));
        Settings->resize(503, 372);
        verticalLayout = new QVBoxLayout(Settings);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        scrollArea = new QScrollArea(Settings);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 483, 314));
        verticalLayout_3 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(13);
        font.setBold(true);
        label->setFont(font);

        verticalLayout_2->addWidget(label);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_3 = new QLabel(scrollAreaWidgetContents);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_6->addWidget(label_3);

        vel_slider = new QSlider(scrollAreaWidgetContents);
        vel_slider->setObjectName(QString::fromUtf8("vel_slider"));
        vel_slider->setMaximum(100);
        vel_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_6->addWidget(vel_slider);

        vel_label = new QLabel(scrollAreaWidgetContents);
        vel_label->setObjectName(QString::fromUtf8("vel_label"));

        horizontalLayout_6->addWidget(vel_label);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_2 = new QLabel(scrollAreaWidgetContents);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_5->addWidget(label_2);

        ang_silder = new QSlider(scrollAreaWidgetContents);
        ang_silder->setObjectName(QString::fromUtf8("ang_silder"));
        ang_silder->setMaximum(100);
        ang_silder->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(ang_silder);

        ang_label = new QLabel(scrollAreaWidgetContents);
        ang_label->setObjectName(QString::fromUtf8("ang_label"));

        horizontalLayout_5->addWidget(ang_label);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout_5);


        verticalLayout_3->addLayout(verticalLayout_2);

        line = new QFrame(scrollAreaWidgetContents);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));

        verticalLayout_3->addLayout(verticalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));

        verticalLayout_3->addLayout(horizontalLayout_3);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        cancel = new QPushButton(Settings);
        cancel->setObjectName(QString::fromUtf8("cancel"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        cancel->setIcon(icon);

        horizontalLayout->addWidget(cancel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        ensure = new QPushButton(Settings);
        ensure->setObjectName(QString::fromUtf8("ensure"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/ensure.png"), QSize(), QIcon::Normal, QIcon::Off);
        ensure->setIcon(icon1);

        horizontalLayout->addWidget(ensure);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(Settings);

        QMetaObject::connectSlotsByName(Settings);
    } // setupUi

    void retranslateUi(QWidget *Settings)
    {
        Settings->setWindowTitle(QApplication::translate("Settings", "Form", nullptr));
        label->setText(QApplication::translate("Settings", "\350\267\257\345\276\204\350\267\237\350\270\252", nullptr));
        label_3->setText(QApplication::translate("Settings", "\347\272\277\351\200\237\345\272\246\350\214\203\345\233\264", nullptr));
        vel_label->setText(QApplication::translate("Settings", "1.00m/s  ", nullptr));
        label_2->setText(QApplication::translate("Settings", "\350\247\222\351\200\237\345\272\246\350\214\203\345\233\264", nullptr));
        ang_label->setText(QApplication::translate("Settings", "1.00rad/s", nullptr));
        cancel->setText(QApplication::translate("Settings", "\345\217\226\346\266\210", nullptr));
        ensure->setText(QApplication::translate("Settings", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Settings: public Ui_Settings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_H
