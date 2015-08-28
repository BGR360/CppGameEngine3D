/****************************************************************************
** Meta object code from reading C++ file 'floatingpointlineedit.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "floatingpointlineedit.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'floatingpointlineedit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FloatingPointLineEdit_t {
    QByteArrayData data[14];
    char stringdata[132];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FloatingPointLineEdit_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FloatingPointLineEdit_t qt_meta_stringdata_FloatingPointLineEdit = {
    {
QT_MOC_LITERAL(0, 0, 21), // "FloatingPointLineEdit"
QT_MOC_LITERAL(1, 22, 12), // "valueChanged"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 8), // "newValue"
QT_MOC_LITERAL(4, 45, 18), // "notifyValueChanged"
QT_MOC_LITERAL(5, 64, 8), // "setValue"
QT_MOC_LITERAL(6, 73, 3), // "val"
QT_MOC_LITERAL(7, 77, 10), // "setMinimum"
QT_MOC_LITERAL(8, 88, 3), // "min"
QT_MOC_LITERAL(9, 92, 10), // "setMaximum"
QT_MOC_LITERAL(10, 103, 3), // "max"
QT_MOC_LITERAL(11, 107, 8), // "setRange"
QT_MOC_LITERAL(12, 116, 11), // "setDecimals"
QT_MOC_LITERAL(13, 128, 3) // "dec"

    },
    "FloatingPointLineEdit\0valueChanged\0\0"
    "newValue\0notifyValueChanged\0setValue\0"
    "val\0setMinimum\0min\0setMaximum\0max\0"
    "setRange\0setDecimals\0dec"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FloatingPointLineEdit[] = {

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
       4,    0,   52,    2, 0x09 /* Protected */,
       5,    1,   53,    2, 0x0a /* Public */,
       7,    1,   56,    2, 0x0a /* Public */,
       9,    1,   59,    2, 0x0a /* Public */,
      11,    2,   62,    2, 0x0a /* Public */,
      12,    1,   67,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float,    6,
    QMetaType::Void, QMetaType::Float,    8,
    QMetaType::Void, QMetaType::Float,   10,
    QMetaType::Void, QMetaType::Float, QMetaType::Float,    8,   10,
    QMetaType::Void, QMetaType::Int,   13,

       0        // eod
};

void FloatingPointLineEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FloatingPointLineEdit *_t = static_cast<FloatingPointLineEdit *>(_o);
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 1: _t->notifyValueChanged(); break;
        case 2: _t->setValue((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->setMinimum((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->setMaximum((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 5: _t->setRange((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 6: _t->setDecimals((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FloatingPointLineEdit::*_t)(float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FloatingPointLineEdit::valueChanged)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject FloatingPointLineEdit::staticMetaObject = {
    { &QLineEdit::staticMetaObject, qt_meta_stringdata_FloatingPointLineEdit.data,
      qt_meta_data_FloatingPointLineEdit,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FloatingPointLineEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FloatingPointLineEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FloatingPointLineEdit.stringdata))
        return static_cast<void*>(const_cast< FloatingPointLineEdit*>(this));
    return QLineEdit::qt_metacast(_clname);
}

int FloatingPointLineEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLineEdit::qt_metacall(_c, _id, _a);
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
void FloatingPointLineEdit::valueChanged(float _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
