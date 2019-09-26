#include "opencv\cv.h"
#include "opencv\highgui.h"
#include <math.h>

using namespace cv;
using namespace std;

int mat[283][283];
long int dx, dy;

int main()
 {
	 Mat imagem = imread("Iron_Man.jpg",1);
	 Mat gray;
	 Mat Sobel(imagem.rows, imagem.cols, CV_8UC1);

	 cvtColor(imagem, Sobel, CV_BGR2GRAY);
	 imshow("Gray", Sobel);
	 imwrite("Gray.jpg", Sobel);

	 for(int y=0; y< Sobel.rows; y++)
	 {
		for(int x=0; x< Sobel.cols; x++)
			mat[x][y] = Sobel.at<uchar>(y,x);
	 }

	 for(int y=1; y< Sobel.rows-1; y++)
	 {
		for(int x=1; x< Sobel.cols-1; x++)
		{
			dx = (1)*mat[x-1][y-1] + (2)*mat[x][y-1] + (1)*mat[x+1][y-1] + (-1)*mat[x-1][y+1] + (-2)*mat[x][y+1] + (-1)*mat[x+1][y+1]; 
			dy = (1)*mat[x-1][y-1] + (-1)*mat[x+1][y-1] + (2)*mat[x-1][y] + (-2)*mat[x+1][y] + (1)*mat[x-1][y+1] + (-1)*mat[x+1][y+1];
			
			Sobel.at<uchar>(y,x) = (int)sqrt(pow(dx,2)+ pow(dy,2));
		}
	 }

	 imshow("Sobel", Sobel);
	 imwrite("Sobel.jpg", Sobel);

	 waitKey(0);
 }
