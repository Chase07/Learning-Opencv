#ifndef _5_4_H
#define _5_4_H
#include<opencv2\opencv.hpp>

class MorphoFeatures
{
private:
	// It was used to produce binary image that threshold
	int threshold;

	// Strucuring elements used in corner detection
	cv::Mat cross;
	cv::Mat diamond;
	cv::Mat square;
	cv::Mat x;

	void applyThreshold(cv::Mat& result);
public:
	MorphoFeatures();//Constructor
	cv::Mat getEdges(const cv::Mat& image);
	cv::Mat getCorners(const cv::Mat& image);
	
	void drawOnImage(const cv::Mat& binary, cv::Mat& image);
	void setThreshold(const int threshold);
	
};

/**********Implement***********/
MorphoFeatures::MorphoFeatures() :threshold(-1), cross(5, 5, CV_8U, cv::Scalar(0)), diamond(5, 5, CV_8U, cv::Scalar(1)), square(5, 5, CV_8U, cv::Scalar(1)), x(5, 5, CV_8U, cv::Scalar(0)) 
{
	// Creating the cross-shaped structuring elemnt
	for (int i = 0; i != 5; ++i)
	{
		// Col: index 2   Row: index i   
		cross.at<uchar>(2, i) = 1;
		// Col: index i   Row: index 2
		cross.at<uchar>(i, 2) = 1;
	}

	// Creating the diamond-shaped structuring element
	diamond.at<uchar>(0, 0) = 0;
	diamond.at<uchar>(0, 1) = 0;
	diamond.at<uchar>(1, 0) = 0;

	diamond.at<uchar>(4, 4) = 0;
	diamond.at<uchar>(4, 3) = 0;
	diamond.at<uchar>(3, 4) = 0;

	diamond.at<uchar>(0, 4) = 0;
	diamond.at<uchar>(0, 3) = 0;
	diamond.at<uchar>(1, 4) = 0;
	
	diamond.at<uchar>(4, 0) = 0;
	diamond.at<uchar>(3, 0) = 0;
	diamond.at<uchar>(4, 1) = 0;

	// Creating the X-shaped structuring element
	for (int i = 0; i != 5; i++)
	{
		x.at<uchar>(i, i) = 1;
		x.at<uchar>(4 - i, i) = 1;
	}

}

cv::Mat MorphoFeatures::getEdges(const cv::Mat& image)
{
	// Get the gradient image
	cv::Mat result;
	cv::morphologyEx(image, result, cv::MORPH_GRADIENT, cv::Mat());

	// Obtaining a binary image
	applyThreshold(result);
	return result;

}
cv::Mat MorphoFeatures::getCorners(const cv::Mat& image)
{

	cv::Mat result1;
	// Dilate with Cross-shaped 
	cv::dilate(image, result1, cross);
	// Erode with Diamond-shaped
	cv::erode(result1, result1, diamond);

	cv::Mat result2;
	// Dilate with X-shaped
	cv::dilate(image, result2, x);
	// Erode with Square-shaped
	cv::erode(result2, result2, square);// Square-shaoed structure is a cv::Mat()
	
	cv::Mat result;
	// Differencing these two closed images
	cv::absdiff(result2, result1, result);
	// Obtaining a binary image
	this->applyThreshold(result);
	return result;
}

void MorphoFeatures::setThreshold(const int threshold)
{
	this->threshold = threshold;
}
void MorphoFeatures::drawOnImage(const cv::Mat& binaryImage, cv::Mat& image)
{
	cv::Mat_<uchar>::const_iterator curr = binaryImage.begin<uchar>();
	cv::Mat_<uchar>::const_iterator end = binaryImage.end<uchar>();
	// for each pixel
	for (int i = 0; curr != end; ++curr, ++i)
	{
		if (!*curr)// Whether the value of current pixel is 0
		{
			// Draw a circle
			cv::circle(image, cv::Point(i % image.step, i / image.step), 5, cv::Scalar(255, 0, 0));
		}

	}

}
void MorphoFeatures::applyThreshold(cv::Mat& result)
{
	// Applying threshold on result
	if (this->threshold > 0) { cv::threshold(result, result, threshold, 255, cv::THRESH_BINARY); }

}
#endif // _5_4_H