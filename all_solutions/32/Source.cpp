#include "opencv\cv.h"
#include "opencv\highgui.h"

using namespace cv;
using namespace std;

int main()
 {
	 Mat imagem = imread("image.jpg",1);
	 Mat gray; Mat canny;

	 vector<vector<Point>> contours; //cria um vetor de pontos
	 Rect region;

	 cvtColor(imagem, gray, CV_BGR2GRAY);

	 Canny(gray, canny, 127, 255 , 3);


	findContours(canny, contours, CV_RETR_EXTERNAL,  CV_CHAIN_APPROX_SIMPLE );
	printf("Numero de contornos encontrados = %d\n\n",contours.size());

     /// Approximate contours to polygons + get bounding rects and circles
     vector<vector<Point> > contours_poly( contours.size() );
     vector<Rect> boundRect( contours.size() );
     vector<Point2f>center( contours.size() );
     vector<float>radius( contours.size() );

     for( int i = 0; i < contours.size(); i++ )
     { 
         approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
         boundRect[i] = boundingRect( Mat(contours_poly[i]) );
		 double area = contourArea(contours[i], false);
		 printf("Area do Objeto %d = %.2f\n", i, area);	
     }

     /// Draw polygonal contour + bonding rects
     Mat drawing = canny.clone();
	 cvtColor(drawing, drawing, CV_GRAY2BGR);
     for( int i = 0; i< contours.size(); i++ )
     {
         rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), Scalar(250,255,0), 2, 8, 0 );          
     }

	 imshow("Desenho", drawing);
	 waitKey(0);
 }
