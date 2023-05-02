#include <iostream>
#include<math.h>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"

using namespace std;
using namespace cv;

unsigned char source[120][188];
unsigned char image_buffer[120][188];
 
void LeadToEdge(void)
{
    int w = 188;
    int h = 120;
	int gx = 0,gy = 0,tempx=0,tempy=0,temp;
 
    for(int i = 1; i< h; i++){
   //卷积操作
        for(int j = 1; j < w; j++){
            gx = (-source[i-1][j-1])
				+(-2*source[i][j-1])
				+(- source[i+1][j-1])
				+( source[i-1][j+1])
				+(2*source[i][j+1])
				+(source[i+1][j+1]);

			gy = (source[i+1][j-1])
				+(2*source[i+1][j])
				+( source[i+1][j+1])
				+( -source[i-1][j-1])
				+(-2*source[i-1][j])
				+(-source[i-1][j+1]);

			temp = abs(gx) + abs(gy);

			if(temp>255)
			{
				image_buffer[i][j] = 255;
			}
			else
			{
				image_buffer[i][j] = 0;
			}

            // double G = sqrt(Gx*Gx+Gy*Gy);
 
            // QRgb pixel;
            // if(G>Gmax)
            //   pixel = qRgb(255,255,255);
            // else
            //   pixel = qRgb(0,0,0);
            // Edge.setPixel(j,i,pixel);
        }
    }
}

int main(int argc ,char *argv[])
{
    //  Mat img = imread("chen.jepg");
    Mat img = imread("IMG_20230417_211227.jpg",IMREAD_GRAYSCALE);
    Mat gray_img;

	// cout << "Width : " << img.size().width << endl;
	// cout << "Height: " << img.size().height << endl;

	img = img(Range(0,2667), Range(0,4000));
	resize(img,gray_img,Size(188, 120),0,0);

	cout << "Width : " << gray_img.size().width << endl;
	cout << "Height: " << gray_img.size().height << endl;


	Mat resultX, resultY, resultXY;
	//-------------Sobel边缘检测--------------
	//X方向一阶边缘
	Sobel(gray_img, resultX, CV_16S, 2, 0, 1);
	convertScaleAbs(resultX, resultX); 

	//Y方向一阶边缘
	Sobel(gray_img, resultY, CV_16S, 0, 1, 3);
	convertScaleAbs(resultY, resultY);

	//整幅图像的一阶边缘
	resultXY = resultX + resultY;

	//显示图像
	// namedWindow("resultX",0);
	// resizeWindow("resultX", 300, 300);
	// imshow("resultX", resultX);
	// namedWindow("resultY",0);
	// resizeWindow("resultY", 300, 300);
	// imshow("resultY", resultY);
	namedWindow("sobel",0);
	resizeWindow("sobel", 1000, 1000);
	imshow("sobel", resultXY);

	// namedWindow("img",0);
	// resizeWindow("img", 300, 300);
	// imshow("img", gray_img);

	// namedWindow("img1",0);
	// resizeWindow("img1", 300, 300);
	// imshow("img1", cropped_image);
	
	// cvtColor(img, gray_img, 120);

	#if 0  //庫自帶函數處理Sobel算子

	Mat resultX, resultY, resultXY;
	//-------------Sobel边缘检测--------------
	//X方向一阶边缘
	Sobel(gray_img, resultX, CV_16S, 2, 0, 1);
	convertScaleAbs(resultX, resultX); 

	//Y方向一阶边缘
	Sobel(gray_img, resultY, CV_16S, 0, 1, 3);
	convertScaleAbs(resultY, resultY);

	//整幅图像的一阶边缘
	resultXY = resultX + resultY;

	//显示图像
	// namedWindow("resultX",0);
	// resizeWindow("resultX", 300, 300);
	// imshow("resultX", resultX);
	// namedWindow("resultY",0);
	// resizeWindow("resultY", 300, 300);
	// imshow("resultY", resultY);
	namedWindow("resultXY",0);
	resizeWindow("resultXY", 1000, 1000);
	imshow("resultXY", resultXY);
	int grayValue;
	for (int r = 0; r < resultXY.rows; r++)
	{
		 cout << "第" << r+1 << "行的灰度值为：" << endl;
		for (int c = 0; c < resultXY.cols; c++)
		{
			source[r][c] = (int)resultXY.at<uchar>(r,c);
			cout << (int)resultXY.at<uchar>(r,c);
			if(source[r][c]>=100)
			{
				source[r][c]=255;
			}
			else 
			{
				source[r][c] = 0;
			}
			resultXY.at<uchar>(r,c)=source[r][c];
			cout << grayValue<<" ";
		}
		cout << endl << endl;
	}

	#endif
	for (int r = 0; r < gray_img.rows; r++)
	{
		 cout << "第" << r+1 << "行的灰度值为：" << endl;
		for (int c = 0; c < gray_img.cols; c++)
		{
			source[r][c] = (int)gray_img.at<uchar>(r,c);
			cout << (int)gray_img.at<uchar>(r,c);
			// if(source[r][c]>=100)
			// {
			// 	source[r][c]=255;
			// }
			// else 
			// {
			// 	source[r][c] = 0;
			// }
			// gray_img.at<uchar>(r,c)=source[r][c];
			cout <<" ";
		}
		cout << endl << endl;
	}
	LeadToEdge();
		for (int r = 0; r < gray_img.rows; r++)
	{
		// cout << "第" << r+1 << "行的灰度值为：" << endl;
		for (int c = 0; c < gray_img.cols; c++)
		{
			// source[r][c] = (int)gray_img.at<uchar>(r,c);
			// cout << (int)gray_img.at<uchar>(r,c);
			// if(source[r][c]>=100)
			// {
			// 	source[r][c]=255;
			// }
			// else 
			// {
			// 	source[r][c] = 0;
			// }
			gray_img.at<uchar>(r,c)=image_buffer[r][c];
		    // cout << (int)gray_img.at<uchar>(r,c);
			// cout << grayValue<<" ";
		}
		// cout << endl << endl;
	}
	// cout << "Width : " << gray_img.size().width << endl;
	// cout << "Height: " << gray_img.size().height << endl;
	namedWindow("XY",0);
	resizeWindow("XY", 1000, 1000);
	imshow("XY", gray_img);
	// printf("%d",)
	waitKey(0);
	return 0;

}
