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

	 /* PARAMETROS DA FUNÇÃO

	 src = imagem de entrada
	 dst = imagem de saida
	 maxValue =  valor diferente de zero atribuída aos pixels para que a condição é satisfeita.
	 adaptiveMethod - algoritmo de limiar adaptativo de usar, ADAPTIVE_THRESH_MEAN_C ou ADAPTIVE_THRESH_GAUSSIAN_C .
	 thresholdType - Thresholding tipo que deve ser ou THRESH_BINARY ou THRESH_BINARY_INV .
	 blockSize - Tamanho de uma vizinhança do pixel que é usada para calcular um valor de limiar para o pixel: 3, 5, 7, e assim por diante.
	 C - Constante subtraído da média ou média ponderada (veja os detalhes abaixo). Normalmente, é positivo, mas podem ser zero ou negativos também.

	 */

	 adaptiveThreshold(gray, limiar, 220, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY_INV, 5, 10);
	 imshow("LIMIAR", limiar);
	 imwrite("Limiar.jpg", limiar);

	 waitKey(0);
 }
