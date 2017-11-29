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
		//���ض��������ֵ����Ϊ255����ɫ��
		if (image.channels() == 1)//ͨ��Ϊ1���Ҷ�ͼ
		{
			image.at<uchar>(j, i) = 255;
		}
		else if (image.channels() == 3)//ͨ��Ϊ3�� ��ɫͼ
		{
			//���룺��ɫͼ��һ�����ص���һ��sizeΪ3��vector
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
	//�����͸�
	cout << image.cols << " " << image.rows << " = " << image.total() << endl;
	cvNamedWindow("salt image");
	imshow("sale image", image);
	waitKey(0);
	return 0;
}
