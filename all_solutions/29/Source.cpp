#include "opencv\cv.h"
#include "opencv\highgui.h"

using namespace cv;
using namespace std;

int mat[640][480];
int aux;

int main()
 {
	 Mat imagem = imread("image.jpg",1);	 Mat gray = imagem.clone();

	 cvtColor(imagem, gray, CV_BGR2GRAY);
	 Mat Laplace = gray.clone();

	 for(int y=0; y< Laplace.rows; y++)
	 {
		for(int x=0; x< Laplace.cols; x++)
			mat[x][y] = Laplace.at<uchar>(y,x);
	 }

	 for(int y=1; y< Laplace.rows-1; y++)
	 {
		for(int x=1; x< Laplace.cols-1; x++)
		{
			aux = (-8)*mat[x][y] + mat[x-1][y-1] + mat[x][y-1]+ mat[x+1][y-1] + mat[x-1][y] + mat[x-1][y+1] + mat[x][y+1] + mat[x+1][y+1] + mat[x+1][y];

			if(aux>255)
				aux=255;

			if(aux<0)
				aux=0;

			Laplace.at<uchar>(y,x) = aux;
			aux = 0;
		}
	 }

	vector<Vec3f> circles ; 

	HoughCircles (Laplace, circles, CV_HOUGH_GRADIENT, 3, 15, 200, 100, 5, 50);

	for(int i=0; i<circles.size(); i++ )
	{
		//Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));

	    int radius = cvRound(circles[i][2]);
 
		circle( imagem, Point(circles[i][0],circles[i][1]), 3, Scalar(0,255,0), -1, 8, 0 );
 
		circle( imagem, Point(circles[i][0],circles[i][1]), radius, Scalar(0,0,255), 3, 8, 0 );
	}

	 imshow("Imagem", imagem);
	 imshow("Laplace", Laplace);

	 waitKey(0);
 }
