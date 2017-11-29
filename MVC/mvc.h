#ifndef MVC_H
#define MVC_H

#include<QtWidgets/QMainWindow>
#include"ui_mvc.h"
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/opencv.hpp>
#include<memory>
#include<string>
#include<QFileDialog>
#include<QString>
#include<QColorDialog>


class MVC : public QMainWindow//������
{
	Q_OBJECT

public:
	MVC(QWidget *parent = 0);
	~MVC();
private:
	Ui::MVCClass ui;
	private slots:
	void on_openButton_clicked();
	void on_selectButton_clicked();
	void on_processButton_clicked();
	void on_sliderOfThreshold_valueChaned();
	void on_sliderOfThreshold_sliderMoved();
	
};
class ColorDetector//�㷨������
{
public:
	ColorDetector();
	void setColorDistanceThreshold(int distance);
	int getColorDistanceThreshold() const;
	void setTargetColor(unsigned char blue, unsigned char green, unsigned char red);
	void setTargetColor(cv::Vec3b color);
	cv::Vec3b getTargetColor() const;
	int getDistance(const cv::Vec3b& color) const;//��������ʹ�õļ�����뺯��
	cv::Mat process(const cv::Mat& image);
	

private:
	int minDist;//���̶�
	cv::Vec3b target;//�����ɫ
	cv::Mat result;//�����ͼ��
	cv::Mat converted;//ת����ͼ��

};
class ColorDetectController//�ؼ���
{
public:
	//�û�(�ؼ�)ʹ�õĺ���
	void setColorDistanceThreshold(int distance);
	int getColorDistanceThreshold() const;
	void setTargetColor(unsigned char blue, unsigned char green, unsigned char red);
	void setTargetColor(cv::Vec3b color);
	void getTargetColor(unsigned char& blue, unsigned char& green, unsigned char& red) const;//ͨ�����ã���¼���ڲ�ͼ���ͨ��ֵ
	bool setInputImage(std::string fileName);
	const cv::Mat getInputImage() const;
	void process();
	const cv::Mat getLastResult() const;
	
	
	~ColorDetectController();//����cdetectָ�򴴽��Ķ�������ͷ��ڴ�	
	static ColorDetectController* getInstance();
	static void destroy();//���ٿؼ�����
private:
	ColorDetector *cdetect;
	ColorDetectController();//˽�еĹ��캯��
	static ColorDetectController* singleton;
	cv::Mat image;//������ͼ��
	cv::Mat result;//�����ͼ��

};
#endif// MVC_H
