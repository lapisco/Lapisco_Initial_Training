#include "opencv\cv.h"
#include "opencv\highgui.h"

using namespace cv;
using namespace std;

int main()
 {
	 Mat imagem = imread("Iron_Man.jpg",1);
	
	 Mat gray;
	 Mat canny;

	 cvtColor(imagem, gray, CV_BGR2GRAY);
	 imshow("CINZA",gray);

	 Canny(gray, canny, 100, 11, 3);
	 imshow("Canny", canny);

	 imwrite("Canny.jpg",canny);

	 waitKey(0);
 }
