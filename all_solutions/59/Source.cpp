#include "opencv\cv.h"
#include "opencv\highgui.h"
#include "classification.h"

using namespace cv;

int lin=0, col=0;
float porcentagemTreino;

int main()
{
	 char endereco[200]="num_padronizado_MomCent_OpenCv.txt";

	 contagem(lin,col,endereco); //Função para contar numero de linhas e colunas do arquivo lido
	 
	 Mat atributos(lin, col, CV_32FC1);
	 Mat label(lin, 1, CV_32FC1);

	 mat_Principal(atributos,label,lin,col,endereco); //Função para colocar os valores no mat
	 normalizar(atributos); //Função para normalizar os atributos para que fique entre 0 e 1

int opcaoFinal;

do{
	 do{
	 printf("Informe a porcentagem de Treino: ");
	 scanf("%f",&porcentagemTreino);

		if(porcentagemTreino<0 || porcentagemTreino>100)
			printf("\n\tDigite valores validos para porcentagem... entre (0 e 100)\n\n");
	
	 }while(porcentagemTreino<0 || porcentagemTreino>100);

	 //Criando as Mats para Treino e Teste
	 Mat treino; Mat labelTreino; Mat teste; Mat labelTeste;

	 //PARA KNN_N
	 
	 int opcaoMetodos, opcaoClassificacao;

	 printf("\n");

	 do{
		 printf("\tEscolha um dos metodos abaixo:\n \t\t1- Leave One Out\n\t\t2- Hold Out\n");
		 printf("Opcao: ");
		 scanf("%d", &opcaoMetodos);

		 if(opcaoMetodos<1 || opcaoMetodos>2)
			 printf("\nOPCAO INCORRETA!! Digite novamente...\n\n");
	 }while(opcaoMetodos<1 || opcaoMetodos>2);

	 printf("\n");

	 do{
		 printf("Selecione o metodo de classificacao desejado: \n");
		 printf(" 1-KNN_Manual\n 2-K_Means\n 3-KNN_OpenCv\n 4-MLP\n 5-SVM\n 6-Bayes\n");
		 printf("\t\t\tOpcao: ");
		 scanf("%d",&opcaoClassificacao);

		 if(opcaoClassificacao<1 || opcaoClassificacao>6)
			 printf("\nOPCAO INCORRETA!! Digite novamente...\n\n");

	 }while(opcaoClassificacao<1 || opcaoClassificacao>6);

	 if(opcaoMetodos==1)
		Leave_One_Out(atributos, label, treino, labelTreino, teste, labelTeste, porcentagemTreino);
	 else
		Hold_Out(atributos, label, treino, labelTreino, teste, labelTeste, porcentagemTreino);

	 //Criação de Variaveis Uteis
	 int tamanho_teste = teste.rows;
	 int tamanho_treino = treino.rows;
	 int atrib = atributos.cols;
	 int classes = maxLabel(label);
	 Mat predict_result;
	 int configMLP=1;


	 switch(opcaoClassificacao)
	 {
		case 1: //KNN Manual

			int K;
				 do{
					printf("\nDigite o valor de K para o KNN. Valores entre 1, 3, 5, 7\n");
					printf("Opcao: ");
					scanf("%d",&K);

						if(K!=1 && K!=3 && K!=5 && K!=7)
							printf("\nOPCAO INCORRETA!! Digite valores validos para K...\n\n");

				 }while(K!=1 && K!=3 && K!=5 && K!=7);

				KNN_N(endereco, predict_result, treino, labelTreino, teste, labelTeste, K, atrib, classes, porcentagemTreino);

		break;

		case 2: //K_Means

			K_means(endereco, predict_result, treino, labelTreino, teste, labelTeste, atrib, classes, porcentagemTreino);

		break;

		case 3: //KNN_OpenCv
			
				 do{
					printf("\nDigite o valor de K para o KNN. Valores entre 1, 3, 5, 7\n");
					printf("Opcao: ");
					scanf("%d",&K);

						if(K!=1 && K!=3 && K!=5 && K!=7)
							printf("\nOPCAO INCORRETA!! Digite valores validos para K...\n\n");

				 }while(K!=1 && K!=3 && K!=5 && K!=7);

				 KNN_OpenCv(endereco, predict_result, label, treino, labelTreino, teste, labelTeste,  K, atrib, classes, porcentagemTreino);

		break;

		case 4: //MLP

			MLP_Opencv(endereco, predict_result, atributos, label, teste, labelTeste, treino, labelTreino, atrib, classes, porcentagemTreino, configMLP, tamanho_teste, tamanho_treino);

		break;

		case 5: //SVM

		int paramAut, kernell; // Tipo de Kernell

			do{
				printf("\n0- Parametro Manual\t1- Parametro Automatico\n");
				printf("Escolha o parametro desejado: ");
				scanf("%d",&paramAut);

				if(paramAut<0 || paramAut>1)
					printf("\nOPCAO INCORRETA!! Digite novamente...\n\n");
			}while(paramAut<0 || paramAut>1);

			do{
				printf("\nEscolha o tipo de topologia para SVM:\n");
				printf(" 1-LINEAR   2-RBF   3-POLY   4-SIGMOID\n");
				printf("Opcao: ");
				scanf("%d",&kernell);

				if(kernell<1 || kernell>4)
					printf("\nOPCAO INCORRETA!! Digite novamente...\n\n");
			}while(kernell<1 || kernell>4);

			SVM_OpenCv(endereco, predict_result, teste, labelTeste, treino, labelTreino, atrib, classes, porcentagemTreino, kernell, paramAut);

		break;

		case 6: //Bayes

			Bayes_OpenCv(endereco, predict_result, teste, labelTeste, treino, labelTreino, atrib, classes, porcentagemTreino);

		break;
	 }

	do{
		printf("\t\tDeseja fazer outra operacao?");
		printf("\n\t\t\t1 - SIM");
		printf("\n\t\t\t2 - NAO");
		printf("\n\t\tOPCAO: ");
		scanf_s("%d",&opcaoFinal);

		if (opcaoFinal<1 || opcaoFinal>2)
			printf("\n\t   >>>>>Opcao INCORRETA! Digite novamente<<<<<\n\n");

	}while(opcaoFinal<1 || opcaoFinal>2);

		printf("\n");

}while(opcaoFinal==1);

	 system("Pause");
}
