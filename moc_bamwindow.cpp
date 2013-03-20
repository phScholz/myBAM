/****************************************************************************
** Meta object code from reading C++ file 'bamwindow.h'
**
** Created: Mon Mar 18 16:41:22 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "bamwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bamwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_bamWindow[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,
      31,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      42,   10,   10,   10, 0x0a,
      62,   10,   10,   10, 0x0a,
      82,   76,   10,   10, 0x0a,
      92,   10,   10,   10, 0x08,
     115,   10,   10,   10, 0x08,
     141,   10,   10,   10, 0x08,
     154,   10,   10,   10, 0x08,
     165,   10,   10,   10, 0x08,
     185,   10,   10,   10, 0x08,
     202,   10,   10,   10, 0x08,
     216,   10,   10,   10, 0x08,
     228,   10,   10,   10, 0x08,
     240,   10,   10,   10, 0x08,
     251,   10,   10,   10, 0x08,
     262,   10,   10,   10, 0x08,
     287,   10,   10,   10, 0x08,
     314,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_bamWindow[] = {
    "bamWindow\0\0pushButtonPressed()\0"
    "beginCal()\0setProgressBar(int)\0"
    "calFinished()\0index\0plot(int)\0"
    "on_calButton_clicked()\0on_browseButton_clicked()\0"
    "resetInput()\0getInput()\0readCountingInput()\0"
    "displayResults()\0plotCurrent()\0"
    "plotNprod()\0plotDiffN()\0loadFile()\0"
    "saveFile()\0on_closeButton_clicked()\0"
    "on_currentButton_clicked()\0"
    "on_nprodButton_clicked()\0"
};

const QMetaObject bamWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_bamWindow,
      qt_meta_data_bamWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &bamWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *bamWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *bamWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_bamWindow))
        return static_cast<void*>(const_cast< bamWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int bamWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: pushButtonPressed(); break;
        case 1: beginCal(); break;
        case 2: setProgressBar((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: calFinished(); break;
        case 4: plot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: on_calButton_clicked(); break;
        case 6: on_browseButton_clicked(); break;
        case 7: resetInput(); break;
        case 8: getInput(); break;
        case 9: readCountingInput(); break;
        case 10: displayResults(); break;
        case 11: plotCurrent(); break;
        case 12: plotNprod(); break;
        case 13: plotDiffN(); break;
        case 14: loadFile(); break;
        case 15: saveFile(); break;
        case 16: on_closeButton_clicked(); break;
        case 17: on_currentButton_clicked(); break;
        case 18: on_nprodButton_clicked(); break;
        default: ;
        }
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void bamWindow::pushButtonPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void bamWindow::beginCal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
