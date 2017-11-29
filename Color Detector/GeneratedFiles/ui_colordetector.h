/********************************************************************************
** Form generated from reading UI file 'colordetector.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COLORDETECTOR_H
#define UI_COLORDETECTOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ColorDetectorClass
{
public:
    QWidget *centralWidget;
    QPushButton *openImage;
    QLabel *label;
    QPushButton *process;
    QPushButton *ok;
    QPushButton *cancel;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ColorDetectorClass)
    {
        if (ColorDetectorClass->objectName().isEmpty())
            ColorDetectorClass->setObjectName(QStringLiteral("ColorDetectorClass"));
        ColorDetectorClass->resize(1191, 752);
        centralWidget = new QWidget(ColorDetectorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        openImage = new QPushButton(centralWidget);
        openImage->setObjectName(QStringLiteral("openImage"));
        openImage->setGeometry(QRect(20, 10, 111, 51));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(190, 20, 611, 401));
        process = new QPushButton(centralWidget);
        process->setObjectName(QStringLiteral("process"));
        process->setGeometry(QRect(20, 90, 111, 51));
        ok = new QPushButton(centralWidget);
        ok->setObjectName(QStringLiteral("ok"));
        ok->setGeometry(QRect(40, 340, 61, 21));
        cancel = new QPushButton(centralWidget);
        cancel->setObjectName(QStringLiteral("cancel"));
        cancel->setGeometry(QRect(40, 380, 61, 21));
        ColorDetectorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ColorDetectorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1191, 23));
        ColorDetectorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ColorDetectorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ColorDetectorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ColorDetectorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ColorDetectorClass->setStatusBar(statusBar);

        retranslateUi(ColorDetectorClass);

        QMetaObject::connectSlotsByName(ColorDetectorClass);
    } // setupUi

    void retranslateUi(QMainWindow *ColorDetectorClass)
    {
        ColorDetectorClass->setWindowTitle(QApplication::translate("ColorDetectorClass", "ColorDetector", Q_NULLPTR));
        openImage->setText(QApplication::translate("ColorDetectorClass", "Open Image", Q_NULLPTR));
        label->setText(QString());
        process->setText(QApplication::translate("ColorDetectorClass", "Process", Q_NULLPTR));
        ok->setText(QApplication::translate("ColorDetectorClass", "OK", Q_NULLPTR));
        cancel->setText(QApplication::translate("ColorDetectorClass", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ColorDetectorClass: public Ui_ColorDetectorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLORDETECTOR_H
