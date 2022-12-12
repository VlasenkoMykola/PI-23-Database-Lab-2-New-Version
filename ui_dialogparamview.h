/********************************************************************************
** Form generated from reading UI file 'dialogparamview.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGPARAMVIEW_H
#define UI_DIALOGPARAMVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogParamView
{
public:
    QDialogButtonBox *buttonBox;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QPlainTextEdit *plainTextEditParam1;
    QPlainTextEdit *plainTextEditParam0;
    QLabel *labelHeader;
    QLabel *labelParam0;
    QLabel *labelParam1;
    QLabel *labelParam2;
    QPlainTextEdit *plainTextEditParam2;
    QLabel *labelParam3;
    QPlainTextEdit *plainTextEditParam3;
    QLabel *labelParam4;
    QPlainTextEdit *plainTextEditParam4;

    void setupUi(QDialog *DialogParamView)
    {
        if (DialogParamView->objectName().isEmpty())
            DialogParamView->setObjectName(QString::fromUtf8("DialogParamView"));
        DialogParamView->resize(400, 300);
        buttonBox = new QDialogButtonBox(DialogParamView);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);
        scrollArea = new QScrollArea(DialogParamView);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(10, 10, 381, 221));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 379, 219));
        plainTextEditParam1 = new QPlainTextEdit(scrollAreaWidgetContents);
        plainTextEditParam1->setObjectName(QString::fromUtf8("plainTextEditParam1"));
        plainTextEditParam1->setGeometry(QRect(130, 70, 231, 31));
        plainTextEditParam0 = new QPlainTextEdit(scrollAreaWidgetContents);
        plainTextEditParam0->setObjectName(QString::fromUtf8("plainTextEditParam0"));
        plainTextEditParam0->setGeometry(QRect(130, 30, 231, 31));
        labelHeader = new QLabel(scrollAreaWidgetContents);
        labelHeader->setObjectName(QString::fromUtf8("labelHeader"));
        labelHeader->setGeometry(QRect(120, 10, 121, 16));
        labelParam0 = new QLabel(scrollAreaWidgetContents);
        labelParam0->setObjectName(QString::fromUtf8("labelParam0"));
        labelParam0->setGeometry(QRect(20, 30, 101, 16));
        labelParam1 = new QLabel(scrollAreaWidgetContents);
        labelParam1->setObjectName(QString::fromUtf8("labelParam1"));
        labelParam1->setGeometry(QRect(20, 70, 101, 20));
        labelParam2 = new QLabel(scrollAreaWidgetContents);
        labelParam2->setObjectName(QString::fromUtf8("labelParam2"));
        labelParam2->setGeometry(QRect(20, 110, 101, 20));
        plainTextEditParam2 = new QPlainTextEdit(scrollAreaWidgetContents);
        plainTextEditParam2->setObjectName(QString::fromUtf8("plainTextEditParam2"));
        plainTextEditParam2->setGeometry(QRect(130, 110, 231, 31));
        labelParam3 = new QLabel(scrollAreaWidgetContents);
        labelParam3->setObjectName(QString::fromUtf8("labelParam3"));
        labelParam3->setGeometry(QRect(20, 150, 101, 20));
        plainTextEditParam3 = new QPlainTextEdit(scrollAreaWidgetContents);
        plainTextEditParam3->setObjectName(QString::fromUtf8("plainTextEditParam3"));
        plainTextEditParam3->setGeometry(QRect(130, 150, 231, 31));
        labelParam4 = new QLabel(scrollAreaWidgetContents);
        labelParam4->setObjectName(QString::fromUtf8("labelParam4"));
        labelParam4->setGeometry(QRect(20, 190, 101, 20));
        plainTextEditParam4 = new QPlainTextEdit(scrollAreaWidgetContents);
        plainTextEditParam4->setObjectName(QString::fromUtf8("plainTextEditParam4"));
        plainTextEditParam4->setGeometry(QRect(130, 190, 231, 31));
        scrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(DialogParamView);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogParamView, SLOT(accept()));

        QMetaObject::connectSlotsByName(DialogParamView);
    } // setupUi

    void retranslateUi(QDialog *DialogParamView)
    {
        DialogParamView->setWindowTitle(QApplication::translate("DialogParamView", "Dialog", nullptr));
        labelHeader->setText(QApplication::translate("DialogParamView", "Enter parameters:", nullptr));
        labelParam0->setText(QApplication::translate("DialogParamView", "@INTEGER0@", nullptr));
        labelParam1->setText(QApplication::translate("DialogParamView", "@TEXT0@", nullptr));
        labelParam2->setText(QApplication::translate("DialogParamView", "@TEXT2@", nullptr));
        labelParam3->setText(QApplication::translate("DialogParamView", "@TEXT3@", nullptr));
        labelParam4->setText(QApplication::translate("DialogParamView", "@TEXT4@", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogParamView: public Ui_DialogParamView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGPARAMVIEW_H
