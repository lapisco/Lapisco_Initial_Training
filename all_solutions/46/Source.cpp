#include "opencv\cv.h"
#include "opencv\highgui.h"

using namespace cv;
using namespace std;

void moments_estatisticos(Mat image)
{
	vector<vector<Point>> contours; //cria um vetor de pontos

	findContours(image, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	FILE* arquivo;
	arquivo = fopen("Estatisticos.txt", "w");

	 vector<vector<Point>>::const_iterator itc= contours.begin();

	 while(itc!=contours.end())
	 {
		 Moments mom = moments(Mat(*itc++));
		 double stat[10];

		 stat[0] = mom.m00;
		 stat[1] = mom.m01;
		 stat[2] = mom.m02;
		 stat[3] = mom.m03;
		 stat[4] = mom.m10;
		 stat[5] = mom.m11;
	     stat[6] = mom.m12;
		 stat[7] = mom.m20;
		 stat[8] = mom.m21;
		 stat[9] = mom.m30;

		for(int i=0; i<10; i++)
			fprintf(arquivo, "%f, ", stat[i]);

		fprintf(arquivo, "0\n");
	 }
	 fclose(arquivo);
}

int main()
{
	 Mat imagem = imread("object.jpg",1);
	 Mat gray; Mat image_final; Mat contornos;

	 cvtColor(imagem, gray, CV_BGR2GRAY);
	 Canny(gray, gray, 127, 255 , 3);

	 Laplacian( gray, contornos, CV_8UC1, 3);
	 threshold(contornos, image_final, 127, 255, CV_THRESH_BINARY);

	 moments_estatisticos(image_final);

	// imshow("Image_Final", image_final);

	 waitKey(0);
}
