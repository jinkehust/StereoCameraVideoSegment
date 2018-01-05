#include "opencv2/objdetect/objdetect.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/imgproc/imgproc.hpp"  

#include <iostream>  
#include <stdio.h>  


using namespace cv;

using namespace std;



int main()

{


	VideoCapture camera0(0);

	//设置的分辨率不一定就是你想要设置的分辨率，还需要摄像头能够支持得了该分辨率。可以使用通用摄像头软件AMCAP2.EXE，
	//打开后在options里面有一项Video Capture Pin...，
	//点进去可以看到数据流格式中输出格式为一个下拉列表，里面的格式即为可以支持的分辨率大小。
	camera0.set(CV_CAP_PROP_FRAME_WIDTH, 1280);

	camera0.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

	if (!camera0.isOpened()) return 1;

	Mat frame00;
	camera0 >> frame00;




	waitKey(2000);   //预热

	while (1) {

		//grab and retrieve each frames of the video sequentially

		Mat frame0;

		camera0 >> frame0;



		imshow("Video1", frame0);
		waitKey(10);



	}



	return 0;

}
