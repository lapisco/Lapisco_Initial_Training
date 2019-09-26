#include "opencv\cv.h"
#include "opencv\highgui.h"

using namespace cv;
using namespace std;

int main()
 {
	 Mat imagem = imread("Iron_Man.jpg",1);
	 Mat gray;

	 cvtColor(imagem, gray, CV_BGR2GRAY);

	 imshow("Iron_Man", imagem);
	 imshow("Iron_Man_GRAY", gray);

	 imwrite("Iron_Man_GRAY.jpg", gray);

	 waitKey(0);
 }
