#ifndef _6_5_H
#define _6_5_H
#include<opencv2\opencv.hpp>

class LaplacianZC
{
private:
	// Original image
	cv::Mat image;
	// 32-bit float image containing the Laplacian
	cv::Mat laplace;
	// Aperture size of the laplacian kernel
	int aperture;

public:
	LaplacianZC() :aperture(3) {}
	// Set the aperture size of kernel
	void setAperture(int aperture) { this->aperture = aperture; }
	// Compute the floating point Laplacian
	cv::Mat computeLaplacian(const cv::Mat& image) 
	{
		// Compute Laplacian 
		cv::Laplacian(image, laplace, CV_32F, aperture);
		// Keep local copy of the image(used for zero-crossings)
		this->image = image.clone();
		return laplace;
	}

	// Return the Laplacian result in 8-bit image
	// Zreo corresponds to gray level 128
	// if no scale is provided, then the max value will be scaled to intensity 255  
	// Must call computeLaplacian before calling this:
	cv::Mat getLaplacianImage(double scale = -1.0)
	{
		if (scale < 0)
		{
			double lapMin, lapMax;
			cv::minMaxLoc(laplace, &lapMin, &lapMax);
			scale = 127 / std::max(-lapMin, lapMax);
		}
		cv::Mat laplaceImage;
		laplace.convertTo(laplaceImage, CV_8U, scale, 128);
		return laplaceImage;

	}

	// Get a binary image of zero-crossing 
	// if the product of the two adjascent pixels is less than threshold
	// then this zero-crossing will be ignored
	cv::Mat getZeroCrossings(float threshold = 1.0)
	{
		// Creat the iterators
		cv::Mat_<float>::const_iterator cur = laplace.begin<float>() + laplace.step1();
		cv::Mat_<float>::const_iterator end = laplace.end<float>();
		cv::Mat_<float>::const_iterator up = laplace.begin<float>();
		
		// Binary image initialize to white
		cv::Mat binary(laplace.size(), CV_8U, cv::Scalar(255));
		cv::Mat_<uchar>::iterator out = binary.begin<uchar>() + binary.step1();

		// Negate the input threshold value
		threshold *= -1.0;
		for (; cur != end; ++cur, ++up, ++out)
		{
			// If the product of two adjascent pixels is nagative,
			// then there is a sign change
			if ((*cur) * (*(cur - 1)) < threshold)
			{
				*out = 0;
			}
			else if ((*cur) * (*(up - 1)) < threshold)
			{
				*out = 0;
			}	
		}
		return binary;
	}

};

#endif // _6_5_H