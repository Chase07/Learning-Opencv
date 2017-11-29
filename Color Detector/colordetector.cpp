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
	result.create(image.rows, image.cols, CV_8U);//���ͼ���ڴ˱�ָ���µĴ�С
												 //����ͼ�����β������
	cv::Mat_<cv::Vec3b>::const_iterator it = image.begin<cv::Vec3b>();
	cv::Mat_<cv::Vec3b>::const_iterator itend = image.end<cv::Vec3b>();
	//���ͼ��ĵ�����
	cv::Mat_<uchar>::iterator itout = result.begin<uchar>();
	//���棺Vec3b��3��uchar���ɵ�vector����
	//���棺����ÿ�����أ��ԱȽ�����������̶Ȳ�����Ӧ����
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
	//return abs(color[0] - target[0]) + abs(color[1] - target[1]) + abs(color[2] - target[2]);//�����������
	return static_cast<int>(cv::norm<int, 3>(cv::Vec3i(color[0] - target[0], color[1] - target[1], color[2] - target[2])));//����ŷ������
}
void ColorDetector::on_openImage_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.png *.jpg *.jpeg *.bmp)"));
	/*�˴�©��δѡ��ͼ������*/
	image = cv::imread(fileName.toLatin1().data());
	cv::cvtColor(image, image, CV_BGR2RGB);
	QImage img1 = QImage(static_cast<const unsigned char*>(image.data), image.cols, image.rows, QImage::Format_RGB888);
	//��ʾ
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
	//res�ǵ�ͨ����CV_8UC1������ӦQt�е�QImage::Format_Indexed8
	QImage result = QImage(static_cast<const unsigned char*>(res.data), res.cols, res.rows, QImage::Format_Indexed8);
	ui.label->setPixmap(QPixmap::fromImage(result));
	ui.label->resize(ui.label->pixmap()->size());

}
void ColorDetector::on_ok_clicked() {}
void ColorDetector::on_cancel_clicked(){}
