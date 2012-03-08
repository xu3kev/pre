/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Fri Mar 9 02:32:59 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      22,   11,   11,   11, 0x08,
      29,   11,   11,   11, 0x08,
      36,   11,   11,   11, 0x08,
      43,   11,   11,   11, 0x08,
      51,   11,   11,   11, 0x08,
      57,   11,   11,   11, 0x08,
      64,   11,   11,   11, 0x08,
      71,   11,   11,   11, 0x08,
      79,   11,   11,   11, 0x08,
      85,   11,   11,   11, 0x08,
      91,   11,   11,   11, 0x08,
      99,   11,   11,   11, 0x08,
     105,   11,   11,   11, 0x08,
     114,   11,   11,   11, 0x08,
     121,   11,   11,   11, 0x08,
     134,  132,   11,   11, 0x08,
     146,   11,   11,   11, 0x08,
     160,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0newFile()\0open()\0save()\0"
    "copy()\0paste()\0cut()\0undo()\0redo()\0"
    "about()\0pen()\0rec()\0paint()\0ecl()\0"
    "choose()\0line()\0getColor()\0g\0check(bool)\0"
    "resizeImage()\0pen(int)\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: newFile(); break;
        case 1: open(); break;
        case 2: save(); break;
        case 3: copy(); break;
        case 4: paste(); break;
        case 5: cut(); break;
        case 6: undo(); break;
        case 7: redo(); break;
        case 8: about(); break;
        case 9: pen(); break;
        case 10: rec(); break;
        case 11: paint(); break;
        case 12: ecl(); break;
        case 13: choose(); break;
        case 14: line(); break;
        case 15: getColor(); break;
        case 16: check((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 17: resizeImage(); break;
        case 18: pen((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 19;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
