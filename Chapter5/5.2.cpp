#include<iostream>
#include<opencv2/opencv.hpp> 

using namespace::std;
using namespace::cv;

int main()
{
	int i = 0;

	// Reading as a grayscale image
	Mat image = imread("../../images/group.jpg", IMREAD_GRAYSCALE);
	imshow("Original group", image);

	// That pixels' value from 0 to 60 will set to 0, and that pixels' value from 61 to 255 will set to 255. 
	threshold(image, image, 60, 255, THRESH_BINARY);// Binarization
	bitwise_not(image, image, Mat());// NOT
	imshow("Binary group", image);

	
	Mat dilated;
	dilate(image, dilated, Mat());
	imshow("Dilated group", dilated);

	Mat eroded;
	erode(image, eroded, cv::Mat(), Point(-1, -1), 3);
	
	/*Mat element(7, 7, CV_8U, cv::Scalar(1));
	erode(image, eroded, element);*/
	imshow("Eroded group", eroded);// Using own construct element
	waitKey(0);
	return 0;
}