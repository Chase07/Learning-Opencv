#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/core/core.hpp>

using namespace::std;
using namespace::cv;

int main()
{
	VideoCapture capture("Megamind.avi");//Opencv the video file
	if (!capture.isOpened()) { return 1; }//Cheak if it was opened

	double rate = capture.get(CV_CAP_PROP_FPS);//Get the rate of frame
	double position = 200.0;//Jump to the 200th frame
	capture.set(CV_CAP_PROP_POS_FRAMES, position);
	bool stop(false);
	Mat frame;//Be Used to save current frame(image)
	namedWindow("Extracted Frame");

	int delay = static_cast<int>(1000 / rate);//The delay among each frame£¬keeping step with the orginal video
	while (!stop)//Traving each frame
	{
		if (!capture.read(frame)) { break; }//Read every frames, breaking if it was failed 
		imshow("Extracted Frame", frame);
		if (waitKey(delay) < 255) { waitKey(0); }
	}

	return 0;
}