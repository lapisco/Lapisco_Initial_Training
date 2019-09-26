#include "opencv\cv.h"
#include "opencv\highgui.h"

using namespace cv;
using namespace std;

void moments_HU(Mat image)
{
	vector<vector<Point>> contours; //cria um vetor de pontos

	findContours(image, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	FILE* arquivo;
	arquivo = fopen("HuMoments.txt", "w");

	 vector<vector<Point>>::const_iterator itc= contours.begin();

	 while(itc!=contours.end())
	 {
		 double Hu[7];

		 Moments mom = moments(Mat(*itc++));
		 HuMoments(mom, Hu);

		 Hu[0] = mom.nu02;
		 Hu[1] = mom.nu03;
		 Hu[2] = mom.nu11;
		 Hu[3] = mom.nu12;
		 Hu[4] = mom.nu20;
		 Hu[5] = mom.nu21;
	     Hu[6] = mom.nu30;

		for(int i=0; i<7; i++)
			fprintf(arquivo, "%f, ", Hu[i]);

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

	 moments_HU(image_final);

	// imshow("Image_Final", image_final);

	 waitKey(0);
}
