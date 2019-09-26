#include "opencv\cv.h"
#include "opencv\highgui.h"

using namespace cv;

void contagem(int &rows, int &cols,char*endereco);
void mat_Principal(Mat &atributos,Mat &label, int lin, int col,char*endereco);
void normalizar(Mat &atributos);
int maxLabel(Mat label);
void Leave_One_Out(Mat atributos, Mat label, Mat &treino, Mat &labelTreino, Mat &teste, Mat &labelTeste, float porcentagem);
void set_vector(int *&vet, int tamanho, int aleatorio);
void Hold_Out(Mat atributos, Mat label, Mat &treino, Mat &labelTreino, Mat &teste, Mat &labelTeste, float porcentagem);
void K_means(char*endereco, Mat &predict_result, Mat treino, Mat labelTreino, Mat teste, Mat labelTeste, int quantidadeAtributos, int quantClasses, float porcentagem);
float KNN_1(Mat treino, Mat labelTreino, Mat teste, Mat labelTeste);
int labelrepeated(float *AuxLabel, int N);
void KNN_N(char*endereco, Mat &predict_result, Mat treino, Mat labelTreino, Mat teste, Mat labelTeste, int N, int quantidadeAtributos, int quantClasses, float porcentagem);
void KNN_OpenCv(char*endereco, Mat &predict_result, Mat label, Mat treino, Mat labelTreino, Mat teste, Mat labelTeste,  int numK, int quantidadeAtributos, int quantClasses, float porcentagem);
void MLP_Opencv(char*endereco, Mat &predict_result, Mat &normalizado,Mat &lable,Mat &teste,Mat &teste_lable,Mat &treino,Mat &treino_lable, int quantidadeAtributos, int quantClasses, float porcentagem, int config, int tamanho_teste,int tamanho_treino);
void SVM_OpenCv(char*endereco, Mat &predict_result, Mat teste, Mat teste_label, Mat treino, Mat treino_label, int quantidadeAtributos, int quantClasses, float porcentagem, int kernell, int parametrosAutomaticos);
void Bayes_OpenCv(char*endereco, Mat &predict_result, Mat teste, Mat teste_label, Mat treino, Mat treino_label, int quantidadeAtributos, int quantClasses, float porcentagem);