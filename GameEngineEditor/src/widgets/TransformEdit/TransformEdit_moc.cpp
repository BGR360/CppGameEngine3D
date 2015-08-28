/****************************************************************************
** Meta object code from reading C++ file 'TransformEdit.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "TransformEdit.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TransformEdit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TransformEdit_t {
    QByteArrayData data[13];
    char stringdata[127];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TransformEdit_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TransformEdit_t qt_meta_stringdata_TransformEdit = {
    {
QT_MOC_LITERAL(0, 0, 13), // "TransformEdit"
QT_MOC_LITERAL(1, 14, 16), // "transformChanged"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 12), // "setTransform"
QT_MOC_LITERAL(4, 45, 10), // "Transform*"
QT_MOC_LITERAL(5, 56, 5), // "trans"
QT_MOC_LITERAL(6, 62, 11), // "setPosition"
QT_MOC_LITERAL(7, 74, 7), // "Vector3"
QT_MOC_LITERAL(8, 82, 8), // "position"
QT_MOC_LITERAL(9, 91, 11), // "setRotation"
QT_MOC_LITERAL(10, 103, 8), // "rotation"
QT_MOC_LITERAL(11, 112, 8), // "setScale"
QT_MOC_LITERAL(12, 121, 5) // "scale"

    },
    "TransformEdit\0transformChanged\0\0"
    "setTransform\0Transform*\0trans\0setPosition\0"
    "Vector3\0position\0setRotation\0rotation\0"
    "setScale\0scale"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TransformEdit[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   40,    2, 0x0a /* Public */,
       6,    1,   43,    2, 0x0a /* Public */,
       9,    1,   46,    2, 0x0a /* Public */,
      11,    1,   49,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,   10,
    QMetaType::Void, 0x80000000 | 7,   12,

       0        // eod
};

void TransformEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TransformEdit *_t = static_cast<TransformEdit *>(_o);
        switch (_id) {
        case 0: _t->transformChanged(); break;
        case 1: _t->setTransform((*reinterpret_cast< Transform*(*)>(_a[1]))); break;
        case 2: _t->setPosition((*reinterpret_cast< const Vector3(*)>(_a[1]))); break;
        case 3: _t->setRotation((*reinterpret_cast< const Vector3(*)>(_a[1]))); break;
        case 4: _t->setScale((*reinterpret_cast< const Vector3(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TransformEdit::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TransformEdit::transformChanged)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject TransformEdit::staticMetaObject = {
    { &QGroupBox::staticMetaObject, qt_meta_stringdata_TransformEdit.data,
      qt_meta_data_TransformEdit,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TransformEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TransformEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TransformEdit.stringdata))
        return static_cast<void*>(const_cast< TransformEdit*>(this));
    return QGroupBox::qt_metacast(_clname);
}

int TransformEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGroupBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void TransformEdit::transformChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
