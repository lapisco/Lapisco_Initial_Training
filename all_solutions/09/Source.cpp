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
/*OBS: Para imagens com apenas um canal (tons de cinza), usa-se <uchar>
			Ex= nome.at<uchar>(y,x)

	   Já para imagens com 3 canais, usa a nomenclatura <Vec3b>    
			Ex= nome.at<Vec3b>(y,x)[canal]							*/
					
			fprintf(arquivo, "%d\t", gray.at<uchar>(y,x));
		}
		fprintf(arquivo, "\n");
	 }

	 fclose(arquivo);

	 waitKey(0);
 }
