#include "opencv\cv.h"
#include "opencv\highgui.h"

using namespace cv;
using namespace std;

int main()
 {
	 while(1)
	 {
		 Mat frame;

		 VideoCapture capture(0); //abrir a câmera padrão

		 capture >> frame; //Obter um novo frame

		 cvtColor(frame, frame, CV_BGR2GRAY);
		 imshow("Frame_Gray",frame);
		 	
		 Canny(frame, frame, 30, 30, 3);
		 imshow("Frame_Canny",frame);

		 waitKey(1000);
	 }
 }
