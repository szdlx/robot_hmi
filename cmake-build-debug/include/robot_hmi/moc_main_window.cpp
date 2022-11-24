/****************************************************************************
** Meta object code from reading C++ file 'main_window.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../include/robot_hmi/main_window.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'main_window.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_robot_hmi__MainWindow_t {
    QByteArrayData data[34];
    char stringdata0[425];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_robot_hmi__MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_robot_hmi__MainWindow_t qt_meta_stringdata_robot_hmi__MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 21), // "robot_hmi::MainWindow"
QT_MOC_LITERAL(1, 22, 14), // "connectSuccess"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 3), // "car"
QT_MOC_LITERAL(4, 42, 13), // "connectFailed"
QT_MOC_LITERAL(5, 56, 21), // "slot_update_dashboard"
QT_MOC_LITERAL(6, 78, 17), // "slot_update_power"
QT_MOC_LITERAL(7, 96, 19), // "slot_set_start_pose"
QT_MOC_LITERAL(8, 116, 16), // "slot_car_connect"
QT_MOC_LITERAL(9, 133, 18), // "updateImgTopicList"
QT_MOC_LITERAL(10, 152, 18), // "updateMapTopicList"
QT_MOC_LITERAL(11, 171, 14), // "onTopicChanged"
QT_MOC_LITERAL(12, 186, 5), // "index"
QT_MOC_LITERAL(13, 192, 17), // "onTopicMapChanged"
QT_MOC_LITERAL(14, 210, 19), // "onTopicLaserChanged"
QT_MOC_LITERAL(15, 230, 9), // "saveImage"
QT_MOC_LITERAL(16, 240, 14), // "slot_set_param"
QT_MOC_LITERAL(17, 255, 14), // "road_value_set"
QT_MOC_LITERAL(18, 270, 9), // "timerSlot"
QT_MOC_LITERAL(19, 280, 10), // "startTimer"
QT_MOC_LITERAL(20, 291, 9), // "stopTimer"
QT_MOC_LITERAL(21, 301, 8), // "slot_gps"
QT_MOC_LITERAL(22, 310, 7), // "posqual"
QT_MOC_LITERAL(23, 318, 11), // "headingqual"
QT_MOC_LITERAL(24, 330, 1), // "x"
QT_MOC_LITERAL(25, 332, 1), // "y"
QT_MOC_LITERAL(26, 334, 3), // "yaw"
QT_MOC_LITERAL(27, 338, 14), // "set_track_path"
QT_MOC_LITERAL(28, 353, 10), // "local_coor"
QT_MOC_LITERAL(29, 364, 14), // "slot_stopTrack"
QT_MOC_LITERAL(30, 379, 20), // "slot_updateVelTopics"
QT_MOC_LITERAL(31, 400, 6), // "getXYT"
QT_MOC_LITERAL(32, 407, 13), // "state<double>"
QT_MOC_LITERAL(33, 421, 3) // "xyt"

    },
    "robot_hmi::MainWindow\0connectSuccess\0"
    "\0car\0connectFailed\0slot_update_dashboard\0"
    "slot_update_power\0slot_set_start_pose\0"
    "slot_car_connect\0updateImgTopicList\0"
    "updateMapTopicList\0onTopicChanged\0"
    "index\0onTopicMapChanged\0onTopicLaserChanged\0"
    "saveImage\0slot_set_param\0road_value_set\0"
    "timerSlot\0startTimer\0stopTimer\0slot_gps\0"
    "posqual\0headingqual\0x\0y\0yaw\0set_track_path\0"
    "local_coor\0slot_stopTrack\0"
    "slot_updateVelTopics\0getXYT\0state<double>\0"
    "xyt"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_robot_hmi__MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,  129,    2, 0x0a /* Public */,
       4,    1,  132,    2, 0x0a /* Public */,
       5,    2,  135,    2, 0x0a /* Public */,
       6,    1,  140,    2, 0x0a /* Public */,
       7,    0,  143,    2, 0x0a /* Public */,
       8,    1,  144,    2, 0x0a /* Public */,
       9,    0,  147,    2, 0x0a /* Public */,
      10,    0,  148,    2, 0x0a /* Public */,
      11,    1,  149,    2, 0x0a /* Public */,
      13,    1,  152,    2, 0x0a /* Public */,
      14,    1,  155,    2, 0x0a /* Public */,
      15,    0,  158,    2, 0x0a /* Public */,
      16,    1,  159,    2, 0x0a /* Public */,
      17,    0,  162,    2, 0x0a /* Public */,
      18,    0,  163,    2, 0x0a /* Public */,
      19,    0,  164,    2, 0x0a /* Public */,
      20,    0,  165,    2, 0x0a /* Public */,
      21,    5,  166,    2, 0x0a /* Public */,
      27,    0,  177,    2, 0x0a /* Public */,
      28,    3,  178,    2, 0x0a /* Public */,
      29,    0,  185,    2, 0x0a /* Public */,
      30,    0,  186,    2, 0x0a /* Public */,
      31,    1,  187,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Float, QMetaType::Float,    2,    2,
    QMetaType::Void, QMetaType::Float,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Double, QMetaType::Double, QMetaType::Double,   22,   23,   24,   25,   26,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,   24,   25,   26,
    QMetaType::Void,
    QMetaType::Void,
    0x80000000 | 32, 0x80000000 | 32,   33,

       0        // eod
};

void robot_hmi::MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connectSuccess((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->connectFailed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->slot_update_dashboard((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 3: _t->slot_update_power((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->slot_set_start_pose(); break;
        case 5: _t->slot_car_connect((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->updateImgTopicList(); break;
        case 7: _t->updateMapTopicList(); break;
        case 8: _t->onTopicChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->onTopicMapChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->onTopicLaserChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->saveImage(); break;
        case 12: _t->slot_set_param((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->road_value_set(); break;
        case 14: _t->timerSlot(); break;
        case 15: _t->startTimer(); break;
        case 16: _t->stopTimer(); break;
        case 17: _t->slot_gps((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5]))); break;
        case 18: _t->set_track_path(); break;
        case 19: _t->local_coor((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 20: _t->slot_stopTrack(); break;
        case 21: _t->slot_updateVelTopics(); break;
        case 22: { state<double> _r = _t->getXYT((*reinterpret_cast< state<double>(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< state<double>*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject robot_hmi::MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_robot_hmi__MainWindow.data,
    qt_meta_data_robot_hmi__MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *robot_hmi::MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *robot_hmi::MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_robot_hmi__MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int robot_hmi::MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 23)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 23;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
