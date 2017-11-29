#include"4.2.h"
#include"4.5.h"
#include<iostream>

using namespace::std;
using namespace::cv;

int main()
{
	
	ColorHistogram hc;
	Mat color(imread("home.jpg"));//Read a colorful image
	Mat testColor(imread("building.jpg"));
	color = hc.colorReduce(color, 32);//Reduce that image's color
	//Mat imageROI(color(Rect(105, 238, 28, 28)));//Select a piece of white cloud as ROI in home image
	Mat imageROI(color(Rect(250, 230, 150, 150)));//Select a piece of building's wall as ROI in home image
	imshow("ROI", imageROI);
	imshow("Original image", color);

	MatND hist(hc.getHistogram(imageROI));
	
	ContentFinder finder;
	finder.setHistogram(hist);
	finder.setThreshold(0.05f);
	Mat result(finder.find(color, 3));
	imshow("Result image", result);
	waitKey(0);
	return 0;
}