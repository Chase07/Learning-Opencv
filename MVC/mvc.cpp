#include "mvc.h"

using namespace::std;
using namespace::cv;
/*窗口类实现*/
//公有部分：
MVC::MVC(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.processButton->setEnabled(false);
	//设置滑动条范围
	ui.sliderOfThreshold->setMinimum(0);
	ui.sliderOfThreshold->setMaximum(255);
	/*设置并显示默认的selected color*/
	QPixmap  colorimg = QPixmap(ui.labelOfColor->size());
	colorimg.fill(Qt::black);//默认检测图像中的黑色
	ui.valueOfColor->setPixmap(colorimg);
	/*设置并显示默认threshold value*/
	ui.sliderOfThreshold->setValue(ColorDetectController::getInstance()->getColorDistanceThreshold());
	ui.valueOfThreshold->setText(QString::number(ColorDetectController::getInstance()->getColorDistanceThreshold()));
	
}

MVC::~MVC()
{

}
//私有部分：
void MVC::on_openButton_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.png *.jpg *.jpeg *.bmp)"));//用QString记录图像文件名

	if (ColorDetectController::getInstance()->setInputImage(fileName.toLatin1().data()))//创建控制器实例，并将文件名转为string，作为参数传入
	{
		/*传入图像成功*/
		//创建一个临时的Mat存放改变通道后的图像
		Mat tmp(ColorDetectController::getInstance()->getInputImage().rows, ColorDetectController::getInstance()->getInputImage().cols, CV_8UC3);
		cvtColor(ColorDetectController::getInstance()->getInputImage(), tmp, CV_BGR2RGB);//改变颜色通道顺序(测试得知,即便是const Mat，其通道顺序也能被改变)
		QImage img = QImage(static_cast<const unsigned char*>(tmp.data), tmp.cols, tmp.rows, QImage::Format_RGB888 );//将opencv中的图像格式转为qt的图像格式
		ui.labelOfOriginalImage->setPixmap(QPixmap::fromImage(img));//将窗口中labelOfImage部分的像素值改为图像的像素值
		ui.labelOfOriginalImage->resize(ui.labelOfOriginalImage->pixmap()->size());
		ui.processButton->setEnabled(true);
		/*namedWindow("Original Image");
		imshow("Original Image", ColorDetectController::getInstance()->getInputImage());*/
		
	}
}
void MVC::on_selectButton_clicked()
{
	QColor color = QColorDialog::getColor();//调出ColorDialog，获得用户选取的颜色
	if(color.isValid())
	{
		ColorDetectController::getInstance()->setTargetColor(color.blue(), color.green(), color.red());
		//创建一个QImage用于显示selected color
		QPixmap colorimg(ui.valueOfColor->size());
		colorimg.fill(color);
		ui.valueOfColor->setPixmap(colorimg);
	}
	
}
void MVC::on_processButton_clicked()
{
	//image的通道顺序已经在读入时被改变，可以直接处理
	ColorDetectController::getInstance()->process();//处理图像
	QImage img = QImage(static_cast<const unsigned char*>(ColorDetectController::getInstance()->getLastResult().data), ColorDetectController::getInstance()->getLastResult().cols, ColorDetectController::getInstance()->getLastResult().rows, QImage::Format_Indexed8);
	ui.labelOfOriginalImage->setPixmap(QPixmap::fromImage(img));//将窗口中相应部分的像素值改为图像的像素值
	ui.labelOfOriginalImage->resize(ui.labelOfOriginalImage->pixmap()->size());

}
void MVC::on_sliderOfThreshold_valueChaned()
{
	ColorDetectController::getInstance()->setColorDistanceThreshold(ui.sliderOfThreshold->value());
	ui.valueOfThreshold->setText(QString::number(ui.sliderOfThreshold->value()));
}
void MVC::on_sliderOfThreshold_sliderMoved()
{
	if (ColorDetectController::getInstance()->getInputImage().data)
	{
		/*图像已经被成功载入*/
		on_processButton_clicked();//调用处理函数
	}
}
/*算法类实现*/
//公有部分：
ColorDetector::ColorDetector():minDist(100) 
{
	target[0] = target[1] = target[2] = 0;//默认检测颜色为黑色
}
void ColorDetector::setColorDistanceThreshold(int distance)
{
	if (distance < 0) { distance = 0; }
	minDist = distance;
}
int ColorDetector::getColorDistanceThreshold() const
{
	return minDist;
}
void ColorDetector::setTargetColor(unsigned char blue, unsigned char green, unsigned char red)
{
	Mat tmp(1, 1, CV_8UC3);
	tmp.at<Vec3b>(0, 0)[0] = blue;
	tmp.at<Vec3b>(0, 0)[1] = green;
	tmp.at<Vec3b>(0, 0)[2] = red;
	cvtColor(tmp, tmp, CV_BGR2Lab);//转换颜色空间（BGR to Lab）
	target = tmp.at<Vec3b>(0, 0);//将转换后的颜色赋予待检测颜色
	/*target[0] = blue;
	target[1] = green;
	target[2] = red;*/
}
void ColorDetector::setTargetColor(Vec3b color)
{
	target = color;
}
Vec3b ColorDetector::getTargetColor() const
{
	return target;
}
int ColorDetector::getDistance(const Vec3b& color) const
{
	//return abs(color[0] - target[0]) + abs(color[1] - target[1]) + abs(color[2] - target[2]);
	return static_cast<int>(norm<int, 3>(Vec3i(color[0] - target[0], color[1] - target[1], color[2] - target[2])));
}
Mat ColorDetector::process(const Mat& image)
{
	result.create(image.size(), CV_8UC1);//给输出图像分配空间
	converted.create(image.size(), image.type());//给转换图像分配空间
	cvtColor(image, converted, CV_BGR2Lab);//将原图像转换到Lab空间
	Mat_<Vec3b>::const_iterator itbeg = converted.begin<Vec3b>();
	Mat_<Vec3b>::const_iterator itend = converted.end<Vec3b>();
	/*Mat_<Vec3b>::const_iterator itbeg = image.begin<Vec3b>();
	Mat_<Vec3b>::const_iterator itend = image.end<Vec3b>();*/
	Mat_<uchar>::iterator itout = result.begin<uchar>();
	//通过循环处理每一个像素
	for (; itbeg != itend; ++itbeg, ++itout)
	{
		if (getDistance(*itbeg) < minDist)
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
/*控件类实现*/
//公有部分：
void ColorDetectController::setColorDistanceThreshold(int distance)
{
	cdetect->setColorDistanceThreshold(distance);
}
int ColorDetectController::getColorDistanceThreshold() const
{
	return cdetect->getColorDistanceThreshold();
}
void ColorDetectController::setTargetColor(unsigned char blue, unsigned char green, unsigned char red)
{
	cdetect->setTargetColor(blue, green, red);
}
void ColorDetectController::setTargetColor(cv::Vec3b color)
{
	cdetect->setTargetColor(color);
}
void ColorDetectController::getTargetColor(unsigned char& blue, unsigned char& green, unsigned char& red) const
{
	red = cdetect->getTargetColor()[0];
	green = cdetect->getTargetColor()[1];
	blue = cdetect->getTargetColor()[2];
}
bool ColorDetectController::setInputImage(string fileName)
{
	image = imread(fileName);
	if (!image.data)
		return false;
	else
		return true;
}
const Mat ColorDetectController::getInputImage() const 
{
	return image;
}
void ColorDetectController::process()
{
	result = cdetect->process(image);
}
const Mat ColorDetectController::getLastResult() const
{
	return result;
}
ColorDetectController::~ColorDetectController()
{ 
	delete cdetect;
}
ColorDetectController* ColorDetectController::singleton;//定义静态成员变量
/*下面是定义静态成员函数*/
ColorDetectController* ColorDetectController::getInstance()
{
	if (singleton == nullptr)
	{
		singleton = new ColorDetectController;
	}
	return singleton;
}
void ColorDetectController::destroy()
{
	if (singleton != nullptr)
	{
		delete singleton;
	}
}
//私有部分
ColorDetectController::ColorDetectController() :cdetect(new ColorDetector()) {}