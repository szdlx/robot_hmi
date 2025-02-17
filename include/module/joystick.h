﻿#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <QDebug>
#include <QDrag>
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>
#include <QWidget>
#include <QtMath>
class JoyStick : public QWidget {
  Q_OBJECT

 public:
  JoyStick(QWidget *parent = 0);
  ~JoyStick();
  enum {
    upleft = 0,
    up,
    upright,
    left,
    stop,
    right,
    downleft,
    down,
    downright
  };
 signals:
  void keyNumchanged(int num);
  void keyPosChanged(QPointF pos);      // 双摇杆控制，分别是线速度与角速度
  void keyControl(float vel, float angle);    // 单个遥控控制，线速度与角速度

 protected:
  void paintEvent(QPaintEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  //  void resizeEvent(QResizeEvent *event)override;
 private:
  int mouseX;
  int mouseY;
  int JoyStickX;  //摇杆
  int JoyStickY;
  int JoyStickR;
  int padX;  //底盘
  int padY;
  int padR;
  double handPadDis;  //两圆圆心距离
  bool mousePressed;
  QTimer *tim;

 private:
  double Pointdis(int a, int b, int x, int y);  //两点距离
  int getKeyNum();
  QPointF getkeyPos();
  QPointF getCoorPos(QPointF pos);
  void emitVel();
};

#endif  // JoyStick_H
