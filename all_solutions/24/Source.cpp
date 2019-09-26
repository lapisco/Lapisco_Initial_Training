#include "opencv\cv.h"
#include "opencv\highgui.h"

using namespace cv;
using namespace std;

Point pt;

void on_Mouse(int event, int x, int y, int d, void *userdata)
{
	pt.x=x;
	pt.y=y;
}

int main()
 {
	 Mat original = imread("gatos.jpg",1);
	 Mat gray; Mat region(original.rows, original.cols, CV_8UC3);

	 int y,x, cont=0;
	 int cont_at=0, cont_fin=1; //Criando o cont atual e final para saber o final da região preenchida

	 cvtColor(original, gray, CV_BGR2GRAY);
	 
	 for(y=0; y<gray.rows; y++)
	 {
		for(x=0; x<gray.cols; x++)
		{
				region.at<Vec3b>(y,x)[0] = 255;
				region.at<Vec3b>(y,x)[1] = 255;
				region.at<Vec3b>(y,x)[2] = 255;
		}
	 }

	imshow("Imagem", gray);
	setMouseCallback("Imagem", on_Mouse, NULL); //função para marcar um ponto ("mesmo nome da janela", função para fazer algo com o mouse, parametro estabelecido)
	waitKey(0);
	x=pt.x; //X recebendo o point x marcado pelo mouse
	y=pt.y; //Y recebendo o point y marcado pelo mouse

	region.at<Vec3b>(y,x)[0] = 0;
	region.at<Vec3b>(y,x)[1] = 0;
	region.at<Vec3b>(y,x)[2] = 0;
	
	imshow("Region",region);
	waitKey(30);
	destroyWindow("Imagem");

	while(cont_at!=cont_fin) //Enquanto for diferente, é pq não preencheu o local ainda
	 {
		 cont_fin=cont_at;
		 cont_at=0;

		for(y=0; y<gray.rows; y++)
		{
			for(x=0; x<gray.cols; x++)
			{
				if((region.at<Vec3b>(y,x)[0]==0) && (region.at<Vec3b>(y,x)[1]==0) && (region.at<Vec3b>(y,x)[2]==0)) //condição para achar o ponto da semente
				{
					//condições para pegar os vizinhos dos pixels

					for(int y2=-1; y2<=1; y2++)
					{
						for(int x2=-1; x2<=1; x2++)
						{
							if(gray.at<uchar>(y+y2,x+x2) > 208)
							{
								region.at<Vec3b>(y+y2,x+x2)[0]=0;
								region.at<Vec3b>(y+y2,x+x2)[1]=0;
								region.at<Vec3b>(y+y2,x+x2)[2]=0;

								cont_at++;
							}
						}
					}
				}
				
			} //FOR INTERNO DA IMAGEM GRAY
		} //FOR EXTERNO DA IMAGEM GRAY

		imshow("Region",region);
		waitKey(30);

	 } //WHILE
	 
	 waitKey(0);
}
