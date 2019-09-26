#include "opencv\cv.h"
#include "opencv\highgui.h"

using namespace cv;
using namespace std;

FILE* arquivo;

int main()
 {
	 arquivo = fopen("saida.xls", "w");

	 Mat imagem = imread("Iron_Man.jpg",1);
	 Mat gray;

	 cvtColor(imagem, gray, CV_BGR2GRAY);

	 for(int y=0; y< gray.rows; y++)
	 {
		for(int x=0; x<gray.cols; x++)
		{
			if(gray.at<uchar>(y,x) > 120)
				gray.at<uchar>(y,x)=255;
			else
				gray.at<uchar>(y,x)=0;

			fprintf(arquivo, "%d\t", gray.at<uchar>(y,x));
		}
		fprintf(arquivo, "\n");
	 }

	 fclose(arquivo);

	 waitKey(0);
 }
