#include "mainwindow.h"

mainwindow::mainwindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.pushButton_2->setEnabled(false);
}

mainwindow::~mainwindow()
{

}
void mainwindow::on_push_button_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.png *.jpg *.jpeg *.bmp)"));
	
	//将Qstring类型转换成imread()能识别的类型
	image = cv::imread(fileName.toLatin1().data());//在Qt5中toAscii()改为toLatin1()
	cv::cvtColor(image, image, CV_BGR2RGB);//改变彩色通道的顺序
	QImage img1 = QImage(static_cast<const unsigned char*>(image.data), image.cols, image.rows, QImage::Format_RGB888);
	//直接显示在label中
	ui.label->setPixmap(QPixmap::fromImage(img1));
	ui.label->resize(ui.label->pixmap()->size());

	/*cv::namedWindow("Orginnal Image");
	cv::imshow("Orginnal Image", image);*/
	ui.pushButton_2->setEnabled(true);

}
void mainwindow::on_pushButton_2_clicked()
{
	result.create(image.size(), image.type());
	cv::flip(image, result, 1);
	//改变彩色通道的顺序
	//cv::cvtColor(result, result, CV_BGR2RGB);
	QImage img = QImage(static_cast<const unsigned char*>(result.data), result.cols, result.rows, QImage::Format_RGB888);
	//显示在label中
	ui.label->setPixmap(QPixmap::fromImage(img));
	ui.label->resize(ui.label->pixmap()->size());
	/*cv::namedWindow("Output Image");
	cv::imshow("Output Image", result);*/
}