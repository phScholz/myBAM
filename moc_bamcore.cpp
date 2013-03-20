/****************************************************************************
** Meta object code from reading C++ file 'bamcore.h'
**
** Created: Mon Mar 18 16:41:23 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "bamcore.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bamcore.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_bamCore[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,
      29,    8,    8,    8, 0x05,
      40,    8,    8,    8, 0x05,
      58,    8,    8,    8, 0x05,
      77,    8,    8,    8, 0x05,
      91,    8,    8,    8, 0x05,
     108,    8,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
     124,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_bamCore[] = {
    "bamCore\0\0setProgressBar(int)\0finished()\0"
    "CurrentFinished()\0N_TargetFinished()\0"
    "PhiFinished()\0N_ProdFinished()\0"
    "SigmaFinished()\0beginCal()\0"
};

const QMetaObject bamCore::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_bamCore,
      qt_meta_data_bamCore, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &bamCore::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *bamCore::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *bamCore::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_bamCore))
        return static_cast<void*>(const_cast< bamCore*>(this));
    return QObject::qt_metacast(_clname);
}

int bamCore::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setProgressBar((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: finished(); break;
        case 2: CurrentFinished(); break;
        case 3: N_TargetFinished(); break;
        case 4: PhiFinished(); break;
        case 5: N_ProdFinished(); break;
        case 6: SigmaFinished(); break;
        case 7: beginCal(); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void bamCore::setProgressBar(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void bamCore::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void bamCore::CurrentFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void bamCore::N_TargetFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void bamCore::PhiFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void bamCore::N_ProdFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void bamCore::SigmaFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}
QT_END_MOC_NAMESPACE
