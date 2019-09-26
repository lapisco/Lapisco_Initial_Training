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

	 do{
	 printf("Informe a porcentagem de Treino: ");
	 scanf("%f",&porcentagemTreino);

		if(porcentagemTreino<0 || porcentagemTreino>100)
			printf("\n\tDigite valores validos para porcentagem... entre (0 e 100)\n\n");
	
	 }while(porcentagemTreino<0 || porcentagemTreino>100);

	 //Criando as Mats para Treino e Teste
	 Mat treino; Mat labelTreino; Mat teste; Mat labelTeste;

	 int opcaoMetodos;

	 printf("\n");

	 do{
		 printf("\tEscolha um dos metodos abaixo:\n \t\t1- Leave One Out\n\t\t2- Hold Out\n");
		 printf("Opcao: ");
		 scanf("%d", &opcaoMetodos);

		 if(opcaoMetodos<1 || opcaoMetodos>2)
			 printf("\nOPCAO INCORRETA!! Digite novamente...\n\n");
	 }while(opcaoMetodos<1 || opcaoMetodos>2);

	  if(opcaoMetodos==1)
		Leave_One_Out(atributos, label, treino, labelTreino, teste, labelTeste, porcentagemTreino);
	 else
		Hold_Out(atributos, label, treino, labelTreino, teste, labelTeste, porcentagemTreino);

	 printf("\n");

	 //Criação de Variaveis Uteis
	 int tamanho_teste = teste.rows;
	 int tamanho_treino = treino.rows;
	 int atrib = atributos.cols;
	 int classes = maxLabel(label);

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

	SVM_OpenCv(teste, labelTeste, treino, labelTreino, atrib, classes, kernell, paramAut);

	 system("Pause");
}
