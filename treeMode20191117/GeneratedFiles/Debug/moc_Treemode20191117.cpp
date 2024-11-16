/****************************************************************************
** Meta object code from reading C++ file 'Treemode20191117.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Treemode20191117.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Treemode20191117.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TreeMode20191117_t {
    QByteArrayData data[7];
    char stringdata0[90];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TreeMode20191117_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TreeMode20191117_t qt_meta_stringdata_TreeMode20191117 = {
    {
QT_MOC_LITERAL(0, 0, 16), // "TreeMode20191117"
QT_MOC_LITERAL(1, 17, 19), // "slotShowNewTreeView"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 19), // "slotTreeViewPressed"
QT_MOC_LITERAL(4, 58, 5), // "index"
QT_MOC_LITERAL(5, 64, 21), // "onSearchButtonclicked"
QT_MOC_LITERAL(6, 86, 3) // "str"

    },
    "TreeMode20191117\0slotShowNewTreeView\0"
    "\0slotTreeViewPressed\0index\0"
    "onSearchButtonclicked\0str"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TreeMode20191117[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x0a /* Public */,
       3,    1,   30,    2, 0x0a /* Public */,
       5,    1,   33,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    4,
    QMetaType::Void, QMetaType::QString,    6,

       0        // eod
};

void TreeMode20191117::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TreeMode20191117 *_t = static_cast<TreeMode20191117 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotShowNewTreeView(); break;
        case 1: _t->slotTreeViewPressed((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 2: _t->onSearchButtonclicked((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject TreeMode20191117::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_TreeMode20191117.data,
      qt_meta_data_TreeMode20191117,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TreeMode20191117::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TreeMode20191117::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TreeMode20191117.stringdata0))
        return static_cast<void*>(const_cast< TreeMode20191117*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int TreeMode20191117::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
