/****************************************************************************
** Meta object code from reading C++ file 'client.h'
**
** Created: Sun Dec 6 21:39:36 2015
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../tcpClient/client.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'client.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Client[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,    8,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
      33,    7,    7,    7, 0x08,
      46,    7,    7,    7, 0x08,
      60,    7,    7,    7, 0x08,
     103,    7,    7,    7, 0x08,
     130,    7,    7,    7, 0x08,
     154,    7,    7,    7, 0x08,
     177,  168,    7,    7, 0x08,
     218,  198,    7,    7, 0x08,
     256,  246,    7,    7, 0x08,
     282,    7,    7,    7, 0x08,
     301,    7,    7,    7, 0x08,
     332,    7,    7,    7, 0x08,
     368,    7,    7,    7, 0x08,
     399,    7,    7,    7, 0x08,
     427,    7,    7,    7, 0x08,
     468,    7,    7,    7, 0x08,
     501,    7,    7,    7, 0x08,
     543,    7,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Client[] = {
    "Client\0\0data\0allbidinfo(QString)\0"
    "newConnect()\0readMessage()\0"
    "displayError(QAbstractSocket::SocketError)\0"
    "on_connectButton_clicked()\0"
    "on_pushButton_clicked()\0ifconnected()\0"
    "itemname\0submititems(QString)\0"
    "itemscode,itemprice\0getbiditem(QString,QString)\0"
    "itemscode\0withdrawiteminfo(QString)\0"
    "serverdisconnect()\0on_regist_pushButton_clicked()\0"
    "on_see_all_bid_pushButton_clicked()\0"
    "on_submit_pushButton_clicked()\0"
    "on_bid_pushButton_clicked()\0"
    "on_see_all_your_bid_pushButton_clicked()\0"
    "on_withdraw_pushButton_clicked()\0"
    "on_see_all_your_item_pushButton_clicked()\0"
    "on_deregist_pushButton_clicked()\0"
};

const QMetaObject Client::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Client,
      qt_meta_data_Client, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Client::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Client::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Client::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Client))
        return static_cast<void*>(const_cast< Client*>(this));
    return QDialog::qt_metacast(_clname);
}

int Client::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: allbidinfo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: newConnect(); break;
        case 2: readMessage(); break;
        case 3: displayError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 4: on_connectButton_clicked(); break;
        case 5: on_pushButton_clicked(); break;
        case 6: ifconnected(); break;
        case 7: submititems((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: getbiditem((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 9: withdrawiteminfo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: serverdisconnect(); break;
        case 11: on_regist_pushButton_clicked(); break;
        case 12: on_see_all_bid_pushButton_clicked(); break;
        case 13: on_submit_pushButton_clicked(); break;
        case 14: on_bid_pushButton_clicked(); break;
        case 15: on_see_all_your_bid_pushButton_clicked(); break;
        case 16: on_withdraw_pushButton_clicked(); break;
        case 17: on_see_all_your_item_pushButton_clicked(); break;
        case 18: on_deregist_pushButton_clicked(); break;
        default: ;
        }
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void Client::allbidinfo(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
