#include "opencv\cv.h"
#include "opencv\highgui.h"

using namespace cv;
using namespace std;

int main()
 {
	 Mat original = imread("circulo.jpg",1);
	 Mat gray; Mat region(original.rows, original.cols, CV_8UC1);
	 int y,x;

	 int cont_at=0, cont_fin=1; //Criando o cont atual e final para saber o final da região preenchida

	 cvtColor(original, gray, CV_BGR2GRAY);
	 
	 for(y=0; y<gray.rows; y++)
	 {
		for(x=0; x<gray.cols; x++)
		{
			if(x==160 && y==180) //Colocando a semente nessas coordenadas
				region.at<uchar>(y,x) = 255;
			else
				region.at<uchar>(y,x) = 0;
		}
	 }
	 
	imshow("Circulo", gray);
	
	while(cont_at!=cont_fin) //Enquanto for diferente, é pq não preencheu o local ainda
	 {
		 cont_fin=cont_at;
		 cont_at=0;

		for(y=0; y<gray.rows; y++)
		{
			for(x=0; x<gray.cols; x++)
			{
				
				if(region.at<uchar>(y,x)==255) //condição para achar o ponto da semente
				{
					//Mascara para pegar os vizinhos dos pixels
					for(int y2=-1; y2<=1; y2++)
					{
						for(int x2=-1; x2<=1; x2++)
						{
							if(gray.at<uchar>(y+y2,x+x2) < 127)
							{
								region.at<uchar>(y+y2,x+x2)=255;
								cont_at++;
							}
						}
					}
				} //IF DA SEMENTE
				
			} //FOR INTERNO DA IMAGEM GRAY
		} //FOR EXTERNO DA IMAGEM GRAY

		imshow("Region",region);
		waitKey(30);

	 } //WHILE

	 waitKey(0);
}
