#include <iostream>
#include<math.h>
#include<time.h>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include <opencv2/imgproc/types_c.h>


using namespace std;
using namespace cv;

unsigned char source[120][188];
unsigned char image_buffer[120][188];

const Point neighbors[8] = { { 0, 1 }, { 1, 1 }, { 1, 0 }, { 1, -1 }, 
                             { 0, -1 }, { -1, -1 }, { -1, 0 }, {-1, 1} };

const Point directions[8] = { { 0, 1 }, {1,1}, { 1, 0 }, { 1, -1 }, 
							  { 0, -1 },  { -1, -1 }, { -1, 0 },{ -1, 1 } };
 
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

	RNG rng(time(0));

    // Mat img = imread("chen.jepg");

	// VideoCapture cap = VideoCapture("VID_20230426_170649.mp4");

	// if (!cap.isOpened())
	// {
	// 	cout << "摄像头打开失败" << endl;
	// }
	// else
	// {
	// 	cout << "摄像头打开成功" << endl;
	// }

	// Mat img1;//构建一个对象
	// int index = 0;
	// while (true) 
	// {	
	// 		cap >> img1;//将视频进行拆分，流向图片
	// 		if (img1.empty()) //如果img为空说明流完了
	// 		{
	// 			break;
	// 		}
	// 	namedWindow("图片");
	// 	resizeWindow("图片",800,800);
	// 	imshow("图片",img1);//把每一次的图片显示出来
	// }
	
 	Mat img = imread("无边框.jpg",IMREAD_GRAYSCALE);


	// flip(img,img, 1);  //水平翻转

    Mat gray_img;

	// cout << "Width : " << img.size().width << endl;
	// cout << "Height: " << img.size().height << endl;

	// img = img(Range(0,2667), Range(0,4000));
	resize(img,gray_img,Size(188, 120),0,0);

	namedWindow("img",0);
	resizeWindow("img", 600, 600);
	imshow("img", img);

	cout << "Width : " << gray_img.size().width << endl;
	cout << "Height: " << gray_img.size().height << endl;

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
		//  cout << "第" << r+1 << "行的灰度值为：" << endl;
		for (int c = 0; c < gray_img.cols; c++)
		{
			source[r][c] = (int)gray_img.at<uchar>(r,c);
			// cout << (int)gray_img.at<uchar>(r,c);
			// if(source[r][c]>=100)
			// {
			// 	source[r][c]=255;
			// }
			// else 
			// {
			// 	source[r][c] = 0;
			// }
			// gray_img.at<uchar>(r,c)=source[r][c];
			// cout << grayValue<<" ";
		}
		// cout << endl << endl;
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
			// cout <<" ";
		}
		// cout << endl << endl;
	}
	namedWindow("sobel",0);
	resizeWindow("sobel", 600, 600);
	imshow("sobel", gray_img);

	#if 1       //八领域

	vector<Point> edge_t;
	vector<vector<Point>> edges;
 
	// 边缘跟踪
	int i, j, counts = 0, curr_d = 0;
	for (i = 1; i < gray_img.rows - 1; i++)
		for (j = 1; j < gray_img.cols - 1; j++)
		{
			// 起始点及当前点
			//Point s_pt = Point(i, j);
			Point b_pt = Point(i, j);
			Point c_pt = Point(i, j);
			

			// 如果当前点为前景点
			if (255 == gray_img.at<uchar>(c_pt.x, c_pt.y))
			{
				edge_t.clear();
				bool tra_flag = false;
				// 存入
				edge_t.push_back(c_pt);
				gray_img.at<uchar>(c_pt.x, c_pt.y) = 0;    // 用过的点直接给设置为0
 
				// 进行跟踪
				while (!tra_flag)
				{			
					// 循环八次
					for (counts = 0; counts < 8; counts++)
					{
						// 防止索引出界
						if (curr_d >= 8)
						{
							curr_d -= 8;
						}
						if (curr_d < 0)
						{
							curr_d += 8;
						}
 
						// 当前点坐标
						// 跟踪的过程，应该是个连续的过程，需要不停的更新搜索的root点
						c_pt = Point(b_pt.x + directions[curr_d].x, b_pt.y + directions[curr_d].y);
 
						// 边界判断
						if ((c_pt.x > 0) && (c_pt.x < gray_img.rows - 1) &&
							(c_pt.y > 0) && (c_pt.y < gray_img.cols - 1))
						{
							// 如果存在边缘
							if (255 == gray_img.at<uchar>(c_pt.x, c_pt.y))
							{
								int x = c_pt.x,y = c_pt.y;
								printf("(%d),",curr_d);
								curr_d -= 2;   // 更新当前方向
								edge_t.push_back(c_pt);
								gray_img.at<uchar>(c_pt.x, c_pt.y) = 0;
 
								// 更新b_pt:跟踪的root点
								b_pt.x = c_pt.x;
								b_pt.y = c_pt.y;
								// cout << c_pt.x << " " << c_pt.y << endl;
 
								break;   // 跳出for循环
							}
						}
						curr_d++;
					}   // end for
					// 跟踪的终止条件：如果8邻域都不存在边缘
					if (8 == counts )
					{
						// 清零
						curr_d = 0;
						tra_flag = true;
						edges.push_back(edge_t);
						printf("\n");
						break;
					}
 
				}  // end if
			}  // end while
			
		}

		
 
	// 显示一下
	Mat trace_edge = Mat::zeros(gray_img.rows, gray_img.cols, CV_8UC1);
	Mat trace_edge_color;
	cvtColor(trace_edge, trace_edge_color, CV_GRAY2BGR);
	for (i = 0; i < edges.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
 
		//cout << edges[i].size() << endl;
		// 过滤掉较小的边缘
		if (edges[i].size() > 50)
		{
			for (j = 0; j < edges[i].size(); j++)
			{
				trace_edge_color.at<Vec3b>(edges[i][j].x, edges[i][j].y)[0] = 0;
				trace_edge_color.at<Vec3b>(edges[i][j].x, edges[i][j].y)[1] = 0;
				trace_edge_color.at<Vec3b>(edges[i][j].x, edges[i][j].y)[2] = 255;
				// printf("(%d %d),",edges[i][j].x, edges[i][j].y);
			}
		}
		
	}

	#endif

	#if 0    //区域生长

	vector<Point> seeds;
	vector<Point> contour;
	vector<vector<Point>> contours;
 
	int i, j, k;
	for (i = 0; i < gray_img.rows; i++)
		for (j = 0; j < gray_img.cols; j++)
		{
			Point c_pt = Point(i, j);
 
			//如果当前点为轮廓点
			if (gray_img.at<uchar>(c_pt.x, c_pt.y) == 255)
			{
 
				contour.clear();
				// 当前点清零
				gray_img.at<uchar>(c_pt.x, c_pt.y) = 0;
 
				// 存入种子点及轮廓
				seeds.push_back(c_pt);
				contour.push_back(c_pt);

				int start_row = i,start_col = j;
				int end_row = i,end_col = j;
				int cout = 0;

				// 区域生长
				while (seeds.size() > 0)
				{
					// 遍历8邻域
					for (k = 0; k < 8; k++)
					{	
						// 更新当前点坐标
						c_pt.x = seeds[0].x + neighbors[k].x;
						c_pt.y = seeds[0].y + neighbors[k].y;
 
						// 边界界定
						if ((c_pt.x >= 0)  && (c_pt.x <= gray_img.rows - 1) &&
							(c_pt.y >= 0) && (c_pt.y <= gray_img.cols - 1))
						{
							if (gray_img.at<uchar>(c_pt.x, c_pt.y) == 255)
							{
								// 当前点清零
								gray_img.at<uchar>(c_pt.x, c_pt.y) = 0;
 
								// 存入种子点及轮廓
								seeds.push_back(c_pt);
								contour.push_back(c_pt);
								int x = c_pt.x,y = c_pt.y;
								printf("(%d %d %d), ",x,y,k);
								// cout << x << " "; 
								// cout << y << " ";

								// cout++;
								// end_row = c_pt.x,end_col = c_pt.y;
								// break;
							}// end if		
						}										
					} // end for
 
					// 删除第一个元素
					seeds.erase(seeds.begin());
					
				}
				// end while
				// cout << endl << endl;
				printf("\n");
				// if(abs(start_row-end_row)<=2&&abs(start_col-end_col)<=2)
				contours.push_back(contour);
 
			}// end if
		}
 
 
	// 显示一下  
	Mat trace_edge = Mat::zeros(gray_img.rows, gray_img.cols, CV_8UC1);
	Mat trace_edge_color;
	cvtColor(trace_edge, trace_edge_color, CV_GRAY2BGR	);
	for (i = 0; i < contours.size(); i++)
	{
		// Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		Scalar color = Scalar(0, 0, 255);
 
		//cout << edges[i].size() << endl;  
		// 过滤掉较小的边缘  
		if (contours[i].size() > 50)
		{
			for (j = 0; j < contours[i].size(); j++)
			{
				trace_edge_color.at<Vec3b>(contours[i][j].x, contours[i][j].y)[0] = color[0];
				trace_edge_color.at<Vec3b>(contours[i][j].x, contours[i][j].y)[1] = color[1];
				trace_edge_color.at<Vec3b>(contours[i][j].x, contours[i][j].y)[2] = color[2];
			}
		}
	}
	#endif

	namedWindow("XY",0);
	resizeWindow("XY", 600, 600);
	imshow("XY", trace_edge_color);
	cout << "Width : " << trace_edge_color.size().width << endl;
	cout << "Height: " << trace_edge_color.size().height << endl;
	// printf("%d",)
	// }
	waitKey(0);
	return 0;

}
