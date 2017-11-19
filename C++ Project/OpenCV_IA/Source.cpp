//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <iostream>
//#include <stdlib.h>
//#include <stdio.h>
//
//using namespace cv;
//using namespace std;
//
///// Global variables
//
//Mat image, greyImage, smallImage;
//Mat dst, detected_edges;
//
//int edgeThresh = 1;
//int lowThreshold;
//int const max_lowThreshold = 100;
//int ratio = 3;
//int kernel_size = 3;
//char* window_name = "Edge Map";
//
//
///**
//* @function CannyThreshold
//* @brief Trackbar callback - Canny thresholds input with a ratio 1:3
//*/
//void CannyThreshold(int, void*)
//{
//	/// Reduce noise with a kernel 3x3
//	blur(greyImage, detected_edges, Size(3, 3));
//
//	/// Canny detector
//	Canny(detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size);
//
//	/// Using Canny's output as a mask, we display our result
//	dst = Scalar::all(0);
//
//
//	image.copyTo(dst, detected_edges);
//
//	resize(dst, smallImage, cv::Size(64,64));
//	imshow(window_name, dst);
//	imshow("small image window", smallImage);
//}
//
//
//int main() {
//	//VideoCapture stream1(0);   //0 is the id of video device.0 if you have only one camera.
//
//	//if (!stream1.isOpened()) { //check if video device has been initialised
//	//	cout << "cannot open camera";
//	//}
//
//	//get webCam and grayscale
//	//Mat greyMat, cameraFrame;
//	//while (true) 
//	//{
//	//	stream1.read(cameraFrame);
//	//	imshow("cam", cameraFrame);
//	//	if (waitKey(30) >= 0)
//	//	{
//	//		cvtColor(cameraFrame, greyMat, CV_BGR2GRAY);
//	//		break;
//	//	}
//	//}
//	//while (true)
//	//{
//	//	imshow("Grey image", greyMat); 
//	//	if (waitKey(30) >= 0)
//	//	{
//	//		break;
//	//	}
//	//}
//
//	image = imread("./Resources/Geometry.png", CV_LOAD_IMAGE_COLOR);// Read the file
//
//	if (!image.data)// Check for invalid input
//	{
//		cout << "Could not open or find the image" << std::endl;
//		return -1;
//	}
//	/// Create a matrix of the same type and size as src (for dst)
//	dst.create(image.size(), image.type());
//
//	/// Convert the image to grayscale
//	cvtColor(image, greyImage, CV_BGR2GRAY);
//
//	/// Create a window
//	namedWindow(window_name, CV_WINDOW_AUTOSIZE);
//
//
//	namedWindow("small image window", CV_WINDOW_AUTOSIZE);
//
//	/// Create a Trackbar for user to enter threshold
//	createTrackbar("Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold);
//
//	/// Show the image
//	CannyThreshold(0, 0);
//
//	/// Wait until user exit program by pressing a key
//	waitKey(0);
//
//	return 0;
//}