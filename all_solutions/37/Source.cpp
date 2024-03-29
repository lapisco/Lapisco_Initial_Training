#include "opencv\cv.h"
#include "opencv\highgui.h"

using namespace cv;
using namespace std;

int main()
 {
	 Mat imagem = imread("image.jpg",1);
	 Mat gray; Mat limiar = imagem.clone(); Mat otsu = imagem.clone();

	 cvtColor(imagem, gray, CV_BGR2GRAY);
	 threshold(gray, limiar, 127, 255, THRESH_OTSU);
	

/*Mat elementos= getStructuringElement (Tipo de dilata��o, Size(3 ou 5 ou 7... , 3 ou 5 ou 7...), Point(-1,-1)) 

OBS: 1) Size(3 ou 5 ou 7... , 3 ou 5 ou 7...) = Kernel utilizado, mascara
	 2) Caso n�o coloque o ponto, admite-se que est� no centro do objeto = Point(-1,-1)

	TIPOS DE KERNEL (Serve tanto para eros�o, quanto para dilata��o)

	Caixa retangular: MORPH_RECT
	Cruz: MORPH_CROSS
	Ellipse: MORPH_ELLIPSE
*/
	 Mat  element  =  getStructuringElement (MORPH_RECT,Size(2,2), Point(-1,-1)); 

	 int dilatacao=20;

	 for(int aux=0; aux<dilatacao; aux++)
	 {
		  dilate(limiar, otsu, element, Point(-1,-1), aux);
		  imshow("Dilate", otsu);
		  waitKey(100);
	 }

	 imshow("Imagem_Limiar", otsu);

	 waitKey(0);
 }
