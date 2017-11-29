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
		target[0] = target[1] = target[2] = 0;//Ĭ��Ŀ��ɫΪ��ɫ
	}
	cv::Mat process(const cv::Mat& image);//�㷨����
	void setColorDistanveThreshold(int distance)
	{
		if (distance < 0)//�˴��ļ�Ᵽ֤��minDist��ֵ�Ǻ����
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

#endif // COLORDETECTOR_H
