#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
//新添加的4个头文件
#include<QFileDialog>
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\opencv.hpp>

class mainwindow : public QMainWindow
{
	Q_OBJECT

public:
	mainwindow(QWidget *parent = 0);
	~mainwindow();

private:
	Ui::mainwindowClass ui;
	cv::Mat image;//新添加的1个图像变量
	cv::Mat result;

	private slots:
	void on_push_button_clicked();
	void on_pushButton_2_clicked();
};

#endif // MAINWINDOW_H
