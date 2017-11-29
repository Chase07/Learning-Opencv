#include<iostream>
#include<opencv2\opencv.hpp>

using namespace::std;
using namespace::cv;
int main()
{
	Mat GrayscaleImage(cv::imread("../../images/boldt.jpg", IMREAD_GRAYSCALE));
	imshow("Original Image", GrayscaleImage);

	Mat sobelX, sobelY;
	Sobel(GrayscaleImage, sobelX, CV_8U, 1, 0, 3, 0.4, 128);
	Sobel(GrayscaleImage, sobelY, CV_8U, 0, 1, 3, 0.4, 128);
	imshow("SobelX Image", sobelX);// sobelX.type() == CV_8UC3
	imshow("SobelY Image", sobelY);
	cout << CV_8UC3 << " " << sobelX.type() << endl;
	
	
	// Compute norm of Sobel
	Sobel(GrayscaleImage, sobelX, CV_16S, 1, 0);
	Sobel(GrayscaleImage, sobelY, CV_16S, 0, 1);
	
	Mat sobel;
	// Compute the L1 norm
	sobel = abs(sobelX) + abs(sobelY);
	
	//Find the max value of Sobel
	double sobMin, sobMax;
	minMaxLoc(sobel, &sobMin, &sobMax);

	//Convert to 8-bit image
	Mat sobelImage;
	sobel.convertTo(sobelImage, CV_8U, -255./sobMax, 255);
	imshow("Sobel Image", sobelImage);

	Mat sobelThresholdLow, sobelThresholdHigh;
	threshold(sobelImage, sobelThresholdLow, 225, 255, THRESH_BINARY);
	threshold(sobelImage, sobelThresholdHigh, 180, 255, THRESH_BINARY);
	imshow("Binary Sobel Image(low)", sobelThresholdLow);
	imshow("Binary Sobel Image(high)", sobelThresholdHigh);
	waitKey(0);
	return 0;
}

