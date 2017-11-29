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
	Mat imageROI = image1(cv::Rect(10, 350, logo.cols, logo.rows));//������һ������Ȥ����Region of interest����ǰ��������ָ����ʼ����
	Mat mask = imread("opencv-logo-white.png", 0);//����Ҷ�ͼ,�ڶ�������ָ������ͼ�����ɫ����

	//addWeighted(imageROI, 1.0, logo, 1.0, 0.0, imageROI);//logo�����Ȥ�������
	//logo.copyTo(imageROI, logo);//������Ч�����Ͼ����ƣ����룺��Ϊlogo�к��������в���ͨ��ֵΪ0�����logo��ɫδȫ�����Ƶ�ROI
	//logo.copyTo(imageROI);//������ֱ�ӽ�ͼƬ���Ƶ�ROI����Ϊ��δ����ͼ��ı���ɫ
	//logo.copyTo(imageROI, mask);//����mask�еı���ɫ���ֵ�ͨ��ֵΪ0����˸���ʱ������ROI����ͨ����ԭֵ
	
	namedWindow("image");
	imshow("image", image1);
	waitKey(0);
	return 0;
}