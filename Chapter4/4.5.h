#ifndef _4_5_H
#define _4_5_H
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

class ContentFinder
{
private:
	float hranges[2];//Range of BGR
	const float* ranges[3];
	int channels[3];
	float threshold;
	cv::MatND histogram;
public:
	ContentFinder();
	void setThreshold(float t);
	float getThreshold();//Get value of threshold
	void setHistogram(const cv::MatND& h);//Set the reference histogram
	cv::Mat find(const cv::Mat& image, int dim);
};
class ColorHistogram
{
public:
	ColorHistogram();
	cv::Mat colorReduce(cv::Mat& image, int div);
	cv::MatND getHistogram(cv::Mat& image);
	//void showHistogram(cv::MatND& hist);
private:
	int bins = 256;//The number of bins
	int histSize[3];
	float hranges[2];
	const float* ranges[3];
	int channels[3];

};
#endif //_4_5_H