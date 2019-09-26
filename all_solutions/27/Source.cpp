#include "opencv\cv.h"
#include "opencv\highgui.h"

using namespace cv;
using namespace std;

FILE* arquivo;
char NameImage[500];

void colorir(int &r, int &g, int &b, int cont)
{
	if (cont==0)
	{
		srand((unsigned)time(NULL)); //gera cores aleatorias

	r+= rand() % 256; //valor aleatório gerado. Obs: %256 para não ultrapassar o valor 255
	g+= rand() % 256;
	b+= rand() % 256;
	}

	else if (cont%2!=0)
	{
		srand((unsigned)time(NULL));

	r+= rand() % 256;
	g+= rand() % 256;
	b+= rand() % 256;
	}

	else if (cont%2==0)
	{
		srand((unsigned)time(NULL));

	r+= rand() % 256;
	g+= rand() % 256;
	b+= rand() % 256;
	}
}

int main()
 {
	 Mat original = imread("imagem.jpg",1);
	 Mat region(original.rows,original.cols, CV_8UC1);
	 Mat region_final(original.rows,original.cols,CV_8UC3);
	 Mat region_final2(original.rows,original.cols,CV_8UC3);

	 int xmax=0, ymax=0, xmin=0, ymin=0, contaux=0;

	 int y,x, cont=0, r=0, g=0, b=0;
	 int cont_at=0, cont_fin=1; //Criando o cont atual e final para saber o final da região preenchida

	 cvtColor(original, original, CV_BGR2GRAY);

	 for(y=0; y<original.rows; y++)
	 {
		for(x=0; x<original.cols; x++)
		{
			region.at<uchar>(y,x) = 0;

			region_final2.at<Vec3b>(y,x)[0]=0;
			region_final2.at<Vec3b>(y,x)[1]=0;
			region_final2.at<Vec3b>(y,x)[2]=0;
		}
	 }

	 imshow("Imagem",original);
	 waitKey(10);

for(int i=0; i<original.rows; i++)
{
	for(int j=0; j<original.cols; j++)
	{
		if(original.at<uchar>(i,j)==0 && region.at<uchar>(i,j)==0)
		{	
			cont++;
			region.at<uchar>(i,j) = cont;
	
		cont_fin=1;
		cont_at=0;

		while(cont_at!=cont_fin) //Enquanto for diferente, é pq não preencheu o local ainda
		 {
		 cont_fin=cont_at;

		for(y=0; y<original.rows; y++)
		{
			for(x=0; x<original.cols; x++)
			{
				if(region.at<uchar>(y,x)==cont) //condição para achar o ponto da semente
				{
					//condições para pegar os vizinhos dos pixels

					if(original.at<uchar>(y-1,x-1) < 127 && (region.at<uchar>(y-1,x-1)!=cont))
					{
						region.at<uchar>(y-1,x-1)=cont;
						cont_at++;
					}

					if(original.at<uchar>(y-1,x) < 127 && (region.at<uchar>(y-1,x)!=cont))
					{
						region.at<uchar>(y-1,x)=cont;
						cont_at++;
					}

					if(original.at<uchar>(y-1,x+1) < 127 && (region.at<uchar>(y-1,x+1)!=cont))
					{
						region.at<uchar>(y-1,x+1)=cont;
						cont_at++;
					}

					if(original.at<uchar>(y,x-1) < 127 && (region.at<uchar>(y,x-1)!=cont))
					{
						region.at<uchar>(y,x-1)=cont;
						cont_at++;
					}

					if(original.at<uchar>(y,x+1) < 127 && (region.at<uchar>(y,x+1)!=cont))
					{
						region.at<uchar>(y,x+1)=cont;
						cont_at++;
					}

					if(original.at<uchar>(y+1,x-1) < 127 && (region.at<uchar>(y+1,x-1)==0) )
					{
						region.at<uchar>(y+1,x-1)=cont;
						cont_at++;
					}

					if(original.at<uchar>(y+1,x) < 127 && (region.at<uchar>(y+1,x)!=cont) )
					{
						region.at<uchar>(y+1,x)=cont;
						cont_at++;
					}

					if(original.at<uchar>(y+1,x+1) < 127 && (region.at<uchar>(y+1,x+1)!=cont) )
					{
						region.at<uchar>(y+1,x+1)=cont;
						cont_at++;
					}
				}

			} //FOR INTERNO DA IMAGEM GRAY
		} //FOR EXTERNO DA IMAGEM GRAY
	} //WHILE

		
	for(int aux=cont; aux<=cont; aux++)
	{
		colorir(r,g,b,cont);

		for(y=0; y<region.rows; y++)
		{
			for(x=0; x<region.cols; x++)
			{
				if(region.at<uchar>(y,x)==cont)
				{
					contaux++;

					region_final.at<Vec3b>(y,x)[0]=b;
					region_final.at<Vec3b>(y,x)[1]=g;
					region_final.at<Vec3b>(y,x)[2]=r;

					region_final2.at<Vec3b>(y,x)[0]=b;
					region_final2.at<Vec3b>(y,x)[1]=g;
					region_final2.at<Vec3b>(y,x)[2]=r;

					if(contaux==1)
					{
						xmin=x;
						ymin=y;
						xmax=x;
						ymax=y;
					}

					else
					{
						if(x<xmin)
							xmin=x;
								
						if(y<ymin)
							ymin=y;

						if(xmax<x) 
							xmax=x;
							
						if(ymax<y) 
							ymax=y;
					}
				}	
			}
		}

		for(y=0; y<region.rows; y++)
		{
			for(x=0; x<region.cols; x++)
			{
				if(region.at<uchar>(y,x)!=cont)
				{
					region_final.at<Vec3b>(y,x)[0]=0;
					region_final.at<Vec3b>(y,x)[1]=0;
					region_final.at<Vec3b>(y,x)[2]=0;
				}
			}
		}

		Rect region=  Rect(xmin, ymin, xmax-xmin, ymax-ymin); 
		Mat image = region_final(region);

		sprintf(NameImage, "image%d", aux);
		imshow(NameImage, image);
		waitKey(50);

		printf("width=%d   height=%d   Xmin=%d   Ymin=%d\n",xmax-xmin, ymax-ymin ,xmin, ymin);

		contaux=0; xmax=0;	xmin=0; ymax=0; ymin=0;

	} //AUX - PARA CRIAR JANELAS

		}
	}
}

printf("%d\n",cont);
imshow("Region_final",region_final2);

	 waitKey(0);
}