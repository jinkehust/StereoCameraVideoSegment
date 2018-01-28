#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/opencv.hpp>
#include <iostream>  
#include <string>  
#include <vector>  

using namespace std;
using namespace cv;

int main()
{
	//load xml
	Mat intrinsic_matrix_loaded, distortion_coeffs_loaded;

	FileStorage fs("intrinsics.xml", FileStorage::READ);
	fs["intrinsics"] >> intrinsic_matrix_loaded;

	FileStorage fs1("distortion.xml", FileStorage::READ);
	fs1["distortion"] >> distortion_coeffs_loaded;

	cout << "\nintrinsic matrix:" << intrinsic_matrix_loaded << endl;
	cout << "\ndistortion coefficients: " << distortion_coeffs_loaded << endl;

	//undistortion
	Mat InputImage, OutputImage;
	InputImage = imread("image.jpg");
	undistort(InputImage, OutputImage, intrinsic_matrix_loaded, distortion_coeffs_loaded);
	imshow("原图片", InputImage);
	imshow("校正后的图片", OutputImage);

	waitKey();
	return 0;
}
