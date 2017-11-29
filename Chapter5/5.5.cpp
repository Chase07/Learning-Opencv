#include"5.5.h"
#include<iostream>

using namespace::cv;
using namespace::std;

int main()
{
	// Read the original image
	Mat OriginalImage(imread("../../images/group.jpg", IMREAD_COLOR));
	
	// Read as a grayscale image
	Mat GrayscaleImage(imread("../../images/group.jpg", IMREAD_GRAYSCALE));
	// Obtain the binary image 
	Mat binaryImage;
	threshold(GrayscaleImage, binaryImage, 60, 255, THRESH_BINARY);
	bitwise_not(binaryImage, binaryImage, Mat());// NOT
	imshow("Original Binary Image", binaryImage);
	
	Mat fg;
	// Eliminate noise as well as small object by eroding 6 times
	erode(binaryImage, fg, Mat(), Point(-1, -1), 6);
	imshow("Foreground Image", fg);
	
	Mat bg;
	dilate(binaryImage, bg, Mat(), Point(-1, -1), 6);
	imshow("Original Background Image", bg);
	// Highlight the background object by thresholding the bg Image
	threshold(bg, bg, 1, 128, THRESH_BINARY_INV);
	imshow("Background Image", bg);

	// Creating the markers Image
	Mat markers(binaryImage.size(), CV_8U, Scalar(0));
	markers = fg + bg;
	imshow("Markers Image", markers);
	
	// Creating the watershed segmentation object
	WatershedSegmenter segmenter;
	Mat watersheds;
	segmenter.setMarkers(markers);
	watersheds = segmenter.process(OriginalImage);
	imshow("Segmentation", segmenter.getSegmentation());
	imshow("Watersheds", segmenter.getWatersheds());
	waitKey(0);
	return 0;
}
