#include "opencv\cv.h"
#include "opencv\highgui.h"
#include <math.h>
#include <Windows.h>

using namespace cv;

char name[500];

void contagem(int &rows, int &cols,char*endereco)
{
	 FILE*arquivo;
	 arquivo = fopen(endereco, "r");
	 float aux;

	 while(!feof(arquivo))
	 {
		fgets(name, 500 ,arquivo);
		rows++;
	 }

	 fclose(arquivo);

	 arquivo = fopen(endereco, "r");
	 while(!feof(arquivo))
	 {
		fscanf(arquivo, "%f,", &aux);
		cols++;
	 }
	 
	 cols= cols/rows;

	 rows=rows-1;

	 fclose(arquivo);
}

void mat_Principal(Mat &atributos,Mat &label, int lin, int col,char*endereco)
{
	FILE*arquivo;
	arquivo = fopen(endereco, "r");

	for(int y=0; y<lin; y++)
	{
		for(int x=0; x<=col; x++)
		{
			if(x==col)
				fscanf(arquivo, "%f,", &label.at<float>(y,0));

			else
				fscanf(arquivo, "%f,", &atributos.at<float>(y,x));
		}
	}
	fclose(arquivo);
}

void normalizar(Mat &atributos)
{
	float *VetMin = new float[atributos.cols-1];
	float *VetMax = new float[atributos.cols-1];

	for(int x=0; x<atributos.cols; x++)
	{
		for(int y=0; y<atributos.rows; y++)
		{
			if(y==0)
			{
				VetMin[x] = atributos.at<float>(y,x);
				VetMax[x] = atributos.at<float>(y,x);
			}

			else
			{
				if(VetMin[x]>atributos.at<float>(y,x))
				{
					VetMin[x] = atributos.at<float>(y,x);
				}

				if(VetMax[x]<atributos.at<float>(y,x))
				{
					VetMax[x] = atributos.at<float>(y,x);
				}
			}
		}
	}
	//Normalizando os atributos
	for(int y=0; y<atributos.rows; y++)
	{
		for(int x=0; x<atributos.cols; x++)
			atributos.at<float>(y,x) = ((atributos.at<float>(y,x)-VetMin[x])/(VetMax[x]-VetMin[x]));
	}
}

int maxLabel(Mat label)
{
	float cont;

	for(int y=0; y<label.rows; y++)
	{
		if(y==0)
			cont=label.at<float>(y,0);

		else
		{
			if(label.at<float>(y,0)>cont)
				cont=label.at<float>(y,0);
		}
	}
	return (int)(cont+1);
}

void Leave_One_Out(Mat atributos, Mat label, Mat &treino, Mat &labelTreino, Mat &teste, Mat &labelTeste, float porcentagem)
{
	int start, end, temp_mili;
	start=(int)GetTickCount();

	int contLabel;
	contLabel = maxLabel(label); //Função para achar o numero de labels

	int *vetAux = new int[contLabel];
	int *vetTotal = new int[contLabel];

	for(int x=0; x<contLabel; x++)
	{
		vetAux[x]=0;
		vetTotal[x]=0;
	}

	for(int y=0; y<label.rows; y++)
	{
		for(int x=0; x<contLabel; x++) //For para saber quantos labels se repete
		{
			if(label.at<float>(y,0)==x)
				vetTotal[x]++;
		}
	}

	int LinTreino=0, LinTeste=0;

	for(int j=0; j<contLabel; j++)
	{
		vetAux[j]= (int)(vetTotal[j]*porcentagem/100); //porcentagem para cada label

		LinTreino+=vetAux[j];
		LinTeste+=(vetTotal[j]-vetAux[j]);
	}

	 treino = Mat(LinTreino, atributos.cols, CV_32FC1);
	 labelTreino = Mat(LinTreino, 1, CV_32FC1);
	 
	 teste = Mat(LinTeste, atributos.cols, CV_32FC1);
	 labelTeste = Mat(LinTeste, 1, CV_32FC1);

	int a=0, b=0;

	for(int j=0; j<contLabel; j++)
	{
		int contaux=0;

		for(int y=0; y<atributos.rows; y++)
		{
			if(label.at<float>(y,0)==j)
			{
				if(contaux<vetAux[j])
				{
					for(int x=0; x<atributos.cols; x++)
					{
						treino.at<float>(a,x)= atributos.at<float>(y,x);
						labelTreino.at<float>(a,0)= label.at<float>(y,0);
					}
					a++;
				}

				if(contaux>=vetAux[j] && contaux<vetTotal[j])
				{
					for(int x=0; x<atributos.cols; x++)
					{
						teste.at<float>(b,x)=atributos.at<float>(y,x);
						labelTeste.at<float>(b,0)= label.at<float>(y,0);
					}
					b++;
				}
				
				contaux++;
			}
		}
	}

	end = (int)GetTickCount();
	temp_mili = end-start;

	printf("\nTempo para Leave One Out : %d ms\n",temp_mili);

}

