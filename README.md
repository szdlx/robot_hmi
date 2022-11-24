# ROS qt 人机交互界面

- 实现图像显示，可以自动刷新图像类型画图
- 实现GPS显示，速度显示，速度控制，不同平台的切换
- 不同预定轨迹的跟踪（纯跟踪算法）
- Karto建图，保存地图，调用远程主控机程序
- move base 导航，调用远程主控机程序

***
## 安装依赖

```bash
sudo apt-get install ros-noetic-urg-node 
```



## 运行方式

```bash
rosrun robot_hmi robot_hmi
```

支持Ubuntu与Windows平台，设计主要是为了window平板

## 界面大致介绍

开机界面，上面一栏是车辆状态显示，可以显示连接状态、车辆速度、GPS位置与电池电量信息。

中间位置是显示车辆的平台选择、图像显示、路径类型选择、激光雷达与地图。最下面是车辆控制按钮，左边是速度控制，右边是转型控制，用于平板操作。

![](https://github.com/lrm2017/robot_hmi/blob/main/%E6%95%88%E6%9E%9C%E5%9B%BE/%E7%95%8C%E9%9D%A2%E6%98%BE%E7%A4%BA.png?raw=true)

![](https://github.com/lrm2017/robot_hmi/blob/main/%E6%95%88%E6%9E%9C%E5%9B%BE/2022-08-29%2010-20-49%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE.png?raw=true)

* 点击移动平台1，如果未开启roscore，会自动启动roscore。其中图像与激光雷达会自动切换都平台1的消息画图。

* 左边是图像，点击刷新可以自动获取图像画图；

* 图中间是小车采用纯跟踪算法跟随S型曲线的轨迹

![](https://github.com/lrm2017/robot_hmi/blob/main/%E6%95%88%E6%9E%9C%E5%9B%BE/2022-08-29%2010-19-07%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE.png?raw=true)

![](https://github.com/lrm2017/robot_hmi/blob/main/%E6%95%88%E6%9E%9C%E5%9B%BE/2022-08-29%2010-17-25%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE.png?raw=true)

## 建图与导航

[远程调用主控机运行程序与关闭程序](https://github.com/lrm2017/remoteProgram)

* 点击开始建图，调用远程主控机karto建图
* 点击导航，远程调用move base规划路径
* 添加全屏模式，方便对地图操作

![](https://github.com/lrm2017/robot_hmi/blob/main/%E6%95%88%E6%9E%9C%E5%9B%BE/%E5%85%A8%E5%B1%8F%E5%AF%BC%E8%88%AA.png?raw=true)



## 改进

由于rviz不支持触屏手势，无法放大与平移，后续加入触屏手势



## 联系方式

邮箱：liangrongmin@foxmail.com 
