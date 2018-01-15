#include<opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
#include<iostream>  
#include<fstream>  
#include<cstring> 
#include <sstream>
#include <string>

#define IMAGE_LIST_FILE "C:\\Users\\Administrator\\Desktop\\project\\_3Dmeasurement\\source_photos\\inputimage.txt"  
using namespace cv;
using namespace std;
string int2str(int num)
{
	if (num == 0)
		return " 0 ";

	string str = "";
	int num_ = num > 0 ? num : -1 * num;

	while (num_)
	{
		str = (char)(num_ % 10 + 48) + str;
		num_ /= 10;
	}

	if (num < 0)
		str = " - " + str;

	return str;
}

int main()
{
	ifstream inFile;
	string  src, dst1, dst2;
	string save_path_L = "C:\\Users\\Administrator\\Desktop\\project\\_3Dmeasurement\\bino_camera_photos\\left\\";
	string save_path_R = "C:\\Users\\Administrator\\Desktop\\project\\_3Dmeasurement\\bino_camera_photos\\right\\";
	Mat images;
	int n = 0;
	Rect rect_left(1280, 0, 1280, 720);
	Rect rect_right(0, 0, 1280, 720);


	inFile.open(IMAGE_LIST_FILE);
	//按行处理路径  
	getline(inFile, src);
	cout << src << endl;
	while (inFile.good())
	{
		//C++路径名默认为'\\',故在每一个'\'后再插入一个'\'  
		int t = src.find('\\', 0);
		while (t != string::npos)
		{
			src = src.insert(t + 1, 1, '\\');
			cout << src << endl;
			t = src.find('\\', t + 2);
		}

		images = imread(src);
		Mat image_copy1, image_copy2, frame_l, frame_r;
		image_copy1 = Mat(images, rect_left);
		frame_l = image_copy1.clone();
		image_copy2 = Mat(images, rect_right);
		frame_r = image_copy2.clone();
		//imshow("left", frame_l);
		//imshow("right", frame_r);		

		//指定批处理后的保存路径  
		//int t2 = src.find(str, 0);
		//dst = src.erase(t2, strlen(str));
		//dst = dst.insert(t2, str2);
		n = n + 1;
		dst1 = save_path_L + int2str(n) + ".jpg";
		dst2 = save_path_R + int2str(n) + ".jpg";
		imwrite(dst1, frame_l);
		imwrite(dst2, frame_r);
		getline(inFile, src);
	}
	
	inFile.close();
	return 0;
}
