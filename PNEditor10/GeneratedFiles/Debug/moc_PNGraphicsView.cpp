/****************************************************************************
** Meta object code from reading C++ file 'PNGraphicsView.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PNGraphicsView.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PNGraphicsView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PNGraphicsView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x08,
      25,   15,   15,   15, 0x08,
      34,   15,   15,   15, 0x08,
      51,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PNGraphicsView[] = {
    "PNGraphicsView\0\0remove()\0rename()\0"
    "increaseZValue()\0decreaseZValue()\0"
};

void PNGraphicsView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PNGraphicsView *_t = static_cast<PNGraphicsView *>(_o);
        switch (_id) {
        case 0: _t->remove(); break;
        case 1: _t->rename(); break;
        case 2: _t->increaseZValue(); break;
        case 3: _t->decreaseZValue(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData PNGraphicsView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PNGraphicsView::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_PNGraphicsView,
      qt_meta_data_PNGraphicsView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PNGraphicsView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PNGraphicsView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PNGraphicsView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PNGraphicsView))
        return static_cast<void*>(const_cast< PNGraphicsView*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int PNGraphicsView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
