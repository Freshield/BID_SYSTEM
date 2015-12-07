/****************************************************************************
** Meta object code from reading C++ file 'server.h'
**
** Created: Sun Dec 6 21:05:44 2015
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../tcpServer/server.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'server.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Server[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x08,
      50,   32,    7,    7, 0x08,
      88,   79,    7,    7, 0x08,
     109,    7,    7,    7, 0x08,
     140,  127,    7,    7, 0x08,
     165,    7,    7,    7, 0x08,
     188,    7,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Server[] = {
    "Server\0\0on_pushButton_clicked()\0"
    "strIPandPort,data\0readMessage(QString,QString)\0"
    "itemcode\0itemtimeout(QString)\0"
    "onNewConnection()\0strIPandPort\0"
    "DeleteOneClient(QString)\0"
    "on_setButton_clicked()\0"
    "on_send_all_pushButton_clicked()\0"
};

const QMetaObject Server::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Server,
      qt_meta_data_Server, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Server::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Server::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Server::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Server))
        return static_cast<void*>(const_cast< Server*>(this));
    return QDialog::qt_metacast(_clname);
}

int Server::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_pushButton_clicked(); break;
        case 1: readMessage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: itemtimeout((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: onNewConnection(); break;
        case 4: DeleteOneClient((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: on_setButton_clicked(); break;
        case 6: on_send_all_pushButton_clicked(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
