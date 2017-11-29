#include"4.2.h"
#include <opencv2/imgproc/imgproc.hpp>

using namespace::std;
using namespace::cv; 
/*******Class Histogram1D*******/
/*Public part:*/
Histogram1D::Histogram1D()
{
	histSize[0] = 256;
	hranges[0] = 0.0; 
	hranges[1] = 255.0;
	ranges[0] = hranges;
	channels[0] = 0;

}
MatND Histogram1D::getHistogram(const Mat& image) 
{
	MatND hist;

	calcHist(&image, 1, channels, Mat(), hist, 1, histSize, ranges);
	return hist;
}
Mat Histogram1D::getHistogramImage(const Mat& image)
{
	MatND hist = getHistogram(image);
	double maxVal = 0;
	double minVal = 0;
	minMaxLoc(hist.reshape(1,1), &minVal, &maxVal, 0, 0);//Get the minimum and maximum

	Mat histImg(histSize[0], histSize[0], CV_8U, Scalar(255));//Creat a histogram image with whole white color
	int hpt = static_cast<int>(0.9 * histSize[0]);
	//Draw a perpendicular for each item
	for (int h = 0; h != histSize[0] ; ++h)
	{
		float binVal = hist.at<float>(h);
		int intensity = static_cast<int>(binVal* hpt / maxVal);
		//Draw a line between two points
		line(histImg, Point(h, histSize[0]), Point(h, histSize[0] - intensity), Scalar::all(0));
	}
	return histImg;

}
Mat Histogram1D::applyLookUp(const cv::Mat& image, const cv::Mat& lookup)
{
	Mat result;
	//Apply the histogram
	LUT(image, lookup, result);
	return result;
}
Mat Histogram1D::stretch(const cv::Mat& image, int minValue)
{
	MatND hist = getHistogram(image);//calculate the histogram
	//Seek the most left size in histogram
	int imin = 0;
	for (; imin != histSize[0]; ++imin)
	{
		cout << hist.at<float>(imin) << endl;
		if (hist.at<float>(imin) > minValue) break;
	}
	//Seek the most right size in histogram
	int imax = histSize[0] - 1;
	for (; imax != 0; --imax)
	{
		if (hist.at<float>(imax) > minValue) break;
	}
	//Creat a look-up table 
	int dim(256);
	Mat lookup(1, &dim, CV_8U);
	//Fill up the look-up table
	for (int i = 0; i != 256; ++i)
	{
		//Make sure the value is between imin and imax
		if (i < imin) lookup.at<uchar>(i) = 0;
		else if (i > imax) lookup.at<uchar>(i) = 255;
		//Linear map
		else lookup.at<uchar>(i) = static_cast<uchar>(255.0 * (i - imin) / (imax - imin) + 0.5);

	}
	Mat result;
	result = applyLookUp(image, lookup);
	return result;
}
Mat Histogram1D::equalize(const cv::Mat& image)
{
	Mat result;
	equalizeHist(image, result);
	return result;
}
