/****************************************************************************
** Meta object code from reading C++ file 'rvizpanel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../include/RvizPanel/rvizpanel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rvizpanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RvizPanel_t {
    QByteArrayData data[22];
    char stringdata0[267];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RvizPanel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RvizPanel_t qt_meta_stringdata_RvizPanel = {
    {
QT_MOC_LITERAL(0, 0, 9), // "RvizPanel"
QT_MOC_LITERAL(1, 10, 12), // "setTopicSlot"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 5), // "topic"
QT_MOC_LITERAL(4, 30, 17), // "setFixedFrameSlot"
QT_MOC_LITERAL(5, 48, 10), // "fixedframe"
QT_MOC_LITERAL(6, 59, 13), // "initPanelSlot"
QT_MOC_LITERAL(7, 73, 15), // "deinitPanelSlot"
QT_MOC_LITERAL(8, 89, 14), // "mapDisplaySlot"
QT_MOC_LITERAL(9, 104, 20), // "QVector<std::string>"
QT_MOC_LITERAL(10, 125, 16), // "LaserDisplaySlot"
QT_MOC_LITERAL(11, 142, 20), // "robotModelDisplySlot"
QT_MOC_LITERAL(12, 163, 14), // "Set_Start_Pose"
QT_MOC_LITERAL(13, 178, 13), // "Set_Goal_Pose"
QT_MOC_LITERAL(14, 192, 13), // "polyfootprint"
QT_MOC_LITERAL(15, 206, 4), // "poly"
QT_MOC_LITERAL(16, 211, 8), // "showPath"
QT_MOC_LITERAL(17, 220, 8), // "pathList"
QT_MOC_LITERAL(18, 229, 11), // "showCarPose"
QT_MOC_LITERAL(19, 241, 3), // "car"
QT_MOC_LITERAL(20, 245, 13), // "GetDisplayNum"
QT_MOC_LITERAL(21, 259, 7) // "ClassID"

    },
    "RvizPanel\0setTopicSlot\0\0topic\0"
    "setFixedFrameSlot\0fixedframe\0initPanelSlot\0"
    "deinitPanelSlot\0mapDisplaySlot\0"
    "QVector<std::string>\0LaserDisplaySlot\0"
    "robotModelDisplySlot\0Set_Start_Pose\0"
    "Set_Goal_Pose\0polyfootprint\0poly\0"
    "showPath\0pathList\0showCarPose\0car\0"
    "GetDisplayNum\0ClassID"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RvizPanel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x0a /* Public */,
       4,    1,   82,    2, 0x0a /* Public */,
       6,    0,   85,    2, 0x0a /* Public */,
       7,    0,   86,    2, 0x0a /* Public */,
       8,    1,   87,    2, 0x0a /* Public */,
      10,    1,   90,    2, 0x0a /* Public */,
      11,    0,   93,    2, 0x0a /* Public */,
      12,    0,   94,    2, 0x0a /* Public */,
      13,    0,   95,    2, 0x0a /* Public */,
      14,    1,   96,    2, 0x0a /* Public */,
      16,    1,   99,    2, 0x0a /* Public */,
      18,    2,  102,    2, 0x0a /* Public */,
      20,    1,  107,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   15,
    QMetaType::Void, 0x80000000 | 9,   17,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    3,   19,
    QMetaType::Int, QMetaType::QString,   21,

       0        // eod
};

void RvizPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RvizPanel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setTopicSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->setFixedFrameSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->initPanelSlot(); break;
        case 3: _t->deinitPanelSlot(); break;
        case 4: _t->mapDisplaySlot((*reinterpret_cast< const QVector<std::string>(*)>(_a[1]))); break;
        case 5: _t->LaserDisplaySlot((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->robotModelDisplySlot(); break;
        case 7: _t->Set_Start_Pose(); break;
        case 8: _t->Set_Goal_Pose(); break;
        case 9: _t->polyfootprint((*reinterpret_cast< const QVector<std::string>(*)>(_a[1]))); break;
        case 10: _t->showPath((*reinterpret_cast< const QVector<std::string>(*)>(_a[1]))); break;
        case 11: _t->showCarPose((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 12: { int _r = _t->GetDisplayNum((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RvizPanel::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_RvizPanel.data,
    qt_meta_data_RvizPanel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RvizPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RvizPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RvizPanel.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int RvizPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
struct qt_meta_stringdata_RvizImage_t {
    QByteArrayData data[6];
    char stringdata0[60];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RvizImage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RvizImage_t qt_meta_stringdata_RvizImage = {
    {
QT_MOC_LITERAL(0, 0, 9), // "RvizImage"
QT_MOC_LITERAL(1, 10, 12), // "setTopicSlot"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 5), // "topic"
QT_MOC_LITERAL(4, 30, 13), // "initPanelSlot"
QT_MOC_LITERAL(5, 44, 15) // "deinitPanelSlot"

    },
    "RvizImage\0setTopicSlot\0\0topic\0"
    "initPanelSlot\0deinitPanelSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RvizImage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x0a /* Public */,
       4,    0,   32,    2, 0x0a /* Public */,
       5,    0,   33,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void RvizImage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RvizImage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setTopicSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->initPanelSlot(); break;
        case 2: _t->deinitPanelSlot(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RvizImage::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_RvizImage.data,
    qt_meta_data_RvizImage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RvizImage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RvizImage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RvizImage.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int RvizImage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
