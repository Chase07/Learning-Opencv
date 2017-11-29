#include "colordetector.h"

using namespace::cv;
using namespace::std;

ColorDetector::ColorDetector(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.process->setEnabled(false);
}

ColorDetector::~ColorDetector()
{

}
cv::Mat ColorDetect_algorithm::process(const cv::Mat& image)
{
	result.create(image.rows, image.cols, CV_8U);//结果图像在此被指定新的大小
												 //输入图像的首尾迭代器
	cv::Mat_<cv::Vec3b>::const_iterator it = image.begin<cv::Vec3b>();
	cv::Mat_<cv::Vec3b>::const_iterator itend = image.end<cv::Vec3b>();
	//输出图像的迭代器
	cv::Mat_<uchar>::iterator itout = result.begin<uchar>();
	//上面：Vec3b是3个uchar构成的vector类型
	//下面：遍历每个像素，对比街区距离和容忍度并做相应处理
	for (; it != itend; ++it, ++itout)
	{
		if (getDistance(*it) < minDist)
		{
			*itout = 255;
		}
		else
		{
			*itout = 0;
		}
	}

	return result;
}
int ColorDetect_algorithm::getDistance(const cv::Vec3b& color) const
{
	//return abs(color[0] - target[0]) + abs(color[1] - target[1]) + abs(color[2] - target[2]);//计算街区距离
	return static_cast<int>(cv::norm<int, 3>(cv::Vec3i(color[0] - target[0], color[1] - target[1], color[2] - target[2])));//计算欧拉长度
}
void ColorDetector::on_openImage_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.png *.jpg *.jpeg *.bmp)"));
	/*此处漏检未选择图像的情况*/
	image = cv::imread(fileName.toLatin1().data());
	cv::cvtColor(image, image, CV_BGR2RGB);
	QImage img1 = QImage(static_cast<const unsigned char*>(image.data), image.cols, image.rows, QImage::Format_RGB888);
	//显示
	ui.label->setPixmap(QPixmap::fromImage(img1));
	ui.label->resize(ui.label->pixmap()->size());
	ui.process->setEnabled(true);
	

}
void ColorDetector::on_process_clicked()
{
	ColorDetect_algorithm cdetect;
	cv::Mat res;
	cdetect.setTargetColor(130, 190, 230);//color of sky
	res = cdetect.process(image);
	//res是单通道（CV_8UC1），对应Qt中的QImage::Format_Indexed8
	QImage result = QImage(static_cast<const unsigned char*>(res.data), res.cols, res.rows, QImage::Format_Indexed8);
	ui.label->setPixmap(QPixmap::fromImage(result));
	ui.label->resize(ui.label->pixmap()->size());

}
void ColorDetector::on_ok_clicked() {}
void ColorDetector::on_cancel_clicked(){}
