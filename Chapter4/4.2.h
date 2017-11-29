#ifndef _4_2_H
#define _4_2_H
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

class Histogram1D 
{
private:
	int histSize[1];//项的数量
	float hranges[2];//像素的最大值和最小值
	const float* ranges[1];
	int channels[1];//仅使用一个通道

public:
	Histogram1D();
	cv::MatND getHistogram(const cv::Mat& image);//计算1D直方图
	cv::Mat getHistogramImage(const cv::Mat& image);//4.2
	cv::Mat applyLookUp(const cv::Mat& image, const cv::Mat& lookup);//4.3
	cv::Mat stretch(const cv::Mat& image, int minvalue = 0);//4.3
	cv::Mat equalize(const cv::Mat& image);
}; 

#endif // !_4_2_H
