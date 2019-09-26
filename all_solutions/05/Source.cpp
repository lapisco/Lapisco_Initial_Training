#include "opencv\cv.h"
#include "opencv\highgui.h"

using namespace cv;
using namespace std;

int main()
 {
	 Mat imagem = imread("Iron_Man.jpg",1);

	 Mat gray;
	 Mat median;
	 Mat gaussian;

	 cvtColor(imagem, gray, CV_BGR2GRAY);
	 imshow("CINZA",gray);

	 medianBlur(gray, median, 5);
	 imshow("MEDIAN",median);

	 GaussianBlur(gray, gaussian, Size(5,5), 0);
	 imshow("GAUSSIAN", gaussian);

	 imwrite("Median_Blur.jpg", median);
	 imwrite("Gaussian_Blur.jpg",gaussian);

	 waitKey(0);
 }
