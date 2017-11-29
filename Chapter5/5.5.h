#ifndef _5_5_H
#define _5_5_H
#include<opencv2\opencv.hpp>

class WatershedSegmenter
{
private:
	cv::Mat markers;
public:
	void setMarkers(const cv::Mat& markerImage);
	cv::Mat process(const cv::Mat& image);
	cv::Mat getSegmentation();
	cv::Mat getWatersheds();

};

/*******Implement********/
void WatershedSegmenter::setMarkers(const cv::Mat& markerImage)
{
	// Convert to image of ints
	markerImage.convertTo(markers, CV_32SC1);
	imshow("In setMarkers1", markerImage);
}
cv::Mat WatershedSegmenter::process(const cv::Mat& image)
{
	// Apply watershed
	cv::watershed(image, markers);
	return markers;

}
cv::Mat WatershedSegmenter::getSegmentation()
{
	cv::Mat temp;
	this->markers.convertTo(temp, CV_8U);
	return temp;
}

cv::Mat WatershedSegmenter::getWatersheds() 
{
	cv::Mat temp;
	this->markers.convertTo(temp, CV_8U, 255, 255);
	return temp;
}
#endif // _5_5_H
