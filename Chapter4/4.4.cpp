#include"4.2.h"
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace::std;
using namespace::cv;

int main()
{
	Mat imageROI, image(imread("home.jpg"));
	imageROI = image(Rect(105, 238, 28, 28));
	Histogram1D h;
	MatND hist = h.getHistogram(imageROI);
	
	namedWindow("image");
	namedWindow("ROI");


	imshow("ROI", imageROI);
	imshow("image", image);
	waitKey(0);


	return 0;
}