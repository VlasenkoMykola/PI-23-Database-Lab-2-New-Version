/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionExit;
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tabTables;
    QComboBox *comboBoxTables;
    QLabel *labelSelectTable;
    QTableView *tableViewTables;
    QWidget *tabViews;
    QComboBox *comboBoxViews;
    QLabel *labelSelectView;
    QTableView *tableViewViews;
    QLabel *labelViewSQLText;
    QLabel *labelSQLTextViews;
    QWidget *tabParamViews;
    QComboBox *comboBoxParamViews;
    QLabel *labelSelectParamView;
    QLabel *labelParamViewSQLText;
    QLabel *labelSQLTextParamViews;
    QTableView *tableViewParamViews;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 771, 541));
        tabTables = new QWidget();
        tabTables->setObjectName(QString::fromUtf8("tabTables"));
        comboBoxTables = new QComboBox(tabTables);
        comboBoxTables->setObjectName(QString::fromUtf8("comboBoxTables"));
        comboBoxTables->setGeometry(QRect(210, 10, 311, 23));
        labelSelectTable = new QLabel(tabTables);
        labelSelectTable->setObjectName(QString::fromUtf8("labelSelectTable"));
        labelSelectTable->setGeometry(QRect(20, 10, 91, 21));
        tableViewTables = new QTableView(tabTables);
        tableViewTables->setObjectName(QString::fromUtf8("tableViewTables"));
        tableViewTables->setGeometry(QRect(20, 50, 720, 440));
        tabWidget->addTab(tabTables, QString());
        tabViews = new QWidget();
        tabViews->setObjectName(QString::fromUtf8("tabViews"));
        comboBoxViews = new QComboBox(tabViews);
        comboBoxViews->setObjectName(QString::fromUtf8("comboBoxViews"));
        comboBoxViews->setGeometry(QRect(210, 10, 531, 23));
        labelSelectView = new QLabel(tabViews);
        labelSelectView->setObjectName(QString::fromUtf8("labelSelectView"));
        labelSelectView->setGeometry(QRect(20, 10, 91, 21));
        tableViewViews = new QTableView(tabViews);
        tableViewViews->setObjectName(QString::fromUtf8("tableViewViews"));
        tableViewViews->setGeometry(QRect(20, 109, 720, 391));
        labelViewSQLText = new QLabel(tabViews);
        labelViewSQLText->setObjectName(QString::fromUtf8("labelViewSQLText"));
        labelViewSQLText->setGeometry(QRect(20, 40, 41, 21));
        labelSQLTextViews = new QLabel(tabViews);
        labelSQLTextViews->setObjectName(QString::fromUtf8("labelSQLTextViews"));
        labelSQLTextViews->setGeometry(QRect(60, 50, 681, 41));
        labelSQLTextViews->setWordWrap(true);
        tabWidget->addTab(tabViews, QString());
        tabParamViews = new QWidget();
        tabParamViews->setObjectName(QString::fromUtf8("tabParamViews"));
        comboBoxParamViews = new QComboBox(tabParamViews);
        comboBoxParamViews->setObjectName(QString::fromUtf8("comboBoxParamViews"));
        comboBoxParamViews->setGeometry(QRect(210, 10, 531, 23));
        labelSelectParamView = new QLabel(tabParamViews);
        labelSelectParamView->setObjectName(QString::fromUtf8("labelSelectParamView"));
        labelSelectParamView->setGeometry(QRect(20, 10, 181, 21));
        labelParamViewSQLText = new QLabel(tabParamViews);
        labelParamViewSQLText->setObjectName(QString::fromUtf8("labelParamViewSQLText"));
        labelParamViewSQLText->setGeometry(QRect(20, 40, 41, 21));
        labelSQLTextParamViews = new QLabel(tabParamViews);
        labelSQLTextParamViews->setObjectName(QString::fromUtf8("labelSQLTextParamViews"));
        labelSQLTextParamViews->setGeometry(QRect(60, 40, 681, 41));
        labelSQLTextParamViews->setWordWrap(true);
        tableViewParamViews = new QTableView(tabParamViews);
        tableViewParamViews->setObjectName(QString::fromUtf8("tableViewParamViews"));
        tableViewParamViews->setGeometry(QRect(20, 110, 720, 391));
        tabWidget->addTab(tabParamViews, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 20));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);

        retranslateUi(MainWindow);
        QObject::connect(actionExit, SIGNAL(triggered()), MainWindow, SLOT(close()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "DB Lab2 Vlasenko Mykola", nullptr));
        actionOpen->setText(QApplication::translate("MainWindow", "&Open DB...", nullptr));
        actionExit->setText(QApplication::translate("MainWindow", "E&xit", nullptr));
        labelSelectTable->setText(QApplication::translate("MainWindow", "Select Table:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabTables), QApplication::translate("MainWindow", "Tables", nullptr));
        labelSelectView->setText(QApplication::translate("MainWindow", "Select View:", nullptr));
        labelViewSQLText->setText(QApplication::translate("MainWindow", "SQL:", nullptr));
        labelSQLTextViews->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tabViews), QApplication::translate("MainWindow", "Views", nullptr));
        labelSelectParamView->setText(QApplication::translate("MainWindow", "Select Parametrized View:", nullptr));
        labelParamViewSQLText->setText(QApplication::translate("MainWindow", "SQL:", nullptr));
        labelSQLTextParamViews->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tabParamViews), QApplication::translate("MainWindow", "ParamViews", nullptr));
        menuFile->setTitle(QApplication::translate("MainWindow", "&File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
