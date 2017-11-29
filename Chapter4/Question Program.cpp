
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp> 

class ColorHistogram
{
private:
	int bins;//The number of bins
	int histSize[3];//Means there are 3 dims in histogram 
	float hranges[2];//Save the minimum and maximum value of each bin
	const float* ranges[3];//Range of each bin
	int channels[3];
public:
	ColorHistogram() :bins(256)
	{
		//Initialize:
		histSize[0] = histSize[1] = histSize[2] = bins;
		hranges[0] = 0.0;
		hranges[1] = 255.0;
		ranges[0] = ranges[1] = ranges[2] = hranges;
		channels[0] = 0;
		channels[1] = 1;
		channels[2] = 2;

	}
	cv::MatND getHistogram(cv::Mat& image)
	{
		cv::MatND hist;
		calcHist(&image, 1, channels, cv::Mat(), hist, 3, histSize, ranges);//Calculate the histogram
		return hist;
	}
};
class ContentFinder
{
private:
	float hranges[2];
	const float* ranges[3];
	int channels[3];
	cv::MatND histogram;
public:
	ContentFinder()
	{
		hranges[0] = 0.0;
		hranges[1] = 255.0;
		ranges[0] = hranges;
		ranges[1] = hranges;
		ranges[2] = hranges;
		///////////////////////
		/*改了这里*/
		channels[0] = 0;
		channels[1] = 1;
		channels[2] = 2;
	}
	void setHistogram(const cv::MatND& h)
	{
		histogram = h;
		//////////归一化的值改为255
		normalize(histogram, histogram, 255.0);//Normalizing the histogram
	}
	cv::Mat find(const cv::Mat& image, int dim)
	{
		cv::Mat result;//The result of backprojecting
		for (int i = 0; i != dim; ++i)
		{
			calcBackProject(&image, 1, channels, histogram, result, ranges, 255.0);//Backprojecting here
		}
		return result;
	}
};

int main()
{
	ColorHistogram hc;
	cv::Mat colorImage(cv::imread("home.jpg"));//Read a colorful image
	cv::Mat imageROI(colorImage(cv::Rect(250, 230, 150, 150)));//Select a piece of building's wall as ROI in home image
	//cv::Mat imageROI(colorImage(cv::Rect(105, 238, 28, 28)));//Select a piece of white cloud as ROI in home image
	imshow("ROI", imageROI);
	imshow("Original image", colorImage);

	cv::MatND histOfROI(hc.getHistogram(imageROI));//Get the histogram of ROI

	ContentFinder finder;
	finder.setHistogram(histOfROI);//Pass that histogram of ROI and normalizing it
	cv::Mat result(finder.find(colorImage, 3));
	imshow("Result image", result);   
	/*Error: Got an all black result here, 
	 *which means everywhere of colorImage may
	 *same as that imageROI and it must something wrong
	 */
	cv::waitKey(0);
	return 0;
}