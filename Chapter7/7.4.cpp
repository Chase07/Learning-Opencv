
#include"7.3.h"

using namespace::std;
using namespace::cv;

int main()
{
	Mat GrayScaleImage(imread("../../images/road.jpg", IMREAD_GRAYSCALE));
	Mat contours;
	// Apply Canny algorithm
	Canny(GrayScaleImage, contours, 125, 350);
	imshow("Contours Image", contours);
	// Creat LineFinder instance
	LineFinder lineFinder;
	// Set probabilistic Hough parameters
	lineFinder.setLineLengthAndGap(100, 20);
	lineFinder.setMinvote(80);
	
	vector<cv::Vec4i> lines;
	// Detect lines and draw them
	lines = lineFinder.findLines(contours);


	int n = 0;
	// Creat a balck image
	Mat oneLine(contours.size(), CV_8U, Scalar(0));
	// Draw a white line
	line(oneLine,
		Point(lines[n][0], lines[n][1]),
		Point(lines[n][2], lines[n][3]),
		Scalar(255),// white
		3);// width of 5 pixel0
	// contours AND white line
	//bitwise_and(contours, oneLine, oneLine);
	bitwise_not(oneLine, oneLine);
	imshow("One Line Image", oneLine);

	vector<Point> points;
	// Iterate over the pixels to obtain all points positions
	for  (int y = 0; y < oneLine.rows; ++y)
	{
		// Row y
		uchar *rowPtr = oneLine.ptr<uchar>(y);
		for (int x = 0; x < oneLine.cols; ++x)
		{
			// Column x
			// If on a contour
			if (rowPtr[x])
			{
				points.push_back(Point(x, y));
			}
		}

	}
	Vec4f line;
	fitLine(Mat(points), line, 
		CV_DIST_L2,// Distance type
		0,// Not used with L2 distance
		0.01, 0.01);// accurancy

	int x0 = line[2];   int y0 = line[3];// A point on the line
	int x1 = x0 - 200 * line[0];// Add a vector of length 200
	int y1 = y0 - 200 * line[1];// Using the unit vector
	Mat OriginalImage(imread("../../images/road.jpg"));
	cv::line(OriginalImage, Point(x0, y0), Point(x1, y1), Scalar(0), 3);
	imshow("Estimated Line Image", OriginalImage);

	waitKey(0);
	return 0;
}