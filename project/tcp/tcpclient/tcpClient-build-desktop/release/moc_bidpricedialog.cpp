/****************************************************************************
** Meta object code from reading C++ file 'bidpricedialog.h'
**
** Created: Sun Dec 6 21:39:38 2015
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../tcpClient/bidpricedialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bidpricedialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BidPriceDialog[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   16,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      44,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_BidPriceDialog[] = {
    "BidPriceDialog\0\0price\0itempriceget(QString)\0"
    "on_pushButton_clicked()\0"
};

const QMetaObject BidPriceDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_BidPriceDialog,
      qt_meta_data_BidPriceDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BidPriceDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BidPriceDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BidPriceDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BidPriceDialog))
        return static_cast<void*>(const_cast< BidPriceDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int BidPriceDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: itempriceget((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: on_pushButton_clicked(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void BidPriceDialog::itempriceget(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
