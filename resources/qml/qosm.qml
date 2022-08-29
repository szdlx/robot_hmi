import QtQuick 2.5
import QtPositioning 5.9
import QtLocation 5.9
import QtQuick.Controls 2.0
import FileOperate 1.0    // Import this module, so we can use it in our QML script


Rectangle {

    id:window
    visible: true
    property var markerCoor     //存储点击的坐标
    property point dataCoor
    property int pCnt: 0

    Plugin {
        id:mapPlugin
        name:"osm"
        PluginParameter { name: "osm.mapping.providersrepository.disabled"; value: true }
    }

    FileOperate {           //导入C++类
        id:fp
    }

    function addMarker(latitude, longtitude)
    {
        var component = Qt.createComponent("marker.qml")
        if( component.status !== Component.Ready);
            console.log("test"+component.errorString()) ;
        var item = component.createObject(window, {
                                              coordinate:QtPositioning.coordinate(latitude,longtitude)
                                            }  )
        map.addMapItem(item)
    }

    Map {
        id:map
        anchors.fill: parent

        plugin: mapPlugin
        center: QtPositioning.coordinate(39.996,116.366)
        zoomLevel: 14

        Button {
            width: 62
            height: 30
            text: qsTr("确定")
            anchors.right: parent.right
            anchors.rightMargin: 8
            anchors.top:parent.top
            anchors.topMargin: 8
            wheelEnabled: false
            onPressed: {
                fp.pCnt = pCnt          //记录点击的次数
                fp.writeCoorData()      //写下标注坐标到txt文件
            }
        }

        Button {
            width: 62
            height: 30
            anchors.rightMargin: 8
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.topMargin: 49
            text: qsTr("清空")

            onPressed: {
                map.clearMapItems()     //清空地图上的标注
                pCnt=0                  //计数清零
            }
        }

        MouseArea{
            anchors.fill: parent
            acceptedButtons: Qt.RightButton
            onPressed: {
                markerCoor = map.toCoordinate(Qt.point(mouseX,mouseY))
                dataCoor.x = markerCoor.longitude       //记录经度
                dataCoor.y = markerCoor.latitude        //记录纬度
                fp.qpf = dataCoor
                pCnt++          //记录标注点的个数
                addMarker(markerCoor.latitude,markerCoor.longitude) //显示标注
                console.log(markerCoor.latitude,markerCoor.longitude)
            }
        }


    }

}
