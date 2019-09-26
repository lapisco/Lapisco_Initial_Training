#include "opencv\cv.h"
#include "opencv\highgui.h"

using namespace cv;
using namespace std;

int main()
 {
	 Mat imagem = imread("Iron_Man.jpg",1);
	 
	 Mat gray;
	 Mat limiar;

	 cvtColor(imagem, gray, CV_BGR2GRAY);
	 imshow("CINZA", gray);

	 /* PARAMETROS DA FUN��O

	 src = imagem de entrada
	 dst = imagem de saida
	 maxValue =  valor diferente de zero atribu�da aos pixels para que a condi��o � satisfeita.
	 adaptiveMethod - algoritmo de limiar adaptativo de usar, ADAPTIVE_THRESH_MEAN_C ou ADAPTIVE_THRESH_GAUSSIAN_C .
	 thresholdType - Thresholding tipo que deve ser ou THRESH_BINARY ou THRESH_BINARY_INV .
	 blockSize - Tamanho de uma vizinhan�a do pixel que � usada para calcular um valor de limiar para o pixel: 3, 5, 7, e assim por diante.
	 C - Constante subtra�do da m�dia ou m�dia ponderada (veja os detalhes abaixo). Normalmente, � positivo, mas podem ser zero ou negativos tamb�m.

	 */

	 adaptiveThreshold(gray, limiar, 220, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY_INV, 5, 10);
	 imshow("LIMIAR", limiar);
	 imwrite("Limiar.jpg", limiar);

	 waitKey(0);
 }
