#include<iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>

using namespace::std;
using namespace::cv;

int main()
{
	Mat logo = imread("opencv-logo-white.png");
	Mat image1 = imread("building.jpg");
	Mat imageROI = image1(cv::Rect(10, 350, logo.cols, logo.rows));//定义了一个感兴趣区域（Region of interest）；前两个参数指明起始坐标
	Mat mask = imread("opencv-logo-white.png", 0);//载入灰度图,第二个参数指定加载图像的颜色类型

	//addWeighted(imageROI, 1.0, logo, 1.0, 0.0, imageROI);//logo与感兴趣区域相加
	//logo.copyTo(imageROI, logo);//这句代码效果与上句类似；猜想：因为logo中红蓝黄中有部分通道值为0，因此logo颜色未全部复制到ROI
	//logo.copyTo(imageROI);//不可以直接将图片复制到ROI，因为尚未忽略图标的背景色
	//logo.copyTo(imageROI, mask);//由于mask中的背景色部分的通道值为0，因此复制时保留了ROI部分通道的原值
	
	namedWindow("image");
	imshow("image", image1);
	waitKey(0);
	return 0;
}