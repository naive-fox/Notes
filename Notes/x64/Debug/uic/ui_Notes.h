/********************************************************************************
** Form generated from reading UI file 'Notes.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOTES_H
#define UI_NOTES_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NotesClass
{
public:

    void setupUi(QWidget *NotesClass)
    {
        if (NotesClass->objectName().isEmpty())
            NotesClass->setObjectName(QString::fromUtf8("NotesClass"));
        NotesClass->resize(642, 480);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Notes.ico"), QSize(), QIcon::Normal, QIcon::Off);
        NotesClass->setWindowIcon(icon);

        retranslateUi(NotesClass);

        QMetaObject::connectSlotsByName(NotesClass);
    } // setupUi

    void retranslateUi(QWidget *NotesClass)
    {
        NotesClass->setWindowTitle(QApplication::translate("NotesClass", "Notes", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NotesClass: public Ui_NotesClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOTES_H
