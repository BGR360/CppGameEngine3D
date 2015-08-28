/****************************************************************************
** Meta object code from reading C++ file 'ModelTest.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ModelTest.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ModelTest.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ModelTest_t {
    QByteArrayData data[18];
    char stringdata[210];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ModelTest_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ModelTest_t qt_meta_stringdata_ModelTest = {
    {
QT_MOC_LITERAL(0, 0, 9), // "ModelTest"
QT_MOC_LITERAL(1, 10, 23), // "nonDestructiveBasicTest"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 8), // "rowCount"
QT_MOC_LITERAL(4, 44, 11), // "columnCount"
QT_MOC_LITERAL(5, 56, 8), // "hasIndex"
QT_MOC_LITERAL(6, 65, 5), // "index"
QT_MOC_LITERAL(7, 71, 6), // "parent"
QT_MOC_LITERAL(8, 78, 4), // "data"
QT_MOC_LITERAL(9, 83, 11), // "runAllTests"
QT_MOC_LITERAL(10, 95, 22), // "layoutAboutToBeChanged"
QT_MOC_LITERAL(11, 118, 13), // "layoutChanged"
QT_MOC_LITERAL(12, 132, 21), // "rowsAboutToBeInserted"
QT_MOC_LITERAL(13, 154, 5), // "start"
QT_MOC_LITERAL(14, 160, 3), // "end"
QT_MOC_LITERAL(15, 164, 12), // "rowsInserted"
QT_MOC_LITERAL(16, 177, 20), // "rowsAboutToBeRemoved"
QT_MOC_LITERAL(17, 198, 11) // "rowsRemoved"

    },
    "ModelTest\0nonDestructiveBasicTest\0\0"
    "rowCount\0columnCount\0hasIndex\0index\0"
    "parent\0data\0runAllTests\0layoutAboutToBeChanged\0"
    "layoutChanged\0rowsAboutToBeInserted\0"
    "start\0end\0rowsInserted\0rowsAboutToBeRemoved\0"
    "rowsRemoved"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ModelTest[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    0,   85,    2, 0x08 /* Private */,
       4,    0,   86,    2, 0x08 /* Private */,
       5,    0,   87,    2, 0x08 /* Private */,
       6,    0,   88,    2, 0x08 /* Private */,
       7,    0,   89,    2, 0x08 /* Private */,
       8,    0,   90,    2, 0x08 /* Private */,
       9,    0,   91,    2, 0x09 /* Protected */,
      10,    0,   92,    2, 0x09 /* Protected */,
      11,    0,   93,    2, 0x09 /* Protected */,
      12,    3,   94,    2, 0x09 /* Protected */,
      15,    3,  101,    2, 0x09 /* Protected */,
      16,    3,  108,    2, 0x09 /* Protected */,
      17,    3,  115,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex, QMetaType::Int, QMetaType::Int,    7,   13,   14,
    QMetaType::Void, QMetaType::QModelIndex, QMetaType::Int, QMetaType::Int,    7,   13,   14,
    QMetaType::Void, QMetaType::QModelIndex, QMetaType::Int, QMetaType::Int,    7,   13,   14,
    QMetaType::Void, QMetaType::QModelIndex, QMetaType::Int, QMetaType::Int,    7,   13,   14,

       0        // eod
};

void ModelTest::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ModelTest *_t = static_cast<ModelTest *>(_o);
        switch (_id) {
        case 0: _t->nonDestructiveBasicTest(); break;
        case 1: _t->rowCount(); break;
        case 2: _t->columnCount(); break;
        case 3: _t->hasIndex(); break;
        case 4: _t->index(); break;
        case 5: _t->parent(); break;
        case 6: _t->data(); break;
        case 7: _t->runAllTests(); break;
        case 8: _t->layoutAboutToBeChanged(); break;
        case 9: _t->layoutChanged(); break;
        case 10: _t->rowsAboutToBeInserted((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 11: _t->rowsInserted((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 12: _t->rowsAboutToBeRemoved((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 13: _t->rowsRemoved((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObject ModelTest::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ModelTest.data,
      qt_meta_data_ModelTest,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ModelTest::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ModelTest::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ModelTest.stringdata))
        return static_cast<void*>(const_cast< ModelTest*>(this));
    return QObject::qt_metacast(_clname);
}

int ModelTest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
