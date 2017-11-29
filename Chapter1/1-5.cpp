#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<iostream>

using namespace::std;
using namespace::cv;

int main()
{
	/*��������ʾһ��ͼ��*/
	Mat image;//������һ����߶�Ϊ0��ͼ��
	//image.size()����һ���ṹ�壬������Աheight��width
	cout << "size:" << image.size().height << "," << image.size().width << endl;
	image = imread("Cute dog.png");
	//if (!image.data)//image.data��һ��ָ�룬����ת��Ϊboolֵ
	//{
	//	cout << "No such an image!" << endl;
	//}
	//namedWindow("Original Image");//define a window
	//imshow("Original Image", image);//show the image
	//waitKey(1000);
	
	/////////////////////////////////////////////////
	
	/*��ͼ��ת*/
	cv::Mat result;//���˱��淴ת���ͼ��
	flip(image, result, 1);//1��ʾˮƽ��ת��0��ʾ��ֱ��ת��negative��ʾ���߽���
	//cv::namedWindow("Result Image");//define an other window
	//cv::imshow("Result Image", result);
	//cv::waitKey(0);
	//cv::imwrite("flipped cute dog.png", result);

	/////////////////////////////////////////////////
	
	/*��֤shallow copy �� deep copy*/
	Mat image2, image3;
	image2 = result;
	result.copyTo(image3);//Deep copy result to image3
	namedWindow("Original image2");
	imshow("Original image2", image2);//չʾԭʼ��image2
	waitKey(0);
	flip(result, result, 1);//��result��ת��result
	namedWindow("Current image2");
	imshow("Current image2", image2);//չʾ���ڵ�image2
	waitKey(0);
	namedWindow("image3");
	imshow("image3", image3);//չʾimage3
	waitKey(0);

	//////////////////////////////////////////////////

	cv::Mat gray = function();
}

cv::Mat function()
{
	cv::Mat ima(240, 320, CV_8U, cv::Scalar(100));
	return ima;
}