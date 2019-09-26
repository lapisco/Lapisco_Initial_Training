#include "opencv\cv.h"
#include "opencv\highgui.h"

using namespace cv;
using namespace std;

int main()
 {
	 Mat imagem = imread("Iron_Man.jpg",1);
	 
	 Mat gray;
	 Mat redimMin;
	 Mat redimMax;

	 cvtColor(imagem, gray, CV_BGR2GRAY);
	 imshow("GRAY", gray);

	 resize(gray, redimMin, Size(160,120));
	 imshow("Pequena", redimMin);

	 resize(gray, redimMax, Size(640,480));
	 imshow("Grande",redimMax);

	 imwrite("Redim_Menor.jpg", redimMin);
	 imwrite("Redim_Maior.jpg", redimMax);

	 waitKey(0);
 }
