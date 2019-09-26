#include "opencv\cv.h"
#include "opencv\highgui.h"

using namespace cv;
using namespace std;

void moments_centrais(Mat image)
{
	vector<vector<Point>> contours; //cria um vetor de pontos

	findContours(image, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	FILE* arquivo;
	arquivo = fopen("Centrais.txt", "w");

	 vector<vector<Point>>::const_iterator itc= contours.begin();

	 while(itc!=contours.end())
	 {
		 Moments mom = moments(Mat(*itc++));
		 double central[7];

		 central[0] = mom.mu20;
		 central[1] = mom.mu11;
		 central[2] = mom.mu02;
		 central[3] = mom.mu30;
		 central[4] = mom.mu21;
	     central[5] = mom.mu12;
		 central[6] = mom.mu03;

		for(int i=0; i<7; i++)
			fprintf(arquivo, "%f, ", central[i]);

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

	 moments_centrais(image_final);

	// imshow("Image_Final", image_final);

	 waitKey(0);
}
