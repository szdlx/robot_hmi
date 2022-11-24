/****************************************************************************
** Meta object code from reading C++ file 'qnode.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../include/robot_hmi/qnode.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qnode.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_robot_hmi__QNode_t {
    QByteArrayData data[28];
    char stringdata0[256];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_robot_hmi__QNode_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_robot_hmi__QNode_t qt_meta_stringdata_robot_hmi__QNode = {
    {
QT_MOC_LITERAL(0, 0, 16), // "robot_hmi::QNode"
QT_MOC_LITERAL(1, 17, 14), // "loggingUpdated"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 11), // "rosShutdown"
QT_MOC_LITERAL(4, 45, 9), // "speed_vel"
QT_MOC_LITERAL(5, 55, 3), // "vel"
QT_MOC_LITERAL(6, 59, 4), // "angv"
QT_MOC_LITERAL(7, 64, 9), // "power_vel"
QT_MOC_LITERAL(8, 74, 8), // "position"
QT_MOC_LITERAL(9, 83, 1), // "x"
QT_MOC_LITERAL(10, 85, 1), // "y"
QT_MOC_LITERAL(11, 87, 1), // "z"
QT_MOC_LITERAL(12, 89, 6), // "pose2D"
QT_MOC_LITERAL(13, 96, 3), // "yaw"
QT_MOC_LITERAL(14, 100, 10), // "showMarker"
QT_MOC_LITERAL(15, 111, 5), // "topic"
QT_MOC_LITERAL(16, 117, 3), // "car"
QT_MOC_LITERAL(17, 121, 20), // "connectMasterSuccess"
QT_MOC_LITERAL(18, 142, 19), // "connectMasterFailed"
QT_MOC_LITERAL(19, 162, 7), // "gps_pos"
QT_MOC_LITERAL(20, 170, 7), // "posqual"
QT_MOC_LITERAL(21, 178, 11), // "headingqual"
QT_MOC_LITERAL(22, 190, 7), // "heading"
QT_MOC_LITERAL(23, 198, 8), // "obs_meet"
QT_MOC_LITERAL(24, 207, 3), // "dis"
QT_MOC_LITERAL(25, 211, 16), // "vel_list_changed"
QT_MOC_LITERAL(26, 228, 10), // "cmd_output"
QT_MOC_LITERAL(27, 239, 16) // "cmd_error_output"

    },
    "robot_hmi::QNode\0loggingUpdated\0\0"
    "rosShutdown\0speed_vel\0vel\0angv\0power_vel\0"
    "position\0x\0y\0z\0pose2D\0yaw\0showMarker\0"
    "topic\0car\0connectMasterSuccess\0"
    "connectMasterFailed\0gps_pos\0posqual\0"
    "headingqual\0heading\0obs_meet\0dis\0"
    "vel_list_changed\0cmd_output\0"
    "cmd_error_output"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_robot_hmi__QNode[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      12,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x06 /* Public */,
       3,    0,   85,    2, 0x06 /* Public */,
       4,    2,   86,    2, 0x06 /* Public */,
       7,    1,   91,    2, 0x06 /* Public */,
       8,    3,   94,    2, 0x06 /* Public */,
      12,    3,  101,    2, 0x06 /* Public */,
      14,    2,  108,    2, 0x06 /* Public */,
      17,    1,  113,    2, 0x06 /* Public */,
      18,    1,  116,    2, 0x06 /* Public */,
      19,    5,  119,    2, 0x06 /* Public */,
      23,    2,  130,    2, 0x06 /* Public */,
      25,    0,  135,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      26,    1,  136,    2, 0x0a /* Public */,
      27,    1,  139,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float, QMetaType::Float,    5,    6,
    QMetaType::Void, QMetaType::Float,    2,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,    9,   10,   11,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,    9,   10,   13,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   15,   16,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Double, QMetaType::Double, QMetaType::Double,   20,   21,    9,   10,   22,
    QMetaType::Void, QMetaType::Float, QMetaType::Int,   24,   16,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::Int,   16,

       0        // eod
};

void robot_hmi::QNode::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QNode *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->loggingUpdated(); break;
        case 1: _t->rosShutdown(); break;
        case 2: _t->speed_vel((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 3: _t->power_vel((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->position((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 5: _t->pose2D((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 6: _t->showMarker((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->connectMasterSuccess((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->connectMasterFailed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->gps_pos((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5]))); break;
        case 10: _t->obs_meet((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: _t->vel_list_changed(); break;
        case 12: _t->cmd_output((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->cmd_error_output((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QNode::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QNode::loggingUpdated)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QNode::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QNode::rosShutdown)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (QNode::*)(float , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QNode::speed_vel)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (QNode::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QNode::power_vel)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (QNode::*)(double , double , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QNode::position)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (QNode::*)(double , double , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QNode::pose2D)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (QNode::*)(QString , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QNode::showMarker)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (QNode::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QNode::connectMasterSuccess)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (QNode::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QNode::connectMasterFailed)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (QNode::*)(int , int , double , double , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QNode::gps_pos)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (QNode::*)(float , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QNode::obs_meet)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (QNode::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QNode::vel_list_changed)) {
                *result = 11;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject robot_hmi::QNode::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_robot_hmi__QNode.data,
    qt_meta_data_robot_hmi__QNode,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *robot_hmi::QNode::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *robot_hmi::QNode::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_robot_hmi__QNode.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int robot_hmi::QNode::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void robot_hmi::QNode::loggingUpdated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void robot_hmi::QNode::rosShutdown()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void robot_hmi::QNode::speed_vel(float _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void robot_hmi::QNode::power_vel(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void robot_hmi::QNode::position(double _t1, double _t2, double _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void robot_hmi::QNode::pose2D(double _t1, double _t2, double _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void robot_hmi::QNode::showMarker(QString _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void robot_hmi::QNode::connectMasterSuccess(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void robot_hmi::QNode::connectMasterFailed(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void robot_hmi::QNode::gps_pos(int _t1, int _t2, double _t3, double _t4, double _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void robot_hmi::QNode::obs_meet(float _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void robot_hmi::QNode::vel_list_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
