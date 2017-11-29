#include"6.5.h"

int main()
{
	cv::Mat image(cv::imread("../../images/boldt.jpg", cv::IMREAD_GRAYSCALE));
	cv::Mat_<float>::const_iterator it = image.begin<float>();
	//LaplacianZC laplacian;
	//// Set the size of aperture
	//laplacian.setAperture(7);
	//cv::Mat flap = laplacian.computeLaplacian(image);
	//cv::Mat laplace = laplacian.getLaplacianImage();
	//cv::imshow("Laplacian Image(7*7)", laplace);

	//// 
	//cv::Mat zeroCrossing = laplacian.getZeroCrossings();
	//cv::imshow("Zero-Crossing Image", zeroCrossing);
	//cvWaitKey(0);
	return 0;
}