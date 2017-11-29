#include<iostream>
#include<opencv2\opencv.hpp>

using namespace::std;
using namespace::cv;

void salt(cv::Mat& image, cv::Mat& result, int n)
{
	image.copyTo(result);
	for (int k = 0; k != n; ++k)
	{
		int i = rand() % result.cols;
		int j = rand() % result.rows;
		if (result.channels() == 1)// Grayscale result
		{
			result.at<uchar>(j, i) = 255;
		}
		else if (result.channels() == 3)// Color result
		{
			result.at<cv::Vec3b>(j, i)[0] = 255;
			result.at<cv::Vec3b>(j, i)[1] = 255;
			result.at<cv::Vec3b>(j, i)[2] = 255;
		}
	}

}

int main()
{
	// Read an image
	cv::Mat OriginalImage(imread("../../images/boldt.jpg"));
	imshow("Original Image", OriginalImage);

	cv::Mat saltImage;
	salt(OriginalImage, saltImage, 3000);
	imshow("Salt Image", saltImage); 

	Mat result;
	medianBlur(OriginalImage, result, 5);
	imshow("Result Image", result);

	waitKey(0);
	return 0;
}
