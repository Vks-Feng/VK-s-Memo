/****************************************************************************
** Meta object code from reading C++ file 'fixre.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../VKmemoFINAL - 1024/fixre.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fixre.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSFixREENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSFixREENDCLASS = QtMocHelpers::stringData(
    "FixRE",
    "on_btn_ac_change_clicked",
    "",
    "on_btn_ac_delete_clicked",
    "on_cancel_ac_clicked",
    "on_confirm_ac_clicked",
    "ChangeRemind",
    "n"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSFixREENDCLASS_t {
    uint offsetsAndSizes[16];
    char stringdata0[6];
    char stringdata1[25];
    char stringdata2[1];
    char stringdata3[25];
    char stringdata4[21];
    char stringdata5[22];
    char stringdata6[13];
    char stringdata7[2];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSFixREENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSFixREENDCLASS_t qt_meta_stringdata_CLASSFixREENDCLASS = {
    {
        QT_MOC_LITERAL(0, 5),  // "FixRE"
        QT_MOC_LITERAL(6, 24),  // "on_btn_ac_change_clicked"
        QT_MOC_LITERAL(31, 0),  // ""
        QT_MOC_LITERAL(32, 24),  // "on_btn_ac_delete_clicked"
        QT_MOC_LITERAL(57, 20),  // "on_cancel_ac_clicked"
        QT_MOC_LITERAL(78, 21),  // "on_confirm_ac_clicked"
        QT_MOC_LITERAL(100, 12),  // "ChangeRemind"
        QT_MOC_LITERAL(113, 1)   // "n"
    },
    "FixRE",
    "on_btn_ac_change_clicked",
    "",
    "on_btn_ac_delete_clicked",
    "on_cancel_ac_clicked",
    "on_confirm_ac_clicked",
    "ChangeRemind",
    "n"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSFixREENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   44,    2, 0x08,    1 /* Private */,
       3,    0,   45,    2, 0x08,    2 /* Private */,
       4,    0,   46,    2, 0x08,    3 /* Private */,
       5,    0,   47,    2, 0x08,    4 /* Private */,
       6,    1,   48,    2, 0x08,    5 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,

       0        // eod
};

Q_CONSTINIT const QMetaObject FixRE::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSFixREENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSFixREENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSFixREENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<FixRE, std::true_type>,
        // method 'on_btn_ac_change_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btn_ac_delete_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_cancel_ac_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_confirm_ac_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'ChangeRemind'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void FixRE::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FixRE *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_btn_ac_change_clicked(); break;
        case 1: _t->on_btn_ac_delete_clicked(); break;
        case 2: _t->on_cancel_ac_clicked(); break;
        case 3: _t->on_confirm_ac_clicked(); break;
        case 4: _t->ChangeRemind((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *FixRE::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FixRE::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSFixREENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int FixRE::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
