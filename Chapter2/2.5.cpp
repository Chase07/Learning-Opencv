#include<iostream>
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<math.h>
using namespace::cv;
using namespace::std;

void colorReduce1(const Mat& image, Mat& result, int div)
{
	//根据给定的长（rows），宽（cols）以及图像类型来创建图像 
	result.create(image.rows, image.cols, image.type());
	int nl = image.rows;
	int nc = image.cols * image.channels();
	for (int j = 0; j < nl; ++j)
	{
		const uchar* data_in = image.ptr<uchar>(j);//ptr是一个模板函数
		uchar* data_out = result.ptr<uchar>(j);

		double n = log10(div) / log10(2);//计算要左移的位数，即缩减因子以2为底的对数
		uchar mask = 0xff << static_cast<int>(n);//强制类型转换
		for (int i = 0; i < nc; ++i)
		{
			//data_out[i] = data_in[i] / div * div + div / 2;//1) 4.00ms
			//*data_out++ = *data_in++ / div * div + div / 2;
			/*注意位运算（&）优先级低于加号运算（+）*/
			//data_out[i] = (data_in[i] & mask) + div / 2;
			*data_out++ = (*data_in++ & mask) + div / 2;//2) 2.51ms 位运算最优，比1）约快38%
			//像素处理完成
		}//整行像素处理完成
	}
}

void colorReduce2(const Mat& image, Mat& result, int div)
{
	//根据给定的长（rows），宽（cols）以及图像类型来创建图像 
	result.create(image.rows, image.cols, image.type());
	int nl = image.rows;
	int nc = image.cols;
	for (int j = 0; j < nl; ++j)
	{
		//得到j行的首地址
		const uchar* data_in = image.ptr<uchar>(j);//ptr是一个模板函数，须知道数据类型
		uchar* data_out = result.ptr<uchar>(j);

		double n = log10(div) / log10(2);//计算要左移的位数，即缩减因子以2为底的对数
		uchar mask = 0xff << static_cast<int>(n);//强制类型转换
		for (int i = 0; i < nc; ++i)
		{
			*data_out++ = (*data_in++ & mask) + div / 2;
			*data_out++ = (*data_in++ & mask) + div / 2;
			*data_out++ = (*data_in++ & mask) + div / 2;
			//像素处理完成
		}//整行像素处理完成
	}
}

void sharpen(const cv::Mat& image, cv::Mat& result)
{
	//result.create(image.rows, image.cols, image.type());
	result.create(image.size(), image.type());
	for (int j = 1; j < image.rows - 1; ++j)
	{
		const uchar* previous = image.ptr<const uchar>(j - 1);//上一行
		const uchar* current = image.ptr<const uchar>(j);//当前行	
		const uchar* next = image.ptr<const uchar>(j + 1);//下一行
		uchar* out = result.ptr<uchar>(j);//输出行的地址
		for (int i = 1; i < image.cols - 1; ++i)
		{
			//处理每一个像素点的3个通道值
			*out++ = cv::saturate_cast<uchar>(5 * (*current++) - *(current - 3) - *(current + 3) - (*previous++) - (*next++));
			*out++ = cv::saturate_cast<uchar>(5 * (*current++) - *(current - 3) - *(current + 3) - (*previous++) - (*next++));
			*out++ = cv::saturate_cast<uchar>(5 * (*current++) - *(current - 3) - *(current + 3) - (*previous++) - (*next++));
		}
	}
	//处理输出图像的边框：像素置0
	result.row(0).setTo(cv::Scalar(0, 0, 0));
	result.row(image.rows - 1).setTo(cv::Scalar(0, 0, 0));
	result.col(0).setTo(cv::Scalar(0, 0, 0));
	result.col(image.cols - 1).setTo(cv::Scalar(0, 0, 0));
	//完成锐化
}

void sharpen2D(const Mat& image, Mat& result)
{
	//新建一个kernel
	Mat kernel(3, 3, CV_32F, Scalar(0));
	//构建核矩阵
	kernel.at<float>(1, 1) = 5.0;
	kernel.at<float>(0, 1) = -1.0;
	kernel.at<float>(2, 1) = -1.0;
	kernel.at<float>(1, 0) = -1.0;
	kernel.at<float>(1, 2) = -1.0;
	//filter2D is in the imgproc.hpp
	cv::filter2D(image, result, image.depth(), kernel);
	//完成锐化，filter2D用于滤波比2.6的更加高效
}
int main()
{
	Mat image = imread("aero1.jpg");
	Mat result;//指向的内存块将在colorReduce函数中创建
	double duration;
	double time = 0;
	for (int i = 0; i < 100; ++i)//执行100次
	{
		duration = static_cast<double>(cv::getTickCount());
		//colorReduce1(image, result, 32);//2.72ms
		colorReduce2(image, result, 32);//2.45ms
		/*测试2.6 和 2.6-extend 的滤波速度*/
		//sharpen(image, result);//24.21ms
		//sharpen2D(image, result);//15.37ms
		duration = static_cast<double>(cv::getTickCount()) - duration;
		duration /= cv::getTickFrequency();
		time += duration;
	}
	time /= 100;//去平均值
	cout << time * 1000 << "ms" << endl;//秒转为毫秒输出
	cvNamedWindow("Image");
	imshow("Image", result);
	waitKey(0);

	/*测试结果：colorReduce2比colorReduce1更快，前者循环次数较少*/
	return 0;
}