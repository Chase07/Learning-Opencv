#ifndef MVC_H
#define MVC_H

#include<QtWidgets/QMainWindow>
#include"ui_mvc.h"
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/opencv.hpp>
#include<memory>
#include<string>
#include<QFileDialog>
#include<QString>
#include<QColorDialog>


class MVC : public QMainWindow//窗口类
{
	Q_OBJECT

public:
	MVC(QWidget *parent = 0);
	~MVC();
private:
	Ui::MVCClass ui;
	private slots:
	void on_openButton_clicked();
	void on_selectButton_clicked();
	void on_processButton_clicked();
	void on_sliderOfThreshold_valueChaned();
	void on_sliderOfThreshold_sliderMoved();
	
};
class ColorDetector//算法处理类
{
public:
	ColorDetector();
	void setColorDistanceThreshold(int distance);
	int getColorDistanceThreshold() const;
	void setTargetColor(unsigned char blue, unsigned char green, unsigned char red);
	void setTargetColor(cv::Vec3b color);
	cv::Vec3b getTargetColor() const;
	int getDistance(const cv::Vec3b& color) const;//处理函数中使用的计算距离函数
	cv::Mat process(const cv::Mat& image);
	

private:
	int minDist;//容忍度
	cv::Vec3b target;//检测颜色
	cv::Mat result;//处理后图像
	cv::Mat converted;//转换后图像

};
class ColorDetectController//控件类
{
public:
	//用户(控件)使用的函数
	void setColorDistanceThreshold(int distance);
	int getColorDistanceThreshold() const;
	void setTargetColor(unsigned char blue, unsigned char green, unsigned char red);
	void setTargetColor(cv::Vec3b color);
	void getTargetColor(unsigned char& blue, unsigned char& green, unsigned char& red) const;//通过引用，记录下内部图像的通道值
	bool setInputImage(std::string fileName);
	const cv::Mat getInputImage() const;
	void process();
	const cv::Mat getLastResult() const;
	
	
	~ColorDetectController();//仅有cdetect指向创建的对象，因此释放内存	
	static ColorDetectController* getInstance();
	static void destroy();//销毁控件对象
private:
	ColorDetector *cdetect;
	ColorDetectController();//私有的构造函数
	static ColorDetectController* singleton;
	cv::Mat image;//待处理图像
	cv::Mat result;//处理后图像

};
#endif// MVC_H
