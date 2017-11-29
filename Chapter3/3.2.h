#ifndef _3_2_H
#define _3_2_H
#include<iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<math.h>

class ColorDetector
{
public:
	ColorDetector() : minDist(100) 
	{
		target[0] = target[1] = target[2] = 0;//Ĭ��Ŀ��ɫΪ��ɫ
	}
	cv::Mat process(const cv::Mat& image);//�㷨����
	void setColorDistanveThreshold(int distance) 
	{
		if(distance < 0)//�˴��ļ�Ᵽ֤��minDist��ֵ�Ǻ����
		{
			minDist = 0;
		}
		else
		{
			minDist = distance;
		}
	}
	//����������ɫ�ķ�ʽ
	void setTargetColor(unsigned char blue, unsigned char green, unsigned char red)
	{
		target[0] = blue;
		target[1] = green; 
		target[2] = red;
	}
	void setTargetColor(cv::Vec3b color)
	{
		target = color;
	}
	//�����û���ѯ�Լ����õĲ���
	int getColorDistanceThreshold() const { return minDist; }
	cv::Vec3b getTargetColor() const { return target; }
private:
	int minDist;//���̶�
	cv::Vec3b target;//������Ŀ����ɫ
	cv::Mat result;//���ͼ��
	int getDistance(const cv::Vec3b& color) const;//��ý�������
};
cv::Mat ColorDetector::process(const cv::Mat& image)
{
	result.create(image.size(), CV_8UC1);//���ͼ���ڴ˱�ָ���µĴ�С��CV_8U��ͬ��CV_8UC1
	//����ͼ�����β������
	cv::Mat_<cv::Vec3b>::const_iterator it = image.begin<cv::Vec3b>();
	cv::Mat_<cv::Vec3b>::const_iterator itend = image.end<cv::Vec3b>();
	//���ͼ��ĵ�����
	cv::Mat_<uchar>::iterator itout = result.begin<uchar>();
	//���棺Vec3b��3��uchar���ɵ�vector����
	//���棺����ÿ�����أ��ԱȽ�����������̶Ȳ�����Ӧ����
	for (; it != itend; ++it, ++itout)
	{
		if(getDistance(*it) < minDist)
		{
			*itout = 255;
		}
		else
		{ 
			*itout = 0;
		}
	}

	return result;
}
int ColorDetector::getDistance(const cv::Vec3b& color) const
{
	//return abs(color[0] - target[0]) + abs(color[1] - target[1]) + abs(color[2] - target[2]);//�����������
	return static_cast<int>(cv::norm<int, 3>(cv::Vec3i(color[0] - target[0], color[1] - target[1], color[2] - target[2])));//����ŷ������
}
#endif