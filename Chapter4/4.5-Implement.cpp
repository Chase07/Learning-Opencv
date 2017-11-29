#include"4.5.h"
#include <opencv2/imgproc/imgproc.hpp>

using namespace::std;
using namespace::cv;

/*******Class ContentFinder*******/
//Public Part:
ContentFinder::ContentFinder() :threshold(-1.0f)
{
	hranges[0] = 0.0;
	hranges[1] = 255.0;
	ranges[0] = hranges;
	ranges[1] = hranges;
	ranges[2] = hranges;
	channels[0] = 0;
	channels[1] = 1;
	channels[2] = 2;
}
void ContentFinder::setThreshold(float t)
{
	threshold = t;
}
float ContentFinder::getThreshold()
{
	return threshold;
}
void ContentFinder::setHistogram(const MatND& h)
{
	histogram = h;
	normalize(histogram, histogram, 1.0);//Normalizing the histogram
}
Mat ContentFinder::find(const cv::Mat& image, int dim)
{
	Mat result;//The result of backprojecting
	for (int i = 0; i != dim; ++i)
	{
		calcBackProject(&image, 1, channels, histogram, result, ranges, 255.0);
	}
	if (threshold > 0.0)
	{
		cv::threshold(result, result, 255 * threshold, 255, THRESH_BINARY);
	}
	return result;
}
/*******Class ColorHistogram*******/
//Public Part:
ColorHistogram::ColorHistogram()
{
	histSize[0] = histSize[1] = histSize[2] = bins;
	hranges[0] = 0.0;
	hranges[1] = 255.0;
	ranges[0] = ranges[1] = ranges[2] = hranges;
	channels[0] = 0;
	channels[1] = 1;
	channels[2] = 2;

}
Mat ColorHistogram::colorReduce(Mat& image, int div)
{
	int nl = image.rows;
	int nc = image.cols;
	for (int j = 0; j < nl; ++j)
	{
		//得到j行的首地址
		const uchar* data_in = image.ptr<uchar>(j);//ptr是一个模板函数，须知道数据类型
		uchar* data_out = image.ptr<uchar>(j);

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
	return image;
}
MatND ColorHistogram::getHistogram(Mat& image)
{
	MatND hist;
	calcHist(&image, 1, channels, cv::Mat(), hist, 3, histSize, ranges);
	return hist;
}
//void ColorHistogram::showHistogram(MatND& hist)
//{
//
//}

