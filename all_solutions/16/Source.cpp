#include "opencv\cv.h"
#include "opencv\highgui.h"

using namespace cv;
using namespace std;

Mat Criar_Hist(Mat image)
{
	int x,y;
	int vec[256];
	int aux=0;
	
	for(x=0;x<256;x++)
	{
		vec[x]=0;
	}

	for(y=0;y<image.rows;y++)
	{
		for(x=0;x<image.cols;x++)
		{
			aux++;
			vec[image.at<uchar>(y,x)]++;
		}
	}
	
	for(x=0;x<256;x++)
	{
		vec[x]=((2000*vec[x])/aux);
	}

	Mat hist(100,256,CV_8UC1);

	for(y=0;y<hist.rows;y++)
	{
		for(x=0;x<hist.cols;x++)
		{
			if(y>=hist.rows-vec[x])
				hist.at<uchar>(y,x)=0;

			else
				hist.at<uchar>(y,x)=255;
		}
	}
	return hist;
}


int main()
 {
	 Mat imagem = imread("paisagem.jpg",1);
	 Mat gray; Mat hist_gray; Mat hist_equal; Mat equal;

	 cvtColor(imagem, gray, CV_BGR2GRAY);
	 imshow("Gray", gray);
	 imwrite("Img_gray.jpg",gray);

	 equalizeHist(gray, equal);
	 imshow("Img_Equal", equal);
	 imwrite("Img_Equal.jpg",equal);

	 hist_gray = Criar_Hist(gray);
	 hist_equal = Criar_Hist(equal);

	 imshow("Hist_gray",hist_gray);
	 imwrite("Hist_gray.jpg",hist_gray);

	 imshow("Hist_equal",hist_equal);
	 imwrite("Hist_equal.jpg",hist_equal);

	 waitKey(0);
 }
