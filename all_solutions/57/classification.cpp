#include"opencv\cv.h"
#include"opencv\highgui.h"
#include"opencv2/opencv.hpp"
#include"opencv2/ml/ml.hpp"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<windows.h>
#include<Windows.h>
#include<direct.h>

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
	contLabel = maxLabel(label); //Fun��o para achar o numero de labels

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
	contLabel = maxLabel(label); //Fun��o para achar o numero de labels

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

	int *vetExist; //vetor para guardar os valores que j� foram gerados
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

					cont=-1; //encontrando a linha j� sorteada, volta para a posi��o zero do vetor
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

	printf(" %d ms\n",temp_mili);
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

float KNN_1(Mat treino, Mat labelTreino, Mat teste, Mat labelTeste)
{
	int start, end, temp_mili;
	start=(int)GetTickCount();

	float menor_dist, porcentagem=0, AuxLabel;

	for(int i=0; i<teste.rows; i++)
	{
		for(int y=0; y<treino.rows; y++)
		{
			float dist=0;

			for(int x=0; x<treino.cols; x++)
				dist+= pow(treino.at<float>(y,x)-teste.at<float>(i,x),2);
			
			dist = sqrt(dist); //Terminando de calcular a distancia

			if(y==0)
			{
				menor_dist=dist;
				AuxLabel = labelTreino.at<float>(y,0);
			}
			else
			{
				if(menor_dist>dist)
				{
					menor_dist=dist;
					AuxLabel = labelTreino.at<float>(y,0);
				}
			}
		}

		if(AuxLabel==labelTeste.at<float>(i,0))
			porcentagem++;
	}

	porcentagem= (porcentagem/teste.rows)*100;

	end = (int)GetTickCount();
	temp_mili = end-start;

	printf("%d ms\n",temp_mili);

	return porcentagem;
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

	acerto = labelrepeated(AuxLabel, N); //chamando a fun��o para saber o label que mais se repete

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

void KNN_OpenCv(Mat label, Mat treino, Mat labelTreino, Mat teste, Mat labelTeste,  int numK)
{
	int K=numK;
	//KNN -- TREINAMENTO
	int start, end, temp_mili;
	start=(int)GetTickCount();

	printf("\n\t START KNN-%d_OpenCv\n",K);
    printf("\nTreinando KNN-%d_OpenCv...",K);

	 CvKNearest knn(treino, labelTreino, cv::Mat(), false, K);

	 //------------------------------------------------------------
     //-----------------KNN CLASSIFICACAO--------------------------
     //------------------------------------------------------------
        
     cv::Mat test_sample;
     float acerto = 0;
     float erro = 0;

	 for (int tsample = 0; tsample<teste.rows; tsample++) 
	 {
            test_sample = teste.row(tsample);
            
            int res =(int)knn.find_nearest(test_sample, K);
            int test = (int) (labelTeste.at<float>(tsample,0));
            
            if (test!=res)
                erro++;
            
			else 
                acerto++;
     }

	printf("OK!\n\n");
	end = (int)GetTickCount();
	temp_mili = end-start;
	printf("Training time: %d ms\n\n", temp_mili);

	float percent_acerto=(acerto/teste.rows);
	printf("A taxa de acerto foi de : %f\n", percent_acerto);
	printf("O percentual de acerto foi de : %f %%\n",percent_acerto*100.0);
	printf("\n\t END KNN-%d_OpenCv\n\n",K);
}

void MLP_Opencv(Mat &normalizado,Mat &lable,Mat &teste,Mat &teste_lable,Mat &treino,Mat &treino_lable, int quantidadeAtributos, int quantClasses, float porcentagem, int config, int tamanho_teste,int tamanho_treino)
{
	printf("\n\tSTART MLP\n\n");

	Mat teste_lable_MLP(teste.rows, quantClasses,CV_32F);
	Mat treino_lable_MLP(treino.rows, quantClasses,CV_32F);
	Mat classificationResult(1, quantClasses, CV_32FC1);

	//------------------------------------------------------------
    //-----------------MLP TREINAMENTO----------------------------
    //------------------------------------------------------------

	Mat layers(3,1,CV_32S);
	
	int x,y;
	int val;

	for(y=0;y<tamanho_teste;y++)
	{
		val = (int)teste_lable.at<float>(y,0);
		for(x=0;x<quantClasses;x++)
		{
			if(val==x)
			{
				teste_lable_MLP.at<float>(y,x) = 1;
			}
			else
			{
				teste_lable_MLP.at<float>(y,x) = 0;
			}
		}
	}
	for(y=0;y<tamanho_treino;y++)
	{
		val = (int)treino_lable.at<float>(y,0);
		for(x=0;x<quantClasses;x++)
		{
			if(val==x)
			{
				treino_lable_MLP.at<float>(y,x) = 1;
			}
			else
			{
				treino_lable_MLP.at<float>(y,x) = 0;
			}
		}
	}

	int numHiddenLayer;
	switch (config) 
	{
	case 1:
		numHiddenLayer = (quantClasses+quantidadeAtributos)/2;
		layers.at<int>(0,0) =quantidadeAtributos;//input layer
        layers.at<int>(1,0)=numHiddenLayer;//hidden layer
        layers.at<int>(2,0) =quantClasses;//output layer
		break;
    case 2:
		numHiddenLayer = (quantClasses+quantidadeAtributos)*2/3;
        layers.at<int>(0,0) = quantidadeAtributos;//input layer
        layers.at<int>(1,0)=numHiddenLayer;//hidden layer
        layers.at<int>(2,0) =quantClasses;//output layer
        break;
	default:
		numHiddenLayer = (quantClasses+quantidadeAtributos)/2;
        layers.at<int>(0,0) = quantidadeAtributos;//input layer
        layers.at<int>(1,0)=numHiddenLayer;//hidden layer
        layers.at<int>(2,0) =quantClasses;//output layer
		break;
	}
	CvANN_MLP nnetwork(layers, CvANN_MLP::SIGMOID_SYM,0.6,1);
	CvANN_MLP_TrainParams params(
                                     // terminate the training after either 1000
                                     // iterations or a very small change in the
                                     // network wieghts below the specified value
                                     cvTermCriteria(CV_TERMCRIT_ITER+CV_TERMCRIT_EPS, 1000, 0.000001),
                                     // use backpropogation for training
                                     CvANN_MLP_TrainParams::BACKPROP,
                                     // co-efficents for backpropogation training
                                     // recommended values taken from http://docs.opencv.org/modules/ml/doc/neural_networks.html#cvann-mlp-trainparams
                                     0.1,
                                     0.1);
	// train the neural network (using training data)

	int start, end, temp_mili;
	start=(int)GetTickCount();
	printf("Treinando MLP...");
    int iterations = nnetwork.train(treino, treino_lable_MLP,cv::Mat(),cv::Mat(),params);
    printf("OK!\n\n");
	end = (int)GetTickCount();
	temp_mili = end-start;
	printf("Training time: %d ms\n\n", temp_mili);

    //------------------------------------------------------------
    //-----------------MLP CLASSIFICACAO--------------------------
    //------------------------------------------------------------
        
    Mat linha_teste;

	float cont_acerto = 0;
	int cont_erro = 0;

	int nClasses = quantClasses;
	
	for (int tsample = 0; tsample < tamanho_teste; tsample++) 
	{
		// extract the sample
		linha_teste = teste.row(tsample);
		//try to predict its class
		nnetwork.predict(linha_teste, classificationResult);
        /*The classification result matrix holds weightage  of each class.
        we take the class with the highest weightage as the resultant class */
            
        // find the class with maximum weightage.
        int maxIndex = 0;
        float value=0.0f;
        float maxValue=classificationResult.at<float>(0,0);
		for(int index=1;index<quantClasses;index++)
		{ 
			value = classificationResult.at<float>(0,index);
            if(value>maxValue)
            {   
				maxValue = value;
				maxIndex=index;
			}
		}

		if (teste_lable_MLP.at<float>(tsample, maxIndex)!=1.0f)
		{
			cont_erro++;
		}
		else 
		{
			cont_acerto++;
		}
	}
	float percent_acerto=(cont_acerto/tamanho_teste);
	printf("A taxa de acerto foi de : %f\n",percent_acerto);
	printf("O percentual de acerto foi de : %f %%\n",percent_acerto*100.0);
	printf("\n\t END MLP\n\n");

	linha_teste.release();
	teste_lable_MLP.release();
	treino_lable_MLP.release();
	classificationResult.release();
	layers.release();
}

void SVM_OpenCv(Mat teste, Mat teste_label, Mat treino, Mat treino_label, int quantidadeAtributos, int quantClasses, int kernell, int parametrosAutomaticos)
{
        //------------------------------------------------------------
        //-----------------SVM TREINAMENTO----------------------------
        //------------------------------------------------------------
        
		printf("\n\t START SVM\n");

        CvSVMParams param = CvSVMParams();
        
        param.svm_type = CvSVM::C_SVC;
        
        switch (kernell) {
            case 1:
                param.kernel_type = CvSVM::LINEAR;
                break;
            case 2:
                param.kernel_type = CvSVM::RBF;
                break;
            case 3:
                param.kernel_type = CvSVM::POLY;
                break;
            case 4:
                param.kernel_type = CvSVM::SIGMOID;
                break;
            default:
                param.kernel_type = CvSVM::LINEAR;
                break;
        }
        
        param.degree = 1; // for poly
        param.gamma = 20; // for poly/rbf/sigmoid
        param.coef0 =10; // for poly/sigmoid
        
        param.C = 7; // for CV_SVM_C_SVC, CV_SVM_EPS_SVR and CV_SVM_NU_SVR
        param.nu = 0.0; // for CV_SVM_NU_SVC, CV_SVM_ONE_CLASS, and CV_SVM_NU_SVR
        param.p = 0.0; // for CV_SVM_EPS_SVR
        
        param.class_weights = NULL; // for CV_SVM_C_SVC
        param.term_crit.type = CV_TERMCRIT_ITER +CV_TERMCRIT_EPS;
        param.term_crit.max_iter = 1000;
        param.term_crit.epsilon = 1e-6;
        
        // SVM training
        CvSVM SVM;
        
        //struct timeval tic, toc;
        
        if(parametrosAutomaticos)
        {
			printf("\nTreinando SVM...");
        //int start, end, temp_mili;
		//start=(int)GetTickCount();

			int iteractions = SVM.train_auto(treino, treino_label, cv::Mat(), cv::Mat(), param);
        
		//end = (int)GetTickCount();
		//temp_mili = end-start;
			printf( "OK\n\n");

			//printf("Training time: %d mili seconds\n\n",temp_mili);
        }
        else
        {
            printf("\nTreinando SVM...");
         //int start, end, temp_mili;
		 //start=(int)GetTickCount();

			int iteractions = SVM.train(treino, treino_label, cv::Mat(), cv::Mat(), param);
        
		 //end = (int)GetTickCount();
		 //temp_mili = end-start;
            printf( "OK\n\n");

			//printf("Training time: %d mili seconds\n\n",temp_mili);
        }
        
        //------------------------------------------------------------
        //-----------------SVM CLASSIFICACAO--------------------------
        //------------------------------------------------------------
        
        Mat test_sample;
        int acerto = 0;
        int erro = 0;

        for (int tsample = 0; tsample < teste.rows; tsample++)
        {         
			test_sample = teste.row(tsample);
            
            int res = (int) (SVM.predict(test_sample));
			int test = (int) (teste_label.at<float>(tsample,0));
            
            if (test!=res)
                erro++;   
     
			else 
                acerto++;
        }

		float percent_acerto=((float)acerto/(float)teste.rows);
		printf("A taxa de acerto foi de : %f\n",percent_acerto);
		printf("O percentual de acerto foi de : %f %\n",percent_acerto*100.0);
		printf("\t END SVM\n\n");
}
