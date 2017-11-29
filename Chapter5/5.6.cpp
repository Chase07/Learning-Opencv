#include<iostream>
#include<opencv2\opencv.hpp>

using namespace::std;
using namespace::cv;

int main()
{
	// Read the original image
	Mat OriginalImage(imread("../../images/group.jpg", IMREAD_COLOR));

	// Define bounding rectangle, the pixels outside this rectangle will be labeled as background
	Rect rectangle(10, 100, 380, 180);
	Mat testImage(OriginalImage.clone());
	cv::rectangle(testImage, rectangle, cv::Scalar(0, 0, 255));
	imshow("Original Image", testImage);

	Mat result;// The segmentation
	Mat bgModel, fgModel;// The models
	
	double duration = static_cast<double>(getTickCount());
	// GrabCut segmentation
	grabCut(OriginalImage, // input image
			result,// segmentation result
			rectangle,// containing foreground
			bgModel, fgModel,// models
			5,// number of iterations
			GC_INIT_WITH_RECT);//use rectangle
	duration = (static_cast<double>(getTickCount()) - duration) / getTickFrequency();
	imshow("Original Result Image", result);
	// Get the pixels marked as likely foreground
	compare(result, GC_PR_FGD, result, CMP_EQ);
	imshow("Afer Compared Result Image", result);

	// Generate an full-white output image of full-white color
	Mat foreground(OriginalImage.size(), CV_8UC3, Scalar(255, 255, 255)); 
	OriginalImage.copyTo(foreground, result);
	imshow("Foreground Image", foreground);
	cout << duration << "s" << endl;
	waitKey(0);
	return 0;
}
