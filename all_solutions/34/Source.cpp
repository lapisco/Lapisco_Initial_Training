#include "opencv\cv.h"
#include "opencv\highgui.h"

using namespace cv;
using namespace std;

char NameImage[500];

int main()
 {
	 Mat imagem = imread("image.jpg",1);
	 Mat gray; Mat canny;

	 vector<vector<Point>> contours; //cria um vetor de pontos

	 cvtColor(imagem, gray, CV_BGR2GRAY);

imagem.release();

	 Canny(gray, canny, 127, 255 , 3);

gray.release();

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
     }

     /// Draw polygonal contour + bonding rects
     Mat drawing = canny.clone();
	 cvtColor(drawing, drawing, CV_GRAY2BGR);
     for( int i = 0; i< contours.size(); i++ )
     {
         rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), Scalar(250,255,0), 2, 8, 0 );     

			Rect region = boundRect[i];
			Mat Image = drawing(region);

			sprintf(NameImage, "image%d", i);
			imshow(NameImage, Image);
			waitKey(50);
     }
	
	 imshow("Desenho", drawing);

canny.release();
drawing.release();

	 waitKey(0);
 }