void set_vector(int *&vet, int tamanho, int aleatorio)
{
	if(tamanho==1)
	{
		vet = new int[tamanho];
		vet[0]=aleatorio;
	}

	else
	{
		int *vetAux = new int[tamanho];

		for(int j=0; j<tamanho-1; j++)
			vetAux[j]=vet[j];

		delete[] vet;
		vet= new int[tamanho];

		for(int i=0; i<tamanho-1; i++)
			vet[i]=vetAux[i];
			
		vet[tamanho-1]=aleatorio;

		delete[] vetAux;
	}
}

void Hold_Out(Mat atributos, Mat label, Mat &treino, Mat &labelTreino, Mat &teste, Mat &labelTeste, float porcentagem)
{
	int start, end, temp_mili;
	start=(int)GetTickCount();

	int contLabel;
	contLabel = maxLabel(label); //Função para achar o numero de labels

	int *vetAux = new int[contLabel];
	int *vetTotal = new int[contLabel];

	for(int x=0; x<contLabel; x++)
	{
		vetAux[x]=0;
		vetTotal[x]=0;
	}

	for(int y=0; y<label.rows; y++)
	{
		for(int x=0; x<contLabel; x++) //For para saber quantos labels se repete
		{
			if(label.at<float>(y,0)==x)
				vetTotal[x]++;
		}
	}

	int LinTreino=0, LinTeste=0;

	for(int j=0; j<contLabel; j++)
	{
		vetAux[j]= (int)(vetTotal[j]*porcentagem/100); //porcentagem para cada label

		LinTreino+=vetAux[j];
		LinTeste+=(vetTotal[j]-vetAux[j]);
	}

	 treino = Mat(LinTreino, atributos.cols, CV_32FC1);
	 labelTreino = Mat(LinTreino, 1, CV_32FC1);
	 
	 teste = Mat(LinTeste, atributos.cols, CV_32FC1);
	 labelTeste = Mat(LinTeste, 1, CV_32FC1);

	srand((unsigned)time(NULL));

	int *vetExist; //vetor para guardar os valores que já foram gerados
	int valor;

	for(int aux=1; aux<=treino.rows; aux++)
	{
		if(aux==1)
		{
			valor=rand() % atributos.rows; //sorteando a linha

			for(int x=0; x<atributos.cols; x++) //jogando a linha sorteada para treino
			{
				treino.at<float>(aux-1, x) = atributos.at<float>(valor, x);
				labelTreino.at<float>(aux-1, 0) = label.at<float>(valor, 0);
			}

			vetAux[(int)label.at<float>(valor, 0)]--;

			set_vector(vetExist, aux, valor);
		}

		else
		{   
			do{
			valor=rand() % atributos.rows;
			}while(vetAux[(int)label.at<float>(valor, 0)]==0);

			for(int cont=0; cont<aux; cont++)
			{
				if(valor==vetExist[cont])
				{
					do{
					valor=rand() % atributos.rows;
					}while(vetAux[(int)label.at<float>(valor, 0)]==0);

					cont=-1; //encontrando a linha já sorteada, volta para a posição zero do vetor
				}
			}

			for(int x=0; x<atributos.cols; x++) 
				treino.at<float>(aux-1, x) = atributos.at<float>(valor, x);
				
			labelTreino.at<float>(aux-1, 0) = label.at<float>(valor, 0);
			

			vetAux[(int)label.at<float>(valor, 0)]--;

			set_vector(vetExist, aux, valor);
		}
	}

	int i=0;

	for(int y=0; y<atributos.rows; y++)
	{
		int contaux=0;

		for(int aux2=0; aux2<treino.rows; aux2++)
		{
			if(y==vetExist[aux2])
			{
				contaux=1;
				break;
			}
		}

		if(contaux==0 && i<teste.rows)
		{
			for(int x=0; x<atributos.cols; x++)
					teste.at<float>(i,x) = atributos.at<float>(y,x);
		
			labelTeste.at<float>(i,0) = label.at<float>(y,0);

			i++;
		}
	}

	end = (int)GetTickCount();
	temp_mili = end-start;

	printf("Tempo para Hold Out : %d ms\n",temp_mili);
}

