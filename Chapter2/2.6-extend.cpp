#include<iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>

using namespace::std;
using namespace::cv;

void sharpen2D(const Mat& image, Mat& result)
{
	//新建一个kernel
	Mat kernel(3, 3, CV_32F, Scalar(0));
	//构建核矩阵
	kernel.at<float>(1, 1) =  5.0;
	kernel.at<float>(0, 1) = -1.0;
	kernel.at<float>(2, 1) = -1.0;
	kernel.at<float>(1, 0) = -1.0;
	kernel.at<float>(1, 2) = -1.0;
	//filter2D is in the imgproc.hpp
	cv::filter2D(image, result, image.depth(), kernel);
	//完成锐化，filter2D用于滤波比2.6的更加高效
}

int main()
{
	Mat image = imread("building.jpg");
	Mat result;
	sharpen2D(image, result);
	
	namedWindow("Sharpened");
	imshow("Sharpened", result);
	waitKey(0);
	return 0;
}