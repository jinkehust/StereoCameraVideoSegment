
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace cv;
using namespace std;

Point Center_cal(vector<vector<Point> > contours, int i)
{
	int centerx = 0, centery = 0, n = contours[i].size();
	centerx = (contours[i][n / 4].x + contours[i][n * 2 / 4].x + contours[i][3 * n / 4].x + contours[i][n - 1].x) / 4;
	centery = (contours[i][n / 4].y + contours[i][n * 2 / 4].y + contours[i][3 * n / 4].y + contours[i][n - 1].y) / 4;
	Point point1 = Point(centerx, centery);
	return point1;
}

void QR_detect(Mat src)
{
	resize(src, src, Size(800, 600));//标准大小
	Mat src_gray;
	Mat src_all = src.clone();
	Mat threshold_output;
	vector<vector<Point> > contours, contours2;
	vector<Vec4i> hierarchy;
	//预处理
	cvtColor(src, src_gray, CV_BGR2GRAY);
	blur(src_gray, src_gray, Size(3, 3)); //模糊，去除毛刺
	threshold(src_gray, threshold_output, 100, 255, THRESH_OTSU);
	//寻找轮廓 
	//第一个参数是输入图像 2值化的
	//第二个参数是内存存储器，FindContours找到的轮廓放到内存里面。
	//第三个参数是层级，**[Next, Previous, First_Child, Parent]** 的vector
	//第四个参数是类型，采用树结构
	//第五个参数是节点拟合模式，这里是全部寻找
	findContours(threshold_output, contours, hierarchy, CV_RETR_TREE, CHAIN_APPROX_NONE, Point(0, 0));
	//轮廓筛选
	int c = 0, ic = 0, area = 0;
	int parentIdx = -1;
	for (int i = 0; i< contours.size(); i++)
	{
		//hierarchy[i][2] != -1 表示不是最外面的轮廓
		if (hierarchy[i][2] != -1 && ic == 0)
		{
			parentIdx = i;
			ic++;
		}
		else if (hierarchy[i][2] != -1)
		{
			ic++;
		}
		//最外面的清0
		else if (hierarchy[i][2] == -1)
		{
			ic = 0;
			parentIdx = -1;
		}
		//找到定位点信息
		if (ic >= 2)
		{
			contours2.push_back(contours[parentIdx]);
			ic = 0;
			parentIdx = -1;
		}
	}
	//填充定位点
	for (int i = 0; i<contours2.size(); i++)
		drawContours(src_all, contours2, i, CV_RGB(0, 255, 0), -1);
	//连接定位点
	Point point[3];
	for (int i = 0; i<contours2.size(); i++)
	{
		point[i] = Center_cal(contours2, i);
	}
	if (point[0].x>10 && point[1].x>10 && point[2].x > 10)
	{
		line(src_all, point[0], point[1], Scalar(0, 0, 255), 2);
		line(src_all, point[1], point[2], Scalar(0, 0, 255), 2);
		line(src_all, point[0], point[2], Scalar(0, 0, 255), 2);
	}
		imshow("结果", src_all);
	
	//cout << "二维码中心坐标为"<<
}

int main()
{
	VideoCapture camera(0);
	Mat frame0;
	if (!camera.isOpened()) return 1;
	while (1) {

		//grab and retrieve each frames of the video sequentially

		

		camera >> frame0;
		QR_detect(frame0);

		waitKey(100);



	}



	return 0;

}
