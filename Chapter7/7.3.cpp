#include"7.3.h"
using namespace::std;

int main()
{
	
	cv::Mat grayScaleImage(cv::imread("../../images/road.jpg", cv::IMREAD_GRAYSCALE));
	cv::imshow("Gray Scale Image", grayScaleImage);
	// Apply Canny algorithm
	cv::Mat contours;// Output contours
	cv::Canny(grayScaleImage, contours,
		125, // Low threshold
		350);// High threshold
	//std::vector<cv::Vec2f> lines;
	//cv::HoughLines(contours, lines, 1,
	//	M_PI / 180,// Step size
	//	80);// Minimun number of votes

	cv::Mat result(cv::imread("../../images/road.jpg"));
	//vector<cv::Vec2f>::const_iterator cur = lines.begin();
	//for (;cur != lines.end(); ++cur)
	//{
	//	float rho = (*cur)[0];
	//	float theta = (*cur)[1];
	//	if (theta < M_PI / 4. || theta > 3. * M_PI / 4.)// Almost vertical line
	//	{
	//		// The point of interection of the line with first row of image
	//		cv::Point pt1(static_cast<int> (rho / cos(theta)), 0);

	//		// The point of interection of the line with last row of image
	//		cv::Point pt2(static_cast<int> ((rho - result.rows * sin(theta)) / cos(theta)), result.rows);

	//		// Draw the white line
	//		cv::line(result, pt1, pt2, cv::Scalar(255), 1);
	//	}
	//	else// Almost horizontal line
	//	{
	//		// The point of interection of the line with first column of the image
	//		cv::Point pt1(0, static_cast<int> (rho / sin(theta)));
	//		// The point of interection of the line with last column of the image
	//		cv::Point pt2(result.cols, static_cast<int> ((rho - result.cols * cos(theta)) / sin(theta)));
	//		// Draw a withe line
	//		cv::line(result, pt1, pt2, cv::Scalar(255), 1);

	//	}
	//}
	//cv::imshow("Detected Lines with Hough", result);

	// Creat LineFinder instance
	LineFinder lineFinder;
	// Set probabilistic Hough parameters
	lineFinder.setLineLengthAndGap(100, 20);
	lineFinder.setMinvote(80);
	// Detect lines and draw them
	lineFinder.findLines(contours);
	lineFinder.drawDetectedLines(result, cv::Scalar(0, 0, 255));
	cv::imshow("Detected Lines with HoughP", result);

	cv::waitKey(0);
	return 0;
}