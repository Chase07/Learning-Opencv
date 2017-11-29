#ifndef _4_2_H
#define _4_2_H
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

class Histogram1D 
{
private:
	int histSize[1];//�������
	float hranges[2];//���ص����ֵ����Сֵ
	const float* ranges[1];
	int channels[1];//��ʹ��һ��ͨ��

public:
	Histogram1D();
	cv::MatND getHistogram(const cv::Mat& image);//����1Dֱ��ͼ
	cv::Mat getHistogramImage(const cv::Mat& image);//4.2
	cv::Mat applyLookUp(const cv::Mat& image, const cv::Mat& lookup);//4.3
	cv::Mat stretch(const cv::Mat& image, int minvalue = 0);//4.3
	cv::Mat equalize(const cv::Mat& image);
}; 

#endif // !_4_2_H