void K_means(Mat treino, Mat labelTreino, Mat teste, Mat labelTeste, int quantidadeAtributos, int quantClasses)
{
	int start, end, temp_mili;
	start=(int)GetTickCount();

	printf("\n\t START K_Means\n");
    printf("\nTreinando K_Means...");

	float menor_dist, percent_acerto=0, AuxLabel;

	Mat media_labels(quantClasses, treino.cols, CV_32FC1); //Mat para guardar a media de cada classe

	for(int aux=0; aux<quantClasses; aux++)
	{
		for(int x=0; x<treino.cols; x++)
		{
			float media=0;
			int cont1=0;

			for(int y=0; y<treino.rows; y++)
			{
				if(labelTreino.at<float>(y,0)==aux)
				{
					media+=treino.at<float>(y,x);
					cont1++;
				}
			}

			media_labels.at<float>(aux,x)=media/cont1;
		}
	}

	for(int i=0; i<teste.rows; i++)
	{
		for(int aux=0; aux<media_labels.rows; aux++)
		{
			float dist=0;

			for(int x=0; x<media_labels.cols; x++)
				dist+= pow(media_labels.at<float>(aux,x)-teste.at<float>(i,x),2);

			dist=sqrt(dist);

			if(aux==0)
			{
				menor_dist=dist;
				AuxLabel = (float)aux;
			}

			else
			{
				if(menor_dist>dist)
				{
					menor_dist=dist;
					AuxLabel = (float)aux;
				}
			}
		}

		if(AuxLabel==labelTeste.at<float>(i,0))
			percent_acerto++;
	}
	
	printf("OK!\n\n");
	end = (int)GetTickCount();
	temp_mili = end-start;
	printf("Training time: %d ms\n\n", temp_mili);

	percent_acerto=(percent_acerto/teste.rows);
	printf("A taxa de acerto foi de : %f\n", percent_acerto);
	printf("O percentual de acerto foi de : %f %%\n",percent_acerto*100.0);
	printf("\n\t END K_Means\n\n");
}

int labelrepeated(float *AuxLabel, int N)
{
	int *cont= new int[N];
	int ind;
	int maior;

	for(int aux=0; aux<N; aux++)
		cont[aux]=0;

	for(int aux=0; aux<N; aux++)
	{
		for(int x=0; x<N; x++)
		{
			if(aux!=x)
			{
				if(AuxLabel[aux]==AuxLabel[x])
					cont[aux]++;
			}
		}
	}

	for(int i=0; i<N; i++)
	{
		if(i==0)
		{
			maior=cont[i];
			ind=i;
		}
	
		else
		{
			if(cont[i]>maior)
			{
				maior=cont[i];
				ind=i;
			}
		}
	}

	return ind;
}

void KNN_N(Mat treino, Mat labelTreino, Mat teste, Mat labelTeste, int N)
{
	int start, end, temp_mili;
	start=(int)GetTickCount();

	printf("\n\t START KNN-%d\n",N);
    printf("\nTreinando KNN-%d...",N);

	float percent_acerto=0;
	int acerto;
	float *AuxLabel = new float[N];
	float *menor_dist = new float [N];

	for(int i=0; i<teste.rows; i++)
	{
		for(int y=0; y<treino.rows; y++)
		{
			float dist=0;
			int aux=0;

			for(int x=0; x<treino.cols; x++)
				dist+= pow(treino.at<float>(y,x)-teste.at<float>(i,x),2);
			
			dist = sqrt(dist); //Terminando de calcular a distancia

			if(y==0)
			{
				for(aux=0; aux<N; aux++)
				{
					menor_dist[aux]=dist;
					AuxLabel[aux] = labelTreino.at<float>(y,0);
				}
			}
			else
			{
				if(dist<menor_dist[0])
				{
					for(int k=N-1; k>=0; k--)
					{
						if(k==0)
						{
							menor_dist[k]=dist;
							AuxLabel[k]=labelTreino.at<float>(y,0);
						}
							
						else
						{
							menor_dist[k]= menor_dist[k-1];
							AuxLabel[k]= AuxLabel[k-1]; 
						}
					}
				}
			}
		}

	acerto = labelrepeated(AuxLabel, N); //chamando a função para saber o label que mais se repete

		if(AuxLabel[acerto]==labelTeste.at<float>(i,0))
			percent_acerto++;
	}

	printf("OK!\n\n");
	end = (int)GetTickCount();
	temp_mili = end-start;
	printf("Training time: %d ms\n\n", temp_mili);

	percent_acerto=(percent_acerto/teste.rows);
	printf("A taxa de acerto foi de : %f\n", percent_acerto);
	printf("O percentual de acerto foi de : %f %%\n",percent_acerto*100.0);
	printf("\n\t END KNN-%d\n\n",N);
}
