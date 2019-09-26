#include "opencv\cv.h"
#include "opencv\highgui.h"

using namespace cv;
using namespace std;

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
	 Mat original = imread("formas.jpg",1);
	 Mat region(original.rows,original.cols, CV_8UC1);
	 Mat region_final(original.rows,original.cols,CV_8UC3);

	 int y,x, cont=0, r=0, g=0, b=0;
	 int cont_at=0, cont_fin=1; //Criando o cont atual e final para saber o final da região preenchida

	 cvtColor(original, original, CV_BGR2GRAY);


	 for(y=0; y<original.rows; y++)
	 {
		for(x=0; x<original.cols; x++)
		{
			region.at<uchar>(y,x) = 0;
		
			region_final.at<Vec3b>(y,x)[0]=0;
			region_final.at<Vec3b>(y,x)[1]=0;
			region_final.at<Vec3b>(y,x)[2]=0;
		}
	 }

for(int i=0; i<original.rows; i++)
{
	for(int j=0; j<original.cols; j++)
	{
		if(original.at<uchar>(i,j)==0 && region.at<uchar>(i,j)==0)
		{	
			region.at<uchar>(i,j) = 255;
			colorir(r,g,b,cont);
			cont++;

		cont_fin=1;
		cont_at=0;

		while(cont_at!=cont_fin) //Enquanto for diferente, é pq não preencheu o local ainda
		 {
		 cont_fin=cont_at;

		for(y=0; y<original.rows; y++)
		{
			for(x=0; x<original.cols; x++)
			{
				if(region.at<uchar>(y,x)==255) //condição para achar o ponto da semente
				{
					//condições para pegar os vizinhos dos pixels

					if(original.at<uchar>(y-1,x-1) < 50 && (region.at<uchar>(y-1,x-1)==0))
					{
						region.at<uchar>(y-1,x-1)=255;

						region_final.at<Vec3b>(y-1,x-1)[0]=b;
						region_final.at<Vec3b>(y-1,x-1)[1]=g;
						region_final.at<Vec3b>(y-1,x-1)[2]=r;
						cont_at++;
					}

					if(original.at<uchar>(y-1,x) < 50 && (region.at<uchar>(y-1,x)==0))
					{
						region.at<uchar>(y-1,x)=255;

						region_final.at<Vec3b>(y-1,x)[0]=b;
						region_final.at<Vec3b>(y-1,x)[1]=g;
						region_final.at<Vec3b>(y-1,x)[2]=r;
						cont_at++;
					}

					if(original.at<uchar>(y-1,x+1) < 50 && (region.at<uchar>(y-1,x+1)==0))
					{
						region.at<uchar>(y-1,x+1)=255;

						region_final.at<Vec3b>(y-1,x+1)[0]=b;
						region_final.at<Vec3b>(y-1,x+1)[1]=g;
						region_final.at<Vec3b>(y-1,x+1)[2]=r;
						cont_at++;
					}

					if(original.at<uchar>(y,x-1) < 50 && (region.at<uchar>(y,x-1)==0))
					{
						region.at<uchar>(y,x-1)=255;

						region_final.at<Vec3b>(y,x-1)[0]=b;
						region_final.at<Vec3b>(y,x-1)[1]=g;
						region_final.at<Vec3b>(y,x-1)[2]=r;
						cont_at++;
					}

					if(original.at<uchar>(y,x+1) < 50 && (region.at<uchar>(y,x+1)==0))
					{
						region.at<uchar>(y,x+1)=255;

						region_final.at<Vec3b>(y,x+1)[0]=b;
						region_final.at<Vec3b>(y,x+1)[1]=g;
						region_final.at<Vec3b>(y,x+1)[2]=r;
						cont_at++;
					}

					if(original.at<uchar>(y+1,x-1) < 50 && (region.at<uchar>(y+1,x-1)==0) )
					{
						region.at<uchar>(y+1,x-1)=255;

						region_final.at<Vec3b>(y+1,x-1)[0]=b;
						region_final.at<Vec3b>(y+1,x-1)[1]=g;
						region_final.at<Vec3b>(y+1,x-1)[2]=r;
						cont_at++;
					}

					if(original.at<uchar>(y+1,x) < 50 && (region.at<uchar>(y+1,x)==0) )
					{
						region.at<uchar>(y+1,x)=255;

						region_final.at<Vec3b>(y+1,x)[0]=b;
						region_final.at<Vec3b>(y+1,x)[1]=g;
						region_final.at<Vec3b>(y+1,x)[2]=r;
						cont_at++;
					}

					if(original.at<uchar>(y+1,x+1) < 50 && (region.at<uchar>(y+1,x+1)==0) )
					{
						region.at<uchar>(y+1,x+1)=255;

						region_final.at<Vec3b>(y+1,x+1)[0]=b;
						region_final.at<Vec3b>(y+1,x+1)[1]=g;
						region_final.at<Vec3b>(y+1,x+1)[2]=r;
						cont_at++;
					}
				}

			} //FOR INTERNO DA IMAGEM GRAY
		} //FOR EXTERNO DA IMAGEM GRAY

		imshow("Region",region);
		imshow("Region_final",region_final);
		waitKey(30);

			} //WHILE
		}
	}
}

printf("%d\n",cont);
imshow("Region_final",region_final);

	 waitKey(0);
}
