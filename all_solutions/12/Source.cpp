#include "opencv\cv.h"
#include "opencv\highgui.h"

using namespace cv;
using namespace std;

FILE* arquivo;

int main()
 {
	 arquivo = fopen("saida.xls", "r");

	 //Cria uma imagem com dimensões (x=283,y=283) de 8bits e 1 canal (CV_8UC1)
	 Mat result(283, 283, CV_8UC1); 

	 for(int y=0; y< result.rows; y++)
	 {
		for(int x=0; x<result.cols; x++)
			fscanf(arquivo, "%d", &result.at<uchar>(y,x));
	 }
	 fclose(arquivo);

	 imwrite("Resultado.jpg", result);
	 imshow("Resultado", result);

	 waitKey(0);
 }
