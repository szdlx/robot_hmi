/****************************************************************************
** Meta object code from reading C++ file 'joystick.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../include/module/joystick.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'joystick.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_JoyStick_t {
    QByteArrayData data[9];
    char stringdata0[67];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_JoyStick_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_JoyStick_t qt_meta_stringdata_JoyStick = {
    {
QT_MOC_LITERAL(0, 0, 8), // "JoyStick"
QT_MOC_LITERAL(1, 9, 13), // "keyNumchanged"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 3), // "num"
QT_MOC_LITERAL(4, 28, 13), // "keyPosChanged"
QT_MOC_LITERAL(5, 42, 3), // "pos"
QT_MOC_LITERAL(6, 46, 10), // "keyControl"
QT_MOC_LITERAL(7, 57, 3), // "vel"
QT_MOC_LITERAL(8, 61, 5) // "angle"

    },
    "JoyStick\0keyNumchanged\0\0num\0keyPosChanged\0"
    "pos\0keyControl\0vel\0angle"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_JoyStick[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       4,    1,   32,    2, 0x06 /* Public */,
       6,    2,   35,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QPointF,    5,
    QMetaType::Void, QMetaType::Float, QMetaType::Float,    7,    8,

       0        // eod
};

void JoyStick::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<JoyStick *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->keyNumchanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->keyPosChanged((*reinterpret_cast< QPointF(*)>(_a[1]))); break;
        case 2: _t->keyControl((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (JoyStick::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&JoyStick::keyNumchanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (JoyStick::*)(QPointF );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&JoyStick::keyPosChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (JoyStick::*)(float , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&JoyStick::keyControl)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject JoyStick::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_JoyStick.data,
    qt_meta_data_JoyStick,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *JoyStick::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *JoyStick::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_JoyStick.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int JoyStick::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void JoyStick::keyNumchanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void JoyStick::keyPosChanged(QPointF _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void JoyStick::keyControl(float _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
