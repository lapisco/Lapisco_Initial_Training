#include "opencv\cv.h"
#include "opencv\highgui.h"

using namespace cv;
using namespace std;

int main()
 {
	 Mat imagem = imread("Iron_Man.jpg",1);

	 vector<Mat> bgr_planes;
	 split(imagem, bgr_planes );
	 imshow("Blue", bgr_planes[0]);
	 imshow("Green", bgr_planes[1]);
	 imshow("Red", bgr_planes[2]);

	 imwrite("Blue.jpg", bgr_planes[0]);
	 imwrite("Green.jpg", bgr_planes[1]);
	 imwrite("Red.jpg", bgr_planes[2]);

	 waitKey(0);
 }
