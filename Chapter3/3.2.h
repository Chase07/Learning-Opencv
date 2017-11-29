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
		target[0] = target[1] = target[2] = 0;//默认目标色为黑色
	}
	cv::Mat process(const cv::Mat& image);//算法函数
	void setColorDistanveThreshold(int distance) 
	{
		if(distance < 0)//此处的检测保证了minDist的值是合理的
		{
			minDist = 0;
		}
		else
		{
			minDist = distance;
		}
	}
	//两种设置颜色的方式
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
	//方便用户查询自己设置的参数
	int getColorDistanceThreshold() const { return minDist; }
	cv::Vec3b getTargetColor() const { return target; }
private:
	int minDist;//容忍度
	cv::Vec3b target;//待检测的目标颜色
	cv::Mat result;//结果图像
	int getDistance(const cv::Vec3b& color) const;//获得街区距离
};
cv::Mat ColorDetector::process(const cv::Mat& image)
{
	result.create(image.size(), CV_8UC1);//结果图像在此被指定新的大小，CV_8U等同于CV_8UC1
	//输入图像的首尾迭代器
	cv::Mat_<cv::Vec3b>::const_iterator it = image.begin<cv::Vec3b>();
	cv::Mat_<cv::Vec3b>::const_iterator itend = image.end<cv::Vec3b>();
	//输出图像的迭代器
	cv::Mat_<uchar>::iterator itout = result.begin<uchar>();
	//上面：Vec3b是3个uchar构成的vector类型
	//下面：遍历每个像素，对比街区距离和容忍度并做相应处理
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
	//return abs(color[0] - target[0]) + abs(color[1] - target[1]) + abs(color[2] - target[2]);//计算街区距离
	return static_cast<int>(cv::norm<int, 3>(cv::Vec3i(color[0] - target[0], color[1] - target[1], color[2] - target[2])));//计算欧拉长度
}
#endif