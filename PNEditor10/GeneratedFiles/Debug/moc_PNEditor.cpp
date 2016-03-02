/****************************************************************************
** Meta object code from reading C++ file 'PNEditor.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PNEditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PNEditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PNEditor[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x08,
      29,    9,    9,    9, 0x08,
      50,    9,    9,    9, 0x08,
      72,    9,    9,    9, 0x08,
      86,    9,    9,    9, 0x08,
     100,    9,    9,    9, 0x08,
     114,    9,    9,    9, 0x08,
     131,    9,    9,    9, 0x08,
     143,    9,    9,    9, 0x08,
     154,    9,    9,    9, 0x08,
     166,    9,    9,    9, 0x08,
     181,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PNEditor[] = {
    "PNEditor\0\0pushAddPosButton()\0"
    "pushAddTransButton()\0allowAddingEdges(int)\0"
    "setViewMode()\0setMoveMode()\0setEditMode()\0"
    "changeRenderer()\0importing()\0exportPn()\0"
    "exportPNL()\0tabClosed(int)\0tabChanged(int)\0"
};

void PNEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PNEditor *_t = static_cast<PNEditor *>(_o);
        switch (_id) {
        case 0: _t->pushAddPosButton(); break;
        case 1: _t->pushAddTransButton(); break;
        case 2: _t->allowAddingEdges((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->setViewMode(); break;
        case 4: _t->setMoveMode(); break;
        case 5: _t->setEditMode(); break;
        case 6: _t->changeRenderer(); break;
        case 7: _t->importing(); break;
        case 8: _t->exportPn(); break;
        case 9: _t->exportPNL(); break;
        case 10: _t->tabClosed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->tabChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PNEditor::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PNEditor::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PNEditor,
      qt_meta_data_PNEditor, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PNEditor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PNEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PNEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PNEditor))
        return static_cast<void*>(const_cast< PNEditor*>(this));
    return QObject::qt_metacast(_clname);
}

int PNEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
