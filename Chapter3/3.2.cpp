#include<iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include"3.2.h"

using namespace::std;
using namespace::cv;


int main()
{
	//ColorDetector cdetect;
	//Mat image = imread("building.jpg");
	//if (!image.data)
	//	return 0;
	//cdetect.setTargetColor(230, 190, 130);//the color of sky
	//namedWindow("result");
	//imshow("result", cdetect.process(image));
	//cout << cdetect.getColorDistanceThreshold() << " " << cdetect.getTargetColor() << endl;
	
	
	/*small test*/
	cv::Mat m1 = cv::imread("1.png");
	const cv::Mat m2 = cv::imread("1.png");
	m1 = m2;//m1 指向了 m2 
	m1.at<Vec3b>(0, 0)[0] = 255;//通过m1修改了m2所指的图像
	cout << m1 << endl;
	cout << m2 << endl;
	waitKey(0);
	return 0;
}
