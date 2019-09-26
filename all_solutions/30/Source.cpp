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
	 
	 /* PARAMETROS DA FUN��O

	 - Imagem de entrada para achar os contornos;
	 - contours = Detectado contornos. Cada contorno � armazenado como um vetor de pontos
	 - MODO:
	 CV_RETR_EXTERNAL = pega apenas os contornos externos. 
	 CV_RETR_LIST = pega todos os contornos , sem estabelecer quaisquer rela��es hier�rquicas.
	 CV_RETR_CCOMP = pega todos os contornos e as organiza em uma hierarquia de dois n�veis. No n�vel mais alto, existem limites externos das componentes. No segundo n�vel, existem limites dos furos. Se houver outro contorno dentro de um buraco de um componente conectado, ele ainda � colocado no n�vel superior.
	 CV_RETR_TREE = pega todos os contornos e reconstr�i uma hierarquia completa de aninhados contornos . Esta hierarquia completa � constru�do e apresentado na OpenCV contours.c demonstra��o.
	
	 - METODO:

	 CV_CHAIN_APPROX_NONE = armazena absolutamente todos os pontos de contorno. Ou seja, quaisquer dois pontos subsequentes (x1, y1) e (x2, y2) do contorno ser� ou vizinhos horizontal, vertical ou diagonal, isto �, Max (abs (x1-x2), ABS (Y2-Y1)) == 1 .
	 CV_CHAIN_APPROX_SIMPLE = comprime segmentos horizontais, verticais e diagonais e deixa apenas os seus pontos finais. Por exemplo, um contorno rectangular-se-� direita � codificada com 4 pontos.
	 CV_CHAIN_APPROX_TC89_L1, CV_CHAIN_APPROX_TC89_KCOS = aplica-se um dos sabores do algoritmo cadeia aproxima��o Teh-Chin. Veja [TehChin89] para mais detalhes.
	
	*/

	 findContours(canny, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	 printf("Numero de contornos encontrados = %d",contours.size());

	 waitKey(0);
 }
