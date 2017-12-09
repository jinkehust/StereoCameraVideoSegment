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

	//camera0.set(CV_CAP_PROP_FRAME_WIDTH, 1280);

	//camera0.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

	Rect rect_left(320, 0, 320, 240);
	Rect rect_right(0, 0, 320, 240);


	if (!camera0.isOpened()) return 1;

	//if (!camera1.isOpened()) return 1;


	Mat frame00;
	camera0 >> frame00;




	waitKey(5000);

	while (1) {

		//grab and retrieve each frames of the video sequentially

		Mat frame0;

		camera0 >> frame0;

		//Mat frame1;

		//camera1 >> frame1;

		/*		if (t==0)
		{
		Size s = frame0.size();
		cout << "height=" << s.height << endl;
		cout << "width=" << s.width << endl;
		t = 1;
		}  */

		//imshow("theall", frame0);

		Mat image_copy1, image_copy2, frame_l, frame_r;
		image_copy1 = Mat(frame0, rect_left);
		frame_l = image_copy1.clone();
		image_copy2 = Mat(frame0, rect_right);
		frame_r = image_copy2.clone();
		imshow("left", frame_l);
		imshow("right", frame_r);

		//imshow("Video1", frame1);

		//      std::cout << frame1.rows() << std::endl;


		waitKey(10);



	}



	return 0;

}
