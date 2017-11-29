#include<opencv2\opencv.hpp>

using namespace::std;

int main()
{
	cv::Mat grayScaleImage(imread("../../images/road.jpg", cv::IMREAD_GRAYSCALE));
	cv::imshow("Gray Scale Image", grayScaleImage);
	// Apply Canny algorithm
	cv::Mat contours;// Output contours
	cv::Canny(grayScaleImage, contours,
		125, // Low threshold
		350);// High threshold
	cv::imshow("Contours Image", contours);
	cv::Mat contoursInv;// Inverted image
	cv::threshold(contours, contoursInv, 
		128,// Values below this 
		255,// become it
		cv::THRESH_BINARY_INV);
	cv::imshow("Contours Inverted Image", contoursInv);

	cv::waitKey(0);
	return 0;
}
