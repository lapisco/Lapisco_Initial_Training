#include "opencv\cv.h"
#include "opencv\highgui.h"
#include <math.h>

using namespace cv;
using namespace std;

int mat[573][325];
long int aux;

Mat Equalizacao(Mat LoadImage)
{
	int mat[573][325];
	int max, min;

	for(int y=0; y<LoadImage.rows; y++)
	{
		for(int x=0; x<LoadImage.cols; x++)
		{
			mat[x][y]= LoadImage.at<uchar>(y,x);
			
			if (x==0 && y==0)
			{
				min = LoadImage.at<uchar>(y,x);
				max = LoadImage.at<uchar>(y,x);
			}

			else
			{
				if(mat[x][y]<min)
					min = LoadImage.at<uchar>(y,x);

				if(mat[x][y]>max)
					max = LoadImage.at<uchar>(y,x);
			}
		}
	}

	Mat ImgEqual = LoadImage.clone();

	for(int y=0; y<LoadImage.rows; y++)
	{
		for(int x=0; x<LoadImage.cols; x++)
			ImgEqual.at<uchar>(y,x) = (LoadImage.at<uchar>(y,x)*255)/(max-min);
	}

	return ImgEqual;
}

int main()
 {
	 Mat imagem = imread("death_note.jpg",1);
	 Mat Laplace(573, 325, CV_8UC1);
	 Mat Equal;

	 cvtColor(imagem, Laplace, CV_BGR2GRAY);
	 imshow("Gray", Laplace);

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

	 Equal = Equalizacao(Laplace);

	 imshow("Laplace", Laplace);
	 imshow("Equalizacao", Equal);
	 imwrite("Laplace.jpg", Laplace);
	 imwrite("Equalizacao.jpg", Equal);

	 waitKey(0);
 }
