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
	//Remember: �ڳ�ʼ���б��в��ǳ�ʼ��������ð�źͻ������м䣩���ں����������ڸ�ֵ�������������м䣩
	ColorDetectController() :cdetect(new ColorDetector()) { /*cdetect = new ColorDetector();*/ }//new��������һ����������operator��
	
	void setColorDistanceThreshold(int distance) { cdetect->setColorDistanveThreshold(distance); }//���ö���ĳ�Ա���������������̶�,����ͬ��
	int getColorDistanceThrehold() const { cdetect->getColorDistanceThreshold(); }
	void setTargetColor(unsigned char blue, unsigned char green, unsigned char red) { cdetect->setTargetColor(blue, green, red); }
	void getTargetColor(unsigned char& blue, unsigned char& green, unsigned char& red) const 
	{
		cv::Vec3b color = cdetect->getTargetColor();
		blue = color[0];
		green = color[1];
		red = color[2];
	}

	//���������ͼ�����ļ���ʽ��ȡ
	bool setInputImage(std::string filename)
	{
		image = cv::imread(filename);
		//����Ƿ��ȡ�ɹ�
		if (!image.data)
			return false;
		else
			return true;
	}
	const cv::Mat getInputImage() const { return image;	}//��õ�ǰ�����ͼ��
	void process() { result = cdetect->process(image); }//����ͼ�� 
	const cv::Mat getLastResult()const { return result; };//��ô�����
	~ColorDetectController() { delete cdetect; };//��������
private:
	ColorDetector* cdetect;
	cv::Mat image;
	cv::Mat result;
};

#endif