/****************************************************************************
** Meta object code from reading C++ file 'biditemdialog.h'
**
** Created: Sun Dec 6 13:43:48 2015
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../tcpClient/biditemdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'biditemdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BidItemDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      30,   15,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      66,   60,   14,   14, 0x08,
      93,   88,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_BidItemDialog[] = {
    "BidItemDialog\0\0itemcode,price\0"
    "biditemsinfo(QString,QString)\0price\0"
    "itempricegot(QString)\0item\0"
    "on_listWidget_itemDoubleClicked(QListWidgetItem*)\0"
};

const QMetaObject BidItemDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_BidItemDialog,
      qt_meta_data_BidItemDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BidItemDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BidItemDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BidItemDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BidItemDialog))
        return static_cast<void*>(const_cast< BidItemDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int BidItemDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: biditemsinfo((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: itempricegot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: on_listWidget_itemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void BidItemDialog::biditemsinfo(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
