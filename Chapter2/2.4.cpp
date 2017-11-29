#include<iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
using namespace::cv;
using namespace::std;

void colorReduce(Mat& image, int div = 64)
{
	//两种声明图像迭代器的方式
	cv::MatIterator_<cv::Vec3b> it1;
	cv::Mat_<cv::Vec3b>::iterator it2;

	it1 = image.begin<cv::Vec3b>() + image.rows * 440;
	it2 = image.end<cv::Vec3b>();
	for (; it1 != it2; it1 += 3)
	{
		(*it1)[0] = (*it1)[0] / div * div + div / 2;
		(*it1)[1] = (*it1)[1] / div * div + div / 2;
		(*it1)[2] = (*it1)[2] / div * div + div / 2;
	}
}
int main()
{
	Mat image = imread("aero1.jpg");
	cout << image.rows << " " << image.cols << endl;
	colorReduce(image);
	cvNamedWindow("reducedImage");
	imshow("reducedImage", image);

	waitKey(0);
}
