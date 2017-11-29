#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace::cv;
using namespace::std;

void colorReduce(const Mat& image, Mat& result, int div = 64)
{
	//根据给定的长（rows），宽（cols）以及图像类型来创建图像 
	result.create(image.rows, image.cols, image.type());
	int nl = image.rows;
	int nc = image.cols * image.channels();
	for (int j = 0; j < nl; ++j)
	{
		const uchar* data_in = image.ptr<uchar>(j);//ptr是一个模板函数
		uchar* data_out = result.ptr<uchar>(j);
		for (int i = 0; i < nc; ++i)
		{
			data_out[i] = data_in[i] / div * div + div / 2;
			//像素处理完成
		}//整行像素处理完成
	}
}

int main()
{
	Mat image = imread("aero1.jpg");
	Mat result;//指向的内存块将在colorReduce函数中创建
	colorReduce(image, result, 32);
	cvNamedWindow("Image");
	imshow("Image", result);

	Mat empty;
	empty.create(image.rows, image.cols, image.type());
	cvNamedWindow("empty");
	imshow("empty", empty);
	waitKey(0);
	return 0;
}