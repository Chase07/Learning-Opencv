#include"4.2.h"
#include<iostream>
#include<opencv2/imgproc/imgproc.hpp>

using namespace::std;
using namespace::cv;

int main()
{
	//int dim(256);
	//Mat lut(1, &dim, CV_8U);
	////cout << lut << endl;
	//for (int i = 0; i != 256; ++i)
	//{
	//	lut.at<uchar>(i) = 255 - i;
	//}
	//cout << lut << endl;
	Mat image(imread("chenglin.jpg"));
	//4.3:
	Histogram1D h;
	/*Mat streteched = h.stretch(image, 1000);
	namedWindow("original histogram");
	imshow("original histogram", h.getHistogramImage(image));
	namedWindow("streteched histogram");
	imshow("streteched histogram", h.getHistogramImage(streteched));
	namedWindow("original image");
	imshow("original image", image);
	namedWindow("streteched image");
	imshow("streteched image", streteched);*/
	
	//4.4:
	namedWindow("equalized image");
	imshow("equalized image", h.equalize(image));
	waitKey(0);
	return 0;
}