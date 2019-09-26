#include "opencv\cv.h"
#include "opencv\highgui.h"
#include <math.h>

using namespace cv;
using namespace std;

Mat histograma(Mat imagem)
{
	int x,y;
	int vec[256];
	int aux=0;
	
	for(x=0;x<256;x++)
	{
		vec[x]=0;
	}

	for(y=0;y<imagem.rows;y++)
	{
		for(x=0;x<imagem.cols;x++)
		{
			aux++;
			vec[imagem.at<uchar>(y,x)]++;
		}
	}
	
	for(x=0;x<256;x++)
	{
		vec[x]=((2000*vec[x])/aux);
	}

	Mat hist(100,256,CV_8UC1);

	for(y=0;y<hist.rows;y++)
	{
		for(x=0;x<hist.cols;x++)
		{
			if(y>=hist.rows-vec[x])
				hist.at<uchar>(y,x)=0;

			else
				hist.at<uchar>(y,x)=255;
		}
	}
	return hist;
}

int mat[573][325];
int dx, dy;

int main()
 {
	 Mat imagem = imread("death_note.jpg",1);
	 Mat gray; Mat hist_gray; Mat hist_Sobel;

	 cvtColor(imagem, gray, CV_BGR2GRAY);
	 imshow("Gray", gray);
	 imwrite("Img_gray.jpg",gray);

	 Mat Sobel = gray.clone();

	 for(int y=0; y< gray.rows; y++)
	 {
		for(int x=0; x< gray.cols; x++)
			mat[x][y] = gray.at<uchar>(y,x);
	 }

	 //Aplicando operador gradiente Sobel

	 for(int y=0; y< gray.rows; y++)
	 {
		for(int x=0; x< gray.cols; x++)
		{
			if(y==0 || x==0 || y==gray.rows-1 || x==gray.cols-1)
				Sobel.at<uchar>(y,x) = 0;

			else
			{
				dx = (1)*mat[x-1][y-1] + (2)*mat[x][y-1] + (1)*mat[x+1][y-1] + (-1)*mat[x-1][y+1] + (-2)*mat[x][y+1] + (-1)*mat[x+1][y+1]; 
				dy = (1)*mat[x-1][y-1] + (-1)*mat[x+1][y-1] + (2)*mat[x-1][y] + (-2)*mat[x+1][y] + (1)*mat[x-1][y+1] + (-1)*mat[x+1][y+1];
			
				Sobel.at<uchar>(y,x) = (int)sqrt(pow(dx,2)+ pow(dy,2));
			}
		}
	 }

	 imshow("Sobel", Sobel);
	 imwrite("Sobel.jpg", Sobel);

	 hist_gray = histograma(gray);

	 hist_Sobel = histograma(Sobel);

	 imshow("Hist_gray",hist_gray);
	 imwrite("Hist_gray.jpg",hist_gray);

	 imshow("Hist_Sobel",hist_Sobel);
	 imwrite("Hist_Sobel.jpg",hist_Sobel);

	 waitKey(0);
 }
