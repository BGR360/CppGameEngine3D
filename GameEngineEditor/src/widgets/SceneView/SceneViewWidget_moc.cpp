/****************************************************************************
** Meta object code from reading C++ file 'SceneViewWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "SceneViewWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SceneViewWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SceneViewWidget_t {
    QByteArrayData data[5];
    char stringdata[51];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SceneViewWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SceneViewWidget_t qt_meta_stringdata_SceneViewWidget = {
    {
QT_MOC_LITERAL(0, 0, 15), // "SceneViewWidget"
QT_MOC_LITERAL(1, 16, 12), // "mouseEntered"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 9), // "mouseLeft"
QT_MOC_LITERAL(4, 40, 10) // "updateSize"

    },
    "SceneViewWidget\0mouseEntered\0\0mouseLeft\0"
    "updateSize"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SceneViewWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    0,   30,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   31,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void SceneViewWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SceneViewWidget *_t = static_cast<SceneViewWidget *>(_o);
        switch (_id) {
        case 0: _t->mouseEntered(); break;
        case 1: _t->mouseLeft(); break;
        case 2: _t->updateSize(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SceneViewWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SceneViewWidget::mouseEntered)) {
                *result = 0;
            }
        }
        {
            typedef void (SceneViewWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SceneViewWidget::mouseLeft)) {
                *result = 1;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject SceneViewWidget::staticMetaObject = {
    { &RenderingEngine::staticMetaObject, qt_meta_stringdata_SceneViewWidget.data,
      qt_meta_data_SceneViewWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SceneViewWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SceneViewWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SceneViewWidget.stringdata))
        return static_cast<void*>(const_cast< SceneViewWidget*>(this));
    return RenderingEngine::qt_metacast(_clname);
}

int SceneViewWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = RenderingEngine::qt_metacall(_c, _id, _a);
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
void SceneViewWidget::mouseEntered()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void SceneViewWidget::mouseLeft()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
