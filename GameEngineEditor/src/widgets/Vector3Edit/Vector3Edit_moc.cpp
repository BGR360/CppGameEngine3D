/****************************************************************************
** Meta object code from reading C++ file 'Vector3Edit.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Vector3Edit.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Vector3Edit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Vector3Edit_t {
    QByteArrayData data[26];
    char stringdata[239];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Vector3Edit_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Vector3Edit_t qt_meta_stringdata_Vector3Edit = {
    {
QT_MOC_LITERAL(0, 0, 11), // "Vector3Edit"
QT_MOC_LITERAL(1, 12, 12), // "valueChanged"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 7), // "Vector3"
QT_MOC_LITERAL(4, 34, 8), // "newValue"
QT_MOC_LITERAL(5, 43, 18), // "notifyValueChanged"
QT_MOC_LITERAL(6, 62, 8), // "setValue"
QT_MOC_LITERAL(7, 71, 3), // "val"
QT_MOC_LITERAL(8, 75, 10), // "setMinimum"
QT_MOC_LITERAL(9, 86, 3), // "min"
QT_MOC_LITERAL(10, 90, 10), // "setMaximum"
QT_MOC_LITERAL(11, 101, 3), // "max"
QT_MOC_LITERAL(12, 105, 8), // "setRange"
QT_MOC_LITERAL(13, 114, 14), // "setGranularity"
QT_MOC_LITERAL(14, 129, 4), // "gran"
QT_MOC_LITERAL(15, 134, 8), // "setLabel"
QT_MOC_LITERAL(16, 143, 5), // "label"
QT_MOC_LITERAL(17, 149, 9), // "setxLabel"
QT_MOC_LITERAL(18, 159, 9), // "setyLabel"
QT_MOC_LITERAL(19, 169, 9), // "setzLabel"
QT_MOC_LITERAL(20, 179, 18), // "setComponentLabels"
QT_MOC_LITERAL(21, 198, 6), // "xLabel"
QT_MOC_LITERAL(22, 205, 6), // "yLabel"
QT_MOC_LITERAL(23, 212, 6), // "zLabel"
QT_MOC_LITERAL(24, 219, 9), // "setLabels"
QT_MOC_LITERAL(25, 229, 9) // "mainLabel"

    },
    "Vector3Edit\0valueChanged\0\0Vector3\0"
    "newValue\0notifyValueChanged\0setValue\0"
    "val\0setMinimum\0min\0setMaximum\0max\0"
    "setRange\0setGranularity\0gran\0setLabel\0"
    "label\0setxLabel\0setyLabel\0setzLabel\0"
    "setComponentLabels\0xLabel\0yLabel\0"
    "zLabel\0setLabels\0mainLabel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Vector3Edit[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   82,    2, 0x09 /* Protected */,
       6,    1,   83,    2, 0x0a /* Public */,
       8,    1,   86,    2, 0x0a /* Public */,
      10,    1,   89,    2, 0x0a /* Public */,
      12,    2,   92,    2, 0x0a /* Public */,
      13,    1,   97,    2, 0x0a /* Public */,
      15,    1,  100,    2, 0x0a /* Public */,
      17,    1,  103,    2, 0x0a /* Public */,
      18,    1,  106,    2, 0x0a /* Public */,
      19,    1,  109,    2, 0x0a /* Public */,
      20,    3,  112,    2, 0x0a /* Public */,
      24,    4,  119,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    7,
    QMetaType::Void, QMetaType::Float,    9,
    QMetaType::Void, QMetaType::Float,   11,
    QMetaType::Void, QMetaType::Float, QMetaType::Float,    9,   11,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   21,   22,   23,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   25,   21,   22,   23,

       0        // eod
};

void Vector3Edit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Vector3Edit *_t = static_cast<Vector3Edit *>(_o);
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< const Vector3(*)>(_a[1]))); break;
        case 1: _t->notifyValueChanged(); break;
        case 2: _t->setValue((*reinterpret_cast< const Vector3(*)>(_a[1]))); break;
        case 3: _t->setMinimum((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->setMaximum((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 5: _t->setRange((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 6: _t->setGranularity((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->setLabel((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->setxLabel((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->setyLabel((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->setzLabel((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->setComponentLabels((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 12: _t->setLabels((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Vector3Edit::*_t)(const Vector3 & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Vector3Edit::valueChanged)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject Vector3Edit::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Vector3Edit.data,
      qt_meta_data_Vector3Edit,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Vector3Edit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Vector3Edit::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Vector3Edit.stringdata))
        return static_cast<void*>(const_cast< Vector3Edit*>(this));
    return QWidget::qt_metacast(_clname);
}

int Vector3Edit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void Vector3Edit::valueChanged(const Vector3 & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
