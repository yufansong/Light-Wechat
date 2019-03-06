/****************************************************************************
** Meta object code from reading C++ file 'chatdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../chatdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chatdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ChatDialog_t {
    QByteArrayData data[13];
    char stringdata0[163];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ChatDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ChatDialog_t qt_meta_stringdata_ChatDialog = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ChatDialog"
QT_MOC_LITERAL(1, 11, 8), // "nextPage"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 14), // "changePassword"
QT_MOC_LITERAL(4, 36, 17), // "changePasswordEnd"
QT_MOC_LITERAL(5, 54, 3), // "end"
QT_MOC_LITERAL(6, 58, 10), // "valChanged"
QT_MOC_LITERAL(7, 69, 8), // "animDone"
QT_MOC_LITERAL(8, 78, 9), // "minWindow"
QT_MOC_LITERAL(9, 88, 23), // "on_activatedSysTrayIcon"
QT_MOC_LITERAL(10, 112, 33), // "QSystemTrayIcon::ActivationRe..."
QT_MOC_LITERAL(11, 146, 6), // "reason"
QT_MOC_LITERAL(12, 153, 9) // "rotateVal"

    },
    "ChatDialog\0nextPage\0\0changePassword\0"
    "changePasswordEnd\0end\0valChanged\0"
    "animDone\0minWindow\0on_activatedSysTrayIcon\0"
    "QSystemTrayIcon::ActivationReason\0"
    "reason\0rotateVal"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ChatDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       1,   66, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x0a /* Public */,
       3,    0,   55,    2, 0x0a /* Public */,
       4,    0,   56,    2, 0x0a /* Public */,
       5,    0,   57,    2, 0x0a /* Public */,
       6,    1,   58,    2, 0x08 /* Private */,
       7,    0,   61,    2, 0x08 /* Private */,
       8,    0,   62,    2, 0x08 /* Private */,
       9,    1,   63,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QVariant,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,

 // properties: name, type, flags
      12, QMetaType::Float, 0x00095103,

       0        // eod
};

void ChatDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ChatDialog *_t = static_cast<ChatDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->nextPage(); break;
        case 1: _t->changePassword(); break;
        case 2: _t->changePasswordEnd(); break;
        case 3: _t->end(); break;
        case 4: _t->valChanged((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 5: _t->animDone(); break;
        case 6: _t->minWindow(); break;
        case 7: _t->on_activatedSysTrayIcon((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        default: ;
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        ChatDialog *_t = static_cast<ChatDialog *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = _t->rotateVal(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        ChatDialog *_t = static_cast<ChatDialog *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setRotateVal(*reinterpret_cast< float*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject ChatDialog::staticMetaObject = {
    { &QStackedWidget::staticMetaObject, qt_meta_stringdata_ChatDialog.data,
      qt_meta_data_ChatDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ChatDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChatDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ChatDialog.stringdata0))
        return static_cast<void*>(const_cast< ChatDialog*>(this));
    return QStackedWidget::qt_metacast(_clname);
}

int ChatDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QStackedWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
