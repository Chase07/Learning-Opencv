#include"4.2.h"
#include<iostream>
#include<opencv2/imgproc/imgproc.hpp>

using namespace::std;
using namespace::cv;

int main()
{

	Mat image = imread("baboon.jpg");
	Histogram1D h;
	MatND histo = h.getHistogram(image);
	long double sum = 0.0;

	for (int i = 0; i != 256; ++i)
	{
		sum += histo.at<float>(i);
		cout << "Value" << i << " = "<< histo.at<float>(i, 0) << endl;
	}
	cout << "sum = " << sum << endl;
	
	waitKey(0);
}