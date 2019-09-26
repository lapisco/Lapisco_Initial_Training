#include "opencv\cv.h"
#include "opencv\highgui.h"

using namespace cv;
using namespace std;

int main()
 {
	 Mat imagem = imread("Iron_Man.jpg",1);
	 Mat saida;

	 cvtColor(imagem, saida, CV_BGR2HSV);
	 imshow("HSV",saida);

	 vector<Mat> hsv_planes(3);
	 split(saida, hsv_planes );
	 imshow("H", hsv_planes[0]);
	 imshow("S", hsv_planes[1]);
	 imshow("V", hsv_planes[2]);

	 imwrite("H.jpg", hsv_planes[0]);
	 imwrite("S.jpg", hsv_planes[1]);
	 imwrite("V.jpg", hsv_planes[2]);

	 waitKey(0);
 }
