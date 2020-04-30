/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *mainLayout;
    QPushButton *pushButton;
    QLabel *img;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *writeD;
    QLabel *setF;
    QLabel *setD;
    QLineEdit *writeF;
    QPushButton *parameters;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(587, 480);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(120, 50, 321, 121));
        mainLayout = new QVBoxLayout(verticalLayoutWidget);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(verticalLayoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        mainLayout->addWidget(pushButton);

        img = new QLabel(verticalLayoutWidget);
        img->setObjectName(QString::fromUtf8("img"));

        mainLayout->addWidget(img, 0, Qt::AlignHCenter);

        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(120, 190, 321, 148));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        writeD = new QLineEdit(gridLayoutWidget);
        writeD->setObjectName(QString::fromUtf8("writeD"));

        gridLayout->addWidget(writeD, 2, 1, 1, 1);

        setF = new QLabel(gridLayoutWidget);
        setF->setObjectName(QString::fromUtf8("setF"));

        gridLayout->addWidget(setF, 0, 0, 1, 1);

        setD = new QLabel(gridLayoutWidget);
        setD->setObjectName(QString::fromUtf8("setD"));

        gridLayout->addWidget(setD, 2, 0, 1, 1);

        writeF = new QLineEdit(gridLayoutWidget);
        writeF->setObjectName(QString::fromUtf8("writeF"));

        gridLayout->addWidget(writeF, 0, 1, 1, 1);

        parameters = new QPushButton(gridLayoutWidget);
        parameters->setObjectName(QString::fromUtf8("parameters"));

        gridLayout->addWidget(parameters, 3, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 587, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Upload image", nullptr));
        img->setText(QCoreApplication::translate("MainWindow", "ipreview", nullptr));
        setF->setText(QCoreApplication::translate("MainWindow", "set F", nullptr));
        setD->setText(QCoreApplication::translate("MainWindow", "set d", nullptr));
        parameters->setText(QCoreApplication::translate("MainWindow", "Send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
