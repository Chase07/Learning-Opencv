#include<iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>

using namespace::std;
using namespace::cv;

void sharpen(const cv::Mat& image, cv::Mat& result)
{
	//result.create(image.rows, image.cols, image.type());
	result.create(image.size(), image.type());
	for (int j = 1; j < image.rows - 1; ++j)
	{
		const uchar* previous = image.ptr<const uchar>(j - 1);//��һ��
		const uchar* current = image.ptr<const uchar>(j);//��ǰ��	
		const uchar* next = image.ptr<const uchar>(j + 1);//��һ��
		uchar* out = result.ptr<uchar>(j);//����еĵ�ַ
		for (int i = 1; i < image.cols - 1; ++i)
		{
			//����ÿһ�����ص��3��ͨ��ֵ
			*out++ = cv::saturate_cast<uchar>(5 * (*current++) - *(current - 3) - *(current + 3) - (*previous++) - (*next++));
			*out++ = cv::saturate_cast<uchar>(5 * (*current++) - *(current - 3) - *(current + 3) - (*previous++) - (*next++));
			*out++ = cv::saturate_cast<uchar>(5 * (*current++) - *(current - 3) - *(current + 3) - (*previous++) - (*next++));
		}
	}
	//�������ͼ��ı߿�������0
	result.row(0).setTo(cv::Scalar(0, 0, 0));
	result.row(image.rows - 1).setTo(cv::Scalar(0, 0, 0));
	result.col(0).setTo(cv::Scalar(0, 0, 0));
	result.col(image.cols - 1).setTo(cv::Scalar(0, 0, 0));
	//�����
}

int main()
{
	Mat image = imread("building.jpg");
	Mat result;
	sharpen(image, result);

	cvNamedWindow("Sharpened");
	imshow("Sharpened", result);
	waitKey(0);
	return 0;
}