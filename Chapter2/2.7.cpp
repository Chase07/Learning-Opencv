#include<iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<math.h>

using namespace::std;
using namespace::cv;

int main()
{
	Mat image1 = imread("aero1.jpg");
	Mat image2 = imread("aero3.jpg");
	int div = 64;
	double n = log10(64) / log10(2);//计算要左移的位数，即缩减因子以2为底的对数
	uchar mask = 0xff << static_cast<int>(n);//强制类型转换

	//addWeighted(image1, 0.5, image2, 0.4, 0.0, image1);
	//由于操作符被重载，上面的函数调用可简洁写为下面的表达式
	//image1 = 0.5 * image1 + 0.4 * image2 + 0.0;
	//同理， 2.5中的reduce函数可简洁写为下面的表达式
	image1 = (image1 & Scalar(mask, mask, mask) + Scalar(div / 2, div / 2, div / 2));//运算符为灰色说明其已经被重载
	namedWindow("result");
	imshow("result", image1);
	waitKey(0);
	return 0;
}