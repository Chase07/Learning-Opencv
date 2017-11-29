#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<iostream>

using namespace::std;
using namespace::cv;

int main()
{
	Mat image1, image2, image3;
	image1 = imread("Cute dog.png");
	image2 = image1;//进行赋值；
	flip(image2, image2, 1);//将image2反转到image2
	/*展示image1*/
	namedWindow("image1");
	imshow("image1", image1);
	waitKey(4000);//展示4秒
	/*以上说明赋值为浅拷贝*/

	return 0;
}