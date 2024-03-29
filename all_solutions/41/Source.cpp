#include <iostream>
using namespace std;

#if (defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__) || (defined(__APPLE__) & defined(__MACH__)))
#include <opencv\cv.h>
#include <opencv\highgui.h>
#else
#include <opencv/cv.h>
#include <opencv/highgui.h>
#endif

#include <cvblob.h>
using namespace cvb;

#pragma region funcao_blob
void printBlobProperty(CvBlob *it, CvContourPolygon *sPolygon)
{
    double moment00 = it->m00;
    double moment10 = it->m10;
    double moment01 = it->m01;
    double moment11 = it->m11;
    double moment20 = it->m20;
    double moment02 = it->m02;
    
    double area = it->area;
    double perimetro = cvContourPolygonPerimeter(sPolygon);
    double circularidade = cvContourPolygonCircularity(sPolygon);
    double angulo = cvAngle(it);
    
    unsigned int minx = it->minx;; ///< X min.
    unsigned int maxx = it->maxx;; ///< X max.
    unsigned int miny = it->miny;; ///< Y min.
    unsigned int maxy = it->maxy;; ///< y max.
    
    double centralMoment11 = it->u11; ///< Central moment 11.
    double centralMoment20 = it->u20; ///< Central moment 20.
    double centralMoment02 = it->u02; ///< Central moment 02.
    
    double NormalizedCentralMoment11 = it->n11; ///< Normalized central moment 11.
    double NormalizedCentralMoment20 = it->n20; ///< Normalized central moment 20.
    double NormalizedCentralMoment02 = it->n02; ///< Normalized central moment 02.
    
    double HuMoment1 = it->p1; ///< Hu moment 1.
    double HuMoment2 = it->p2; ///< Hu moment 2.
    
    CvPoint2D64f centroid = it->centroid;
    
  
    //centroid.y;
    
    printf("\n\nMomentos\n\n");
    printf("moment00\t-\t%f\n",(float)moment00);
    printf("moment10\t-\t%f\n",(float)moment10);
    printf("moment01\t-\t%f\n",(float)moment01);
    printf("moment11\t-\t%f\n",(float)moment11);
    printf("moment20\t-\t%f\n",(float)moment20);
    printf("moment02\t-\t%f\n",(float)moment02);
    
    printf("\n\nMomentos 2a ordem\n\n");
    printf("centralMoment11\t-\t%f\n",(float)centralMoment11);
    printf("centralMoment20\t-\t%f\n",(float)centralMoment20);
    printf("centralMoment02\t-\t%f\n",(float)centralMoment02);
    printf("NormalizedCentralMoment11\t-\t%f\n",(float)NormalizedCentralMoment11);
    printf("NormalizedCentralMoment20\t-\t%f\n",(float)NormalizedCentralMoment20);
    printf("NormalizedCentralMoment02\t-\t%f\n",(float)NormalizedCentralMoment02);
    
    printf("\n\nMomentos de HU\n\n");
    printf("HuMoment1\t-\t%f\n",(float)HuMoment1);
    printf("HuMoment2\t-\t%f\n",(float)HuMoment2);/**/
    
    printf("\n\nContorno\n\n");
    printf("Centroide\t-\t%d,%d\n",(int)centroid.x, (int)centroid.y);
    printf("area\t-\t%f\n",(float)area);
    printf("perimetro\t-\t%f\n",(float)perimetro);
    printf("circularidade\t-\t%f\n",(float)circularidade);
    printf("angulo\t-\t%f\n",(float)angulo);
    printf("diferenca em X\t-\t%d\n",(int)(maxx-minx));
    printf("diferenca em Y\t-\t%d\n",(int)(maxy-miny));
    
    
}
CvMemStorage *storageline = cvCreateMemStorage(0);
CvSeq *lines = 0;
CvMemStorage* storage = cvCreateMemStorage(0);
CvSeq* contour = NULL;
CvRect rec;
CvPoint P1,P2,pontos;
int control=0;
#pragma endregion funcao_blob

int main()
{
	IplImage *color = cvLoadImage("image.jpg", 1);
	
	IplImage *gray = cvCreateImage(cvGetSize(color),8,1);

	IplImage *thresholded = cvCreateImage(cvGetSize(color), 8, 1);
	
	cvCvtColor(color,gray,CV_RGB2GRAY);
	cvCanny(gray,gray, 127, 255, 3);
	cvThreshold(gray,thresholded,127,255,CV_THRESH_BINARY);

  //Cria��o da estrutura blob e processamento dos dados

  IplImage *labelImg = cvCreateImage(cvGetSize(thresholded),IPL_DEPTH_LABEL,1);

  CvBlobs blobs; //Cria��o da estrutura blob
 
  unsigned int result = cvLabel(thresholded, labelImg, blobs);
           
	cvFilterByArea(blobs,1,10000); //filtrar a area para pegar os contornos. Ex usado: s� pega os contornos de area 1 at� 10000
  
	printf("\n\n%d contornos", blobs.size()); //blobs.size() = total de contornos detectados

	cvShowImage("Imagem_ENTRADA", color);

  cvReleaseImage(&gray);
  cvReleaseImage(&labelImg);
  
  cvReleaseBlobs(blobs);

  cvWaitKey(0);
}