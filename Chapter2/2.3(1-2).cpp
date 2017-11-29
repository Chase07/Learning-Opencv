#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace::cv;
using namespace::std;

void colorReduce(const Mat& image, Mat& result, int div = 64)
{
	//���ݸ����ĳ���rows������cols���Լ�ͼ������������ͼ�� 
	result.create(image.rows, image.cols, image.type());
	int nl = image.rows;
	int nc = image.cols * image.channels();
	for (int j = 0; j < nl; ++j)
	{
		const uchar* data_in = image.ptr<uchar>(j);//ptr��һ��ģ�庯��
		uchar* data_out = result.ptr<uchar>(j);
		for (int i = 0; i < nc; ++i)
		{
			data_out[i] = data_in[i] / div * div + div / 2;
			//���ش������
		}//�������ش������
	}
}

int main()
{
	Mat image = imread("aero1.jpg");
	Mat result;//ָ����ڴ�齫��colorReduce�����д���
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