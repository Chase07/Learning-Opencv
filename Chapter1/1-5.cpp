#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<iostream>

using namespace::std;
using namespace::cv;

int main()
{
	/*创建并显示一个图像*/
	Mat image;//创建了一个宽高都为0的图像
	//image.size()返回一个结构体，包含成员height和width
	cout << "size:" << image.size().height << "," << image.size().width << endl;
	image = imread("Cute dog.png");
	//if (!image.data)//image.data是一个指针，可以转换为bool值
	//{
	//	cout << "No such an image!" << endl;
	//}
	//namedWindow("Original Image");//define a window
	//imshow("Original Image", image);//show the image
	//waitKey(1000);
	
	/////////////////////////////////////////////////
	
	/*将图像反转*/
	cv::Mat result;//用了保存反转后的图像
	flip(image, result, 1);//1表示水平反转，0表示垂直反转，negative表示两者皆有
	//cv::namedWindow("Result Image");//define an other window
	//cv::imshow("Result Image", result);
	//cv::waitKey(0);
	//cv::imwrite("flipped cute dog.png", result);

	/////////////////////////////////////////////////
	
	/*验证shallow copy 和 deep copy*/
	Mat image2, image3;
	image2 = result;
	result.copyTo(image3);//Deep copy result to image3
	namedWindow("Original image2");
	imshow("Original image2", image2);//展示原始的image2
	waitKey(0);
	flip(result, result, 1);//将result反转至result
	namedWindow("Current image2");
	imshow("Current image2", image2);//展示现在的image2
	waitKey(0);
	namedWindow("image3");
	imshow("image3", image3);//展示image3
	waitKey(0);

	//////////////////////////////////////////////////

	cv::Mat gray = function();
}

cv::Mat function()
{
	cv::Mat ima(240, 320, CV_8U, cv::Scalar(100));
	return ima;
}