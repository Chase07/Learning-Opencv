#include"5.4.h"

using namespace std;
using namespace cv;

int main()
{
	// Creat the morphological features instance
	MorphoFeatures morpho;
	morpho.setThreshold(40);

	// Reading an image
	Mat image(imread("../../images/building.jpg", IMREAD_GRAYSCALE));
	imshow("Original Image", image);

	// Get the edges
	Mat edges;
	edges = morpho.getEdges(image);
	bitwise_not(edges, edges, Mat());// NOT
	imshow("Edges", edges);

	// Get the corners
	Mat corners;
	corners = morpho.getCorners(image);
	bitwise_not(corners, corners, Mat());// NOT
	morpho.drawOnImage(corners, image);
	imshow("Corners on Original Image", image);
	waitKey(0);
	return 0;
}