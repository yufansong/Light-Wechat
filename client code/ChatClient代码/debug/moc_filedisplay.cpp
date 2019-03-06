/****************************************************************************
** Meta object code from reading C++ file 'filedisplay.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../filedisplay.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'filedisplay.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FileDisplay_t {
    QByteArrayData data[9];
    char stringdata0[148];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FileDisplay_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FileDisplay_t qt_meta_stringdata_FileDisplay = {
    {
QT_MOC_LITERAL(0, 0, 11), // "FileDisplay"
QT_MOC_LITERAL(1, 12, 19), // "on_listView_clicked"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 5), // "index"
QT_MOC_LITERAL(4, 39, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(5, 61, 23), // "on_pushButton_4_clicked"
QT_MOC_LITERAL(6, 85, 14), // "ClientReadData"
QT_MOC_LITERAL(7, 100, 23), // "on_pushButton_3_clicked"
QT_MOC_LITERAL(8, 124, 23) // "on_pushButton_2_clicked"

    },
    "FileDisplay\0on_listView_clicked\0\0index\0"
    "on_pushButton_clicked\0on_pushButton_4_clicked\0"
    "ClientReadData\0on_pushButton_3_clicked\0"
    "on_pushButton_2_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FileDisplay[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x08 /* Private */,
       4,    0,   47,    2, 0x08 /* Private */,
       5,    0,   48,    2, 0x08 /* Private */,
       6,    0,   49,    2, 0x08 /* Private */,
       7,    0,   50,    2, 0x08 /* Private */,
       8,    0,   51,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QModelIndex,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void FileDisplay::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FileDisplay *_t = static_cast<FileDisplay *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_listView_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 1: _t->on_pushButton_clicked(); break;
        case 2: _t->on_pushButton_4_clicked(); break;
        case 3: _t->ClientReadData(); break;
        case 4: _t->on_pushButton_3_clicked(); break;
        case 5: _t->on_pushButton_2_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject FileDisplay::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_FileDisplay.data,
      qt_meta_data_FileDisplay,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FileDisplay::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FileDisplay::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FileDisplay.stringdata0))
        return static_cast<void*>(const_cast< FileDisplay*>(this));
    return QDialog::qt_metacast(_clname);
}

int FileDisplay::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
