#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<iostream>

using namespace::std;
using namespace::cv;

int main()
{
	Mat image1, image2, image3;
	image1 = imread("Cute dog.png");
	image2 = image1;//���и�ֵ��
	flip(image2, image2, 1);//��image2��ת��image2
	/*չʾimage1*/
	namedWindow("image1");
	imshow("image1", image1);
	waitKey(4000);//չʾ4��
	/*����˵����ֵΪǳ����*/

	return 0;
}