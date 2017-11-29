#ifndef _7_3_H
#define _7_3_H

#define _USE_MATH_DEFINES
#include <math.h>
#include<opencv2\opencv.hpp>

class LineFinder
{
private:
	// Original image
	cv::Mat img;
	// Vector containing the end points of the detected lines
	std::vector<cv::Vec4i> lines;
	// The resolusion parameters of accumulator 
	double deltaRho;
	double deltaTheta;
	// Minimum number of votes that a line must receive before being considered
	int minVote;
	// Minimum length for a line
	double minLength;
	// Maximum allowed gap along the line
	double maxGap;

public:
	// Default accumulator resolution is 1 pixel by 1 degree, no minimum gap and length
	LineFinder() :deltaRho(1), deltaTheta(M_PI / 180), minVote(10), minLength(0.), maxGap(0.) {};
	// Set the resolution of the accmulator
	void setAccmulator(double dRho, double dTheta)
	{
		this->deltaRho = dRho;
		this->deltaTheta = dTheta;
	}
	// Set the minimum number of votes
	void setMinvote(int minv)
	{
		this->minVote = minv;
	}
	// Set the line length and gap
	void setLineLengthAndGap(double length, double gap)
	{
		this->minLength = length;
		this->maxGap = gap;
	}

	// Apply probabilistic Hough Transform
	std::vector<cv::Vec4i> findLines(cv::Mat &binary)
	{
		this->lines.clear();
		cv::HoughLinesP(binary, lines, deltaRho, deltaTheta, minVote, minLength, maxGap);

		return this->lines;      
	}
	// Draw the detected lines on image
	void drawDetectedLines(cv::Mat &image, cv::Scalar color = cv::Scalar(255, 255, 255))
	{
		std::vector<cv::Vec4i>::const_iterator cur = lines.begin();
		for (; cur != lines.end(); ++cur)
		{
			cv::Point pt1((*cur)[0], (*cur)[1]);
			cv::Point pt2((*cur)[2], (*cur)[3]);
			cv::line(image, pt1, pt2, color, 1);
		}
	}

};


#endif // !_7_3_H


