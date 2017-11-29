#ifndef COLORDETECTOR_H
#define COLORDETECTOR_H

#include<QtWidgets\QMainWindow>
#include<QFileDialog>
#include "ui_colordetector.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\opencv.hpp>

class ColorDetector : public QMainWindow
{
	Q_OBJECT

public:
	ColorDetector(QWidget *parent = 0);
	~ColorDetector();

private:
	Ui::ColorDetectorClass ui;
	cv::Mat image;
	private slots:
	void on_openImage_clicked();
	void on_process_clicked();
	void on_ok_clicked();
	void on_cancel_clicked();
};
class ColorDetect_algorithm
{
public:
	ColorDetect_algorithm() : minDist(100)
	{
		target[0] = target[1] = target[2] = 0;//默认目标色为黑色
	}
	cv::Mat process(const cv::Mat& image);//算法函数
	void setColorDistanveThreshold(int distance)
	{
		if (distance < 0)//此处的检测保证了minDist的值是合理的
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

#endif // COLORDETECTOR_H
