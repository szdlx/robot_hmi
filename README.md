# 多场景ROS人机交互界面

## 感谢

主框架来源于其他[开源项目](https://github.com/chengyangkj/Ros_Qt5_Gui_App/tree/rviz_tree)，在此基础上修复问题，添加自己的功能

## 安装依赖

```bash
sudo apt-get install libqt5location5 libqt5multimedia5 libqt5quickcontrols2-5
```

## 运行

```bash
rosrun cyrobot_monitor cyrobot_monitor 
```

## 开机主界面

![](https://github.com/lrm2017/robot_hmi/blob/robot_qt_need/image/%E5%9B%BE%E7%89%871.png?raw=true)

对于阿克曼消息类型，自动切换到摇杆控制，对应差速消息类型，切换到全向控制

![](https://github.com/lrm2017/robot_hmi/blob/robot_qt_need/image/%E5%9B%BE%E7%89%876.png?raw=true)

![](https://github.com/lrm2017/robot_hmi/blob/robot_qt_need/image/%E5%9B%BE%E7%89%872.png?raw=true)

### 图像窗口

图像显示窗口，可以右键选择显示的图像数量

![](https://github.com/lrm2017/robot_hmi/blob/robot_qt_need/image/%E5%9B%BE%E5%83%8F%E6%98%BE%E7%A4%BA%E7%AA%97%E5%8F%A3.png?raw=true)

在此设置图像话题

![](https://github.com/lrm2017/robot_hmi/blob/robot_qt_need/image/%E5%9B%BE%E5%83%8F%E8%AF%9D%E9%A2%98.png?raw=true)

### rviz

集成了rviz模块

![](rviz%E6%98%BE%E7%A4%BA2.png)

###  数据显示模块

需要设置对应的话题与参考坐标系

![](https://github.com/lrm2017/robot_hmi/blob/robot_qt_need/image/%E5%9B%BE%E7%89%877.png?raw=true)

![](https://github.com/lrm2017/robot_hmi/blob/robot_qt_need/image/%E5%9B%BE%E7%89%878.png?raw=true)

### 道路信息显示

显示道路类型的图片

![](https://github.com/lrm2017/robot_hmi/blob/robot_qt_need/image/%E5%9B%BE%E7%89%873.png?raw=true)

从csv加载道路信息，然后显示局部路径与全局路径

![](https://github.com/lrm2017/robot_hmi/blob/robot_qt_need/image/%E5%9B%BE%E7%89%874.png?raw=true)

### 地图

采用qml写的地图，地图来源与openstreetmap

![](https://github.com/lrm2017/robot_hmi/blob/robot_qt_need/image/%E5%9B%BE%E7%89%879.png?raw=true)
