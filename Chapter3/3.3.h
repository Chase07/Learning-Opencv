#ifndef _3_3_H
#define _3_3_H
#include<iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<math.h>
#include<string>
#include"3.2.h"

class ColorDetectController
{
public:
	//Remember: 在初始化列表中才是初始化操作（冒号和花括号中间），在函数体中属于赋值操作（花括号中间）
	ColorDetectController() :cdetect(new ColorDetector()) { /*cdetect = new ColorDetector();*/ }//new在这里是一个操作符（operator）
	
	void setColorDistanceThreshold(int distance) { cdetect->setColorDistanveThreshold(distance); }//调用对象的成员函数来的设置容忍度,以下同理
	int getColorDistanceThrehold() const { cdetect->getColorDistanceThreshold(); }
	void setTargetColor(unsigned char blue, unsigned char green, unsigned char red) { cdetect->setTargetColor(blue, green, red); }
	void getTargetColor(unsigned char& blue, unsigned char& green, unsigned char& red) const 
	{
		cv::Vec3b color = cdetect->getTargetColor();
		blue = color[0];
		green = color[1];
		red = color[2];
	}

	//设置输入的图像，以文件方式读取
	bool setInputImage(std::string filename)
	{
		image = cv::imread(filename);
		//检查是否读取成功
		if (!image.data)
			return false;
		else
			return true;
	}
	const cv::Mat getInputImage() const { return image;	}//获得当前读入的图像
	void process() { result = cdetect->process(image); }//处理图象 
	const cv::Mat getLastResult()const { return result; };//获得处理结果
	~ColorDetectController() { delete cdetect; };//析构函数
private:
	ColorDetector* cdetect;
	cv::Mat image;
	cv::Mat result;
};

#endif