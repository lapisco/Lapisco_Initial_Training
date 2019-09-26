#include "opencv\cv.h"
#include "opencv\highgui.h"

using namespace cv;
using namespace std;

int xc=0, yc=0, cont=0;

int main()
 {
	 Mat imagem = imread("quadrado.jpg",1);
	 Mat gray;

	 cvtColor(imagem, gray, CV_BGR2GRAY);
	 imshow("GRAY", imagem);

	 for(int y=0; y< gray.rows; y++)
	 {
		for(int x=0; x<gray.cols; x++)
		{
			if(gray.at<uchar>(y,x)==0)
			 {
				xc=xc+x;
				yc=yc+y;
				cont++;
			 }
		}
	 }

	 xc=xc/cont;
	 yc=yc/cont;

	 for(int y=0; y< gray.rows; y++)
	 {
		for(int x=0; x<gray.cols; x++)
		{
			if(x==xc && y==yc)
			{
				circle(gray, Point(xc, yc), 1, Scalar(255,255,255),1,8,0);
				gray.at<uchar>(y,x) = 255;
			}
		}
	 }

	 imshow("Centro", gray);
	 imwrite("Center_Point.jpg", gray);

	 waitKey(0);
 }
