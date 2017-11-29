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
	double n = log10(64) / log10(2);//����Ҫ���Ƶ�λ����������������2Ϊ�׵Ķ���
	uchar mask = 0xff << static_cast<int>(n);//ǿ������ת��

	//addWeighted(image1, 0.5, image2, 0.4, 0.0, image1);
	//���ڲ����������أ�����ĺ������ÿɼ��дΪ����ı��ʽ
	//image1 = 0.5 * image1 + 0.4 * image2 + 0.0;
	//ͬ�� 2.5�е�reduce�����ɼ��дΪ����ı��ʽ
	image1 = (image1 & Scalar(mask, mask, mask) + Scalar(div / 2, div / 2, div / 2));//�����Ϊ��ɫ˵�����Ѿ�������
	namedWindow("result");
	imshow("result", image1);
	waitKey(0);
	return 0;
}