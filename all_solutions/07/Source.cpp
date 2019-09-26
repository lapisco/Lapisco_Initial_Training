#include "opencv\cv.h"
#include "opencv\highgui.h"

using namespace cv;
using namespace std;

int main()
 {
	 Mat imagem = imread("Iron_Man.jpg",1);
	 
	 Mat gray;
	 Mat limiar;

	 cvtColor(imagem, gray, CV_BGR2GRAY);
	 imshow("CINZA", gray);

	 threshold(gray, limiar, 120, 255, CV_THRESH_BINARY);
	 imshow("LIMIAR", limiar);
	 imwrite("Limiar.jpg", limiar);

	 waitKey(0);
 }
