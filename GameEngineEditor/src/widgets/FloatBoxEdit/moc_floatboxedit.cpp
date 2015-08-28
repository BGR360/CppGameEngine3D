/****************************************************************************
** Meta object code from reading C++ file 'floatboxedit.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "floatboxedit.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'floatboxedit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FloatBoxEdit_t {
    QByteArrayData data[15];
    char stringdata[123];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FloatBoxEdit_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FloatBoxEdit_t qt_meta_stringdata_FloatBoxEdit = {
    {
QT_MOC_LITERAL(0, 0, 12), // "FloatBoxEdit"
QT_MOC_LITERAL(1, 13, 12), // "valueChanged"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 8), // "newValue"
QT_MOC_LITERAL(4, 36, 8), // "setValue"
QT_MOC_LITERAL(5, 45, 3), // "val"
QT_MOC_LITERAL(6, 49, 10), // "setMinimum"
QT_MOC_LITERAL(7, 60, 3), // "min"
QT_MOC_LITERAL(8, 64, 10), // "setMaximum"
QT_MOC_LITERAL(9, 75, 3), // "max"
QT_MOC_LITERAL(10, 79, 8), // "setRange"
QT_MOC_LITERAL(11, 88, 14), // "setGranularity"
QT_MOC_LITERAL(12, 103, 4), // "gran"
QT_MOC_LITERAL(13, 108, 8), // "setLabel"
QT_MOC_LITERAL(14, 117, 5) // "label"

    },
    "FloatBoxEdit\0valueChanged\0\0newValue\0"
    "setValue\0val\0setMinimum\0min\0setMaximum\0"
    "max\0setRange\0setGranularity\0gran\0"
    "setLabel\0label"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FloatBoxEdit[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   52,    2, 0x0a /* Public */,
       6,    1,   55,    2, 0x0a /* Public */,
       8,    1,   58,    2, 0x0a /* Public */,
      10,    2,   61,    2, 0x0a /* Public */,
      11,    1,   66,    2, 0x0a /* Public */,
      13,    1,   69,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Float,    5,
    QMetaType::Void, QMetaType::Float,    7,
    QMetaType::Void, QMetaType::Float,    9,
    QMetaType::Void, QMetaType::Float, QMetaType::Float,    7,    9,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::QString,   14,

       0        // eod
};

void FloatBoxEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FloatBoxEdit *_t = static_cast<FloatBoxEdit *>(_o);
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 1: _t->setValue((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->setMinimum((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->setMaximum((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->setRange((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 5: _t->setGranularity((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->setLabel((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FloatBoxEdit::*_t)(float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FloatBoxEdit::valueChanged)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject FloatBoxEdit::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FloatBoxEdit.data,
      qt_meta_data_FloatBoxEdit,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FloatBoxEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FloatBoxEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FloatBoxEdit.stringdata))
        return static_cast<void*>(const_cast< FloatBoxEdit*>(this));
    return QWidget::qt_metacast(_clname);
}

int FloatBoxEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void FloatBoxEdit::valueChanged(float _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
