#include <stdio.h>
#include <iostream>
#include "opencv2\core\core.hpp"
#include "opencv2\features2d\features2d.hpp"
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\nonfree\nonfree.hpp"
#include "opencv2\nonfree\features2d.hpp"
#include "opencv/cv.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace cv;
using namespace std;

FILE*fp;

void glcm(Mat img)
{

    float energy=0,contrast=0,homogenity=0;
	float IDM=0,entropy=0,mean1=0, dissimilarity=0;
	float ASM=0, correlation=0;
	float mean2=0, mean3=0, omegai=0, omegaj=0;
	float average = 0,variance = 0,S_entropy = 0;
    
	int row=img.rows,col=img.cols;
    
	Mat gl=Mat::zeros(256,256,CV_32FC1);
    
    //creating glcm matrix with 256 levels,radius=1 and in the horizontal direction
    for(int i=0;i<row;i++)
	{
        for(int j=0;j<col-1;j++)
		{
           // gl.at<float>(img.at<uchar>(i,j),img.at<uchar>(i,j+1))=gl.at<float>(img.at<uchar>(i,j),img.at<uchar>(i,j+1))+1;
			gl.at<float>(img.at<uchar>(i,j),img.at<uchar>(i,j+1))++;
		}
	}
    
	// normalizing glcm matrix for parameter determination
    gl=gl+gl.t(); // Soma a matriz original a sua transposta
    gl=gl/sum(gl)[0];
    
    
    for(int i=0;i<256;i++)
	{
        for(int j=0;j<256;j++)
		{
          
            contrast+=(i-j)*(i-j)*gl.at<float>(i,j);

            homogenity+=gl.at<float>(i,j)/(1+(i-j)*(i-j)); 

			dissimilarity+=gl.at<float>(i,j)*(abs(i-j));

			ASM=ASM+(gl.at<float>(i,j)*gl.at<float>(i,j));

			energy=energy+sqrt(ASM);

			if(i!=j){
                IDM=IDM+gl.at<float>(i,j)/((i-j)*(i-j)); //Taking k=2; // IDM no artigo o denominador é (1 + (i-j)^2)
			}
			if(gl.at<float>(i,j)!=0){
                entropy=entropy-gl.at<float>(i,j)*log10(gl.at<float>(i,j));
			}
			
			mean1+=i*gl.at<float>(i,j);
			mean2+=j*gl.at<float>(i,j);

			omegai+=sqrt(gl.at<float>(i,j)*(i-mean1)*(i-mean1));
			omegaj+=sqrt(gl.at<float>(i,j)*(j-mean2)*(j-mean2));
			if(omegai!=0 && omegaj!=0)
			{
				correlation+=((i*j)*(gl.at<float>(i,j)) - (mean1*mean2)) / (omegai * omegaj);
			}
			for(int k = 2;k < (2*256);k++)
			{
				if(j+i == k)
					average += (k)*(gl.at<float>(i,j));
			}

			for(int k = 2;k < (2*256);k++)
			{
				if(j+i == k){
					if(gl.at<float>(i,j)!=0)
						variance += (gl.at<float>(i,j))*log10(gl.at<float>(i,j));
				}
			}
			variance = (-1)*variance;

			for(int k = 2;k < (2*256);k++)
			{
				if(j+i == k){
						S_entropy += (pow(k - variance,2))*(gl.at<float>(i,j));
				}
			}

		}
	}
	//PRINTANDO OS RESULTADOS EM UM ARQUIVO
	fp =fopen("Resultado.txt","w");

	fprintf(fp,"Energy = %f",energy);
	fprintf(fp,"\nContrast = %f",contrast);
	fprintf(fp,"\nHomonenity = %f",homogenity);
	fprintf(fp,"\nIDM = %f",IDM);
	fprintf(fp,"\nEntropy = %f",entropy);
	fprintf(fp,"\nAngularSecondMoment = %f",dissimilarity);
	fprintf(fp,"\nCorrelation = %f",ASM);
	fprintf(fp,"\nSumAvagere = %f",average);
	fprintf(fp,"\nSumVariance = %f",variance);
	fprintf(fp,"\nSumEntropy = %f",S_entropy);

	fclose(fp);

	printf("\t\t\tRESULTADO\n");

	printf("Energy = %f",energy);
	printf("\nContrast = %f",contrast);
	printf("\nHomonenity = %f",homogenity);
	printf("\nIDM = %f",IDM);
	printf("\nEntropy = %f",entropy);
	printf("\nAngularSecondMoment = %f",dissimilarity);
	printf("\nCorrelation = %f",ASM);
	printf("\nSumAvagere = %f",average);
	printf("\nSumVariance = %f",variance);
	printf("\nSumEntropy = %f",S_entropy);
}

int main()
{
      
	Mat entrada=imread("Iron_Man.jpg",1);
    Mat gray;
	cvtColor(entrada, gray, CV_RGB2GRAY);
    imshow("Image", gray);        
	glcm(gray);

	cvWaitKey(0);
}
