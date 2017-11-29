#include<iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<math.h>
using namespace::cv;
using namespace::std;

void colorReduce1(const Mat& image, Mat& result, int div)
{
	//���ݸ����ĳ���rows������cols���Լ�ͼ������������ͼ�� 
	result.create(image.rows, image.cols, image.type());
	int nl = image.rows;
	int nc = image.cols * image.channels();
	for (int j = 0; j < nl; ++j)
	{
		const uchar* data_in = image.ptr<uchar>(j);//ptr��һ��ģ�庯��
		uchar* data_out = result.ptr<uchar>(j);

		double n = log10(div) / log10(2);//����Ҫ���Ƶ�λ����������������2Ϊ�׵Ķ���
		uchar mask = 0xff << static_cast<int>(n);//ǿ������ת��
		for (int i = 0; i < nc; ++i)
		{
			//data_out[i] = data_in[i] / div * div + div / 2;//1) 4.00ms
			//*data_out++ = *data_in++ / div * div + div / 2;
			/*ע��λ���㣨&�����ȼ����ڼӺ����㣨+��*/
			//data_out[i] = (data_in[i] & mask) + div / 2;
			*data_out++ = (*data_in++ & mask) + div / 2;//2) 2.51ms λ�������ţ���1��Լ��38%
			//���ش������
		}//�������ش������
	}
}

void colorReduce2(const Mat& image, Mat& result, int div)
{
	//���ݸ����ĳ���rows������cols���Լ�ͼ������������ͼ�� 
	result.create(image.rows, image.cols, image.type());
	int nl = image.rows;
	int nc = image.cols;
	for (int j = 0; j < nl; ++j)
	{
		//�õ�j�е��׵�ַ
		const uchar* data_in = image.ptr<uchar>(j);//ptr��һ��ģ�庯������֪����������
		uchar* data_out = result.ptr<uchar>(j);

		double n = log10(div) / log10(2);//����Ҫ���Ƶ�λ����������������2Ϊ�׵Ķ���
		uchar mask = 0xff << static_cast<int>(n);//ǿ������ת��
		for (int i = 0; i < nc; ++i)
		{
			*data_out++ = (*data_in++ & mask) + div / 2;
			*data_out++ = (*data_in++ & mask) + div / 2;
			*data_out++ = (*data_in++ & mask) + div / 2;
			//���ش������
		}//�������ش������
	}
}

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

void sharpen2D(const Mat& image, Mat& result)
{
	//�½�һ��kernel
	Mat kernel(3, 3, CV_32F, Scalar(0));
	//�����˾���
	kernel.at<float>(1, 1) = 5.0;
	kernel.at<float>(0, 1) = -1.0;
	kernel.at<float>(2, 1) = -1.0;
	kernel.at<float>(1, 0) = -1.0;
	kernel.at<float>(1, 2) = -1.0;
	//filter2D is in the imgproc.hpp
	cv::filter2D(image, result, image.depth(), kernel);
	//����񻯣�filter2D�����˲���2.6�ĸ��Ӹ�Ч
}
int main()
{
	Mat image = imread("aero1.jpg");
	Mat result;//ָ����ڴ�齫��colorReduce�����д���
	double duration;
	double time = 0;
	for (int i = 0; i < 100; ++i)//ִ��100��
	{
		duration = static_cast<double>(cv::getTickCount());
		//colorReduce1(image, result, 32);//2.72ms
		colorReduce2(image, result, 32);//2.45ms
		/*����2.6 �� 2.6-extend ���˲��ٶ�*/
		//sharpen(image, result);//24.21ms
		//sharpen2D(image, result);//15.37ms
		duration = static_cast<double>(cv::getTickCount()) - duration;
		duration /= cv::getTickFrequency();
		time += duration;
	}
	time /= 100;//ȥƽ��ֵ
	cout << time * 1000 << "ms" << endl;//��תΪ�������
	cvNamedWindow("Image");
	imshow("Image", result);
	waitKey(0);

	/*���Խ����colorReduce2��colorReduce1���죬ǰ��ѭ����������*/
	return 0;
}