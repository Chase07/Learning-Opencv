#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace::cv;
using namespace::std;

void salt(Mat& image, int n)
{
	for (int k = 0; k < n; ++k)
	{

		int i = rand() % image.cols;
		int j = rand() % image.rows;
		//将特定点的像素值设置为255（白色）
		if (image.channels() == 1)//通道为1，灰度图
		{
			image.at<uchar>(j, i) = 255;
		}
		else if (image.channels() == 3)//通道为3， 彩色图
		{
			//猜想：彩色图的一个像素点是一个size为3的vector
			image.at<Vec3b>(j, i)[0] = 255;
			image.at<Vec3b>(j, i)[1] = 255;
			image.at<Vec3b>(j, i)[2] = 255;
		}
	}
}

int main()
{
	Mat image = imread("aero1.jpg");
	salt(image, 30000);
	//输出宽和高
	cout << image.cols << " " << image.rows << " = " << image.total() << endl;
	cvNamedWindow("salt image");
	imshow("sale image", image);
	waitKey(0);
	return 0;
}
