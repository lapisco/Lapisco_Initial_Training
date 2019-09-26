#include "opencv\cv.h"
#include "opencv\highgui.h"

using namespace cv;

void contagem(int &rows, int &cols,char*endereco);
void mat_Principal(Mat &atributos,Mat &label, int lin, int col,char*endereco);
void normalizar(Mat &atributos);
int maxLabel(Mat label);
void Leave_One_Out(Mat atributos, Mat label, Mat &treino, Mat &labelTreino, Mat &teste, Mat &labelTeste, float porcentagem);
float  KNN_1( Mat treino, Mat labelTreino, Mat teste, Mat labelTeste);
void KNN_N(Mat treino, Mat labelTreino, Mat teste, Mat labelTeste, int N);
void Hold_Out(Mat atributos, Mat label, Mat &treino, Mat &labelTreino, Mat &teste, Mat &labelTeste, float porcentagem);
void set_vector(int *&vet, int tamanho, int aleatorio);
int labelrepeated(float *AuxLabel, int N);
