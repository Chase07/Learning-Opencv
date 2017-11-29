/********************************************************************************
** Form generated from reading UI file 'mvc.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MVC_H
#define UI_MVC_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MVCClass
{
public:
    QWidget *centralWidget;
    QPushButton *openButton;
    QPushButton *selectButton;
    QPushButton *processButton;
    QLabel *labelOfOriginalImage;
    QLabel *labelOfColor;
    QLabel *labelOfThreshold;
    QSlider *sliderOfThreshold;
    QLabel *valueOfColor;
    QLabel *valueOfThreshold;
    QLabel *labelOfProcessImage;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MVCClass)
    {
        if (MVCClass->objectName().isEmpty())
            MVCClass->setObjectName(QStringLiteral("MVCClass"));
        MVCClass->resize(1213, 942);
        centralWidget = new QWidget(MVCClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        openButton = new QPushButton(centralWidget);
        openButton->setObjectName(QStringLiteral("openButton"));
        openButton->setGeometry(QRect(30, 30, 81, 31));
        selectButton = new QPushButton(centralWidget);
        selectButton->setObjectName(QStringLiteral("selectButton"));
        selectButton->setGeometry(QRect(30, 70, 81, 31));
        processButton = new QPushButton(centralWidget);
        processButton->setObjectName(QStringLiteral("processButton"));
        processButton->setGeometry(QRect(30, 510, 81, 31));
        labelOfOriginalImage = new QLabel(centralWidget);
        labelOfOriginalImage->setObjectName(QStringLiteral("labelOfOriginalImage"));
        labelOfOriginalImage->setGeometry(QRect(170, 30, 271, 271));
        labelOfColor = new QLabel(centralWidget);
        labelOfColor->setObjectName(QStringLiteral("labelOfColor"));
        labelOfColor->setGeometry(QRect(30, 440, 41, 21));
        QFont font;
        font.setPointSize(10);
        labelOfColor->setFont(font);
        labelOfThreshold = new QLabel(centralWidget);
        labelOfThreshold->setObjectName(QStringLiteral("labelOfThreshold"));
        labelOfThreshold->setGeometry(QRect(30, 470, 71, 21));
        labelOfThreshold->setFont(font);
        sliderOfThreshold = new QSlider(centralWidget);
        sliderOfThreshold->setObjectName(QStringLiteral("sliderOfThreshold"));
        sliderOfThreshold->setGeometry(QRect(60, 150, 22, 251));
        sliderOfThreshold->setOrientation(Qt::Vertical);
        valueOfColor = new QLabel(centralWidget);
        valueOfColor->setObjectName(QStringLiteral("valueOfColor"));
        valueOfColor->setGeometry(QRect(70, 440, 31, 20));
        QFont font1;
        font1.setPointSize(9);
        valueOfColor->setFont(font1);
        valueOfThreshold = new QLabel(centralWidget);
        valueOfThreshold->setObjectName(QStringLiteral("valueOfThreshold"));
        valueOfThreshold->setGeometry(QRect(100, 470, 31, 20));
        labelOfProcessImage = new QLabel(centralWidget);
        labelOfProcessImage->setObjectName(QStringLiteral("labelOfProcessImage"));
        labelOfProcessImage->setGeometry(QRect(230, 70, 271, 271));
        MVCClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MVCClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1213, 23));
        MVCClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MVCClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MVCClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MVCClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MVCClass->setStatusBar(statusBar);

        retranslateUi(MVCClass);
        QObject::connect(sliderOfThreshold, SIGNAL(valueChanged(int)), MVCClass, SLOT(on_sliderOfThreshold_valueChaned()));
        QObject::connect(sliderOfThreshold, SIGNAL(sliderMoved(int)), MVCClass, SLOT(on_sliderOfThreshold_sliderMoved()));

        QMetaObject::connectSlotsByName(MVCClass);
    } // setupUi

    void retranslateUi(QMainWindow *MVCClass)
    {
        MVCClass->setWindowTitle(QApplication::translate("MVCClass", "MVC", Q_NULLPTR));
        openButton->setText(QApplication::translate("MVCClass", "Open Image", Q_NULLPTR));
        selectButton->setText(QApplication::translate("MVCClass", "Select Color", Q_NULLPTR));
        processButton->setText(QApplication::translate("MVCClass", "Process", Q_NULLPTR));
        labelOfOriginalImage->setText(QString());
        labelOfColor->setText(QApplication::translate("MVCClass", "Color:", Q_NULLPTR));
        labelOfThreshold->setText(QApplication::translate("MVCClass", "Threshold:", Q_NULLPTR));
        valueOfColor->setText(QString());
        valueOfThreshold->setText(QString());
        labelOfProcessImage->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MVCClass: public Ui_MVCClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MVC_H
