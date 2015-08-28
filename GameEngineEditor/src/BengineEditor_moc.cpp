/****************************************************************************
** Meta object code from reading C++ file 'BengineEditor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "BengineEditor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BengineEditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_BengineEditor_t {
    QByteArrayData data[23];
    char stringdata[273];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BengineEditor_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BengineEditor_t qt_meta_stringdata_BengineEditor = {
    {
QT_MOC_LITERAL(0, 0, 13), // "BengineEditor"
QT_MOC_LITERAL(1, 14, 12), // "sceneChanged"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 4), // "show"
QT_MOC_LITERAL(4, 33, 4), // "undo"
QT_MOC_LITERAL(5, 38, 4), // "redo"
QT_MOC_LITERAL(6, 43, 8), // "loadGame"
QT_MOC_LITERAL(7, 52, 9), // "pauseGame"
QT_MOC_LITERAL(8, 62, 10), // "resumeGame"
QT_MOC_LITERAL(9, 73, 10), // "updateGame"
QT_MOC_LITERAL(10, 84, 18), // "setupHierarchyView"
QT_MOC_LITERAL(11, 103, 17), // "setupResourceView"
QT_MOC_LITERAL(12, 121, 8), // "newScene"
QT_MOC_LITERAL(13, 130, 9), // "openScene"
QT_MOC_LITERAL(14, 140, 10), // "closeScene"
QT_MOC_LITERAL(15, 151, 14), // "editGameObject"
QT_MOC_LITERAL(16, 166, 13), // "addGameObject"
QT_MOC_LITERAL(17, 180, 16), // "removeGameObject"
QT_MOC_LITERAL(18, 197, 17), // "focusOnGameObject"
QT_MOC_LITERAL(19, 215, 11), // "addResource"
QT_MOC_LITERAL(20, 227, 14), // "removeResource"
QT_MOC_LITERAL(21, 242, 24), // "updateSelectedGameObject"
QT_MOC_LITERAL(22, 267, 5) // "index"

    },
    "BengineEditor\0sceneChanged\0\0show\0undo\0"
    "redo\0loadGame\0pauseGame\0resumeGame\0"
    "updateGame\0setupHierarchyView\0"
    "setupResourceView\0newScene\0openScene\0"
    "closeScene\0editGameObject\0addGameObject\0"
    "removeGameObject\0focusOnGameObject\0"
    "addResource\0removeResource\0"
    "updateSelectedGameObject\0index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BengineEditor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  114,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,  115,    2, 0x0a /* Public */,
       4,    0,  116,    2, 0x0a /* Public */,
       5,    0,  117,    2, 0x0a /* Public */,
       6,    0,  118,    2, 0x0a /* Public */,
       7,    0,  119,    2, 0x0a /* Public */,
       8,    0,  120,    2, 0x0a /* Public */,
       9,    0,  121,    2, 0x0a /* Public */,
      10,    0,  122,    2, 0x0a /* Public */,
      11,    0,  123,    2, 0x0a /* Public */,
      12,    0,  124,    2, 0x0a /* Public */,
      13,    0,  125,    2, 0x0a /* Public */,
      14,    0,  126,    2, 0x0a /* Public */,
      15,    0,  127,    2, 0x0a /* Public */,
      16,    0,  128,    2, 0x0a /* Public */,
      17,    0,  129,    2, 0x0a /* Public */,
      18,    0,  130,    2, 0x0a /* Public */,
      19,    0,  131,    2, 0x0a /* Public */,
      20,    0,  132,    2, 0x0a /* Public */,
      21,    1,  133,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   22,

       0        // eod
};

void BengineEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BengineEditor *_t = static_cast<BengineEditor *>(_o);
        switch (_id) {
        case 0: _t->sceneChanged(); break;
        case 1: _t->show(); break;
        case 2: _t->undo(); break;
        case 3: _t->redo(); break;
        case 4: _t->loadGame(); break;
        case 5: _t->pauseGame(); break;
        case 6: _t->resumeGame(); break;
        case 7: _t->updateGame(); break;
        case 8: _t->setupHierarchyView(); break;
        case 9: _t->setupResourceView(); break;
        case 10: _t->newScene(); break;
        case 11: _t->openScene(); break;
        case 12: _t->closeScene(); break;
        case 13: _t->editGameObject(); break;
        case 14: _t->addGameObject(); break;
        case 15: _t->removeGameObject(); break;
        case 16: _t->focusOnGameObject(); break;
        case 17: _t->addResource(); break;
        case 18: _t->removeResource(); break;
        case 19: _t->updateSelectedGameObject((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (BengineEditor::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BengineEditor::sceneChanged)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject BengineEditor::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_BengineEditor.data,
      qt_meta_data_BengineEditor,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *BengineEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BengineEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_BengineEditor.stringdata))
        return static_cast<void*>(const_cast< BengineEditor*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int BengineEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void BengineEditor::sceneChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
