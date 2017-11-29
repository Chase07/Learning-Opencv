
#include<opencv2\opencv.hpp>

using namespace::std;
using namespace::cv;

int main()
{
	// Read a original image
	Mat image(imread("../../images/boldt.jpg"));
	Mat result;
	// Low-pass filter
	blur(image, result, cv::Size(5, 5));
	imshow("Original Image", image);
	imshow("Normal Blur Image", result);
	// Gaussian low-pass filter
	GaussianBlur(image, result, cv::Size(5, 5), 1.5);
	imshow("Gaussian Blur Image", result);

	Mat resizedImage;
	pyrDown(image, resizedImage);
	imshow("Reduced Image", resizedImage); 
	resize(image, resizedImage, cv::Size(image.cols / 3, image.rows / 3));
	imshow("Resized Image", resizedImage);

	waitKey(0);
	return 0;
}