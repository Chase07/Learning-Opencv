#include<iostream>
#include<opencv2/opencv.hpp>

using namespace::std;
using namespace::cv;

int main()
{
	// Reading as a grayscale image
	Mat image(imread("../../images/group.jpg", cv::IMREAD_GRAYSCALE));
	imshow("Original image", image);
	threshold(image, image, 60, 255, cv::THRESH_BINARY);// Binarization 
	bitwise_not(image, image, Mat());// NOT
	imshow("Binarization image", image);

	Mat element(5, 5, CV_8U, cv::Scalar(1));
	Mat eroded, dilated, closed, opened;
	erode(image, eroded, element);
	imshow("Eroded", eroded);

	dilate(image, dilated, element);
	imshow("Dilated", dilated);
	
	morphologyEx(image, closed, cv::MORPH_CLOSE, element);
	imshow("Closed", closed);
	morphologyEx(image, opened, cv::MORPH_OPEN, element);
	
	imshow("Opened", opened);
	waitKey(0);

	return 0;
}