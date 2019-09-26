#include "opencv\cv.h"
#include "opencv\highgui.h"

using namespace cv;
using namespace std;

int main()
 {
	 Mat imagem = imread("Iron_Man.jpg",1);
	 
	 imshow("IRON_MAN", imagem);
	 imwrite("image.jpg", imagem);

	 waitKey(0);
 }
