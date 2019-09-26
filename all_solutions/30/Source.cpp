#include "opencv\cv.h"
#include "opencv\highgui.h"

using namespace cv;
using namespace std;

int main()
 {
	 Mat imagem = imread("image.jpg",1);
	 Mat gray; Mat canny;

	 vector<vector<Point>> contours; //cria um vetor de pontos

	 cvtColor(imagem, gray, CV_BGR2GRAY);
	 Canny(gray, canny, 127, 255 , 3);
	 imshow("Canny", canny);
	 
	 /* PARAMETROS DA FUNÇÃO

	 - Imagem de entrada para achar os contornos;
	 - contours = Detectado contornos. Cada contorno é armazenado como um vetor de pontos
	 - MODO:
	 CV_RETR_EXTERNAL = pega apenas os contornos externos. 
	 CV_RETR_LIST = pega todos os contornos , sem estabelecer quaisquer relações hierárquicas.
	 CV_RETR_CCOMP = pega todos os contornos e as organiza em uma hierarquia de dois níveis. No nível mais alto, existem limites externos das componentes. No segundo nível, existem limites dos furos. Se houver outro contorno dentro de um buraco de um componente conectado, ele ainda é colocado no nível superior.
	 CV_RETR_TREE = pega todos os contornos e reconstrói uma hierarquia completa de aninhados contornos . Esta hierarquia completa é construído e apresentado na OpenCV contours.c demonstração.
	
	 - METODO:

	 CV_CHAIN_APPROX_NONE = armazena absolutamente todos os pontos de contorno. Ou seja, quaisquer dois pontos subsequentes (x1, y1) e (x2, y2) do contorno será ou vizinhos horizontal, vertical ou diagonal, isto é, Max (abs (x1-x2), ABS (Y2-Y1)) == 1 .
	 CV_CHAIN_APPROX_SIMPLE = comprime segmentos horizontais, verticais e diagonais e deixa apenas os seus pontos finais. Por exemplo, um contorno rectangular-se-à direita é codificada com 4 pontos.
	 CV_CHAIN_APPROX_TC89_L1, CV_CHAIN_APPROX_TC89_KCOS = aplica-se um dos sabores do algoritmo cadeia aproximação Teh-Chin. Veja [TehChin89] para mais detalhes.
	
	*/

	 findContours(canny, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	 printf("Numero de contornos encontrados = %d",contours.size());

	 waitKey(0);
 }
