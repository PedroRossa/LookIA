//#include "opencv2/imgproc.hpp"
//#include "opencv2/highgui.hpp"
//#include <Windows.h>
//#include <iostream>
//
//using namespace std;
//using namespace cv;
//
//int xMin = 0;
//int yMin = 0;
//int xMax = 480;
//int yMax = 320;
//
//bool cropSaved = false;
//
///// Global variables
//
//int threshold_value = 150;
//int threshold_type = 0;;
//int const max_value = 255;
//int const max_type = 4;
//int const max_BINARY_value = 255;
//
//Mat croppedImage, croppedImage_grey, dst, smallImage;
//char* window_name = "Threshold Demo";
//
//char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
//char* trackbar_value = "Value";
//
///**
//* @function Threshold_Demo
//*/
//void Threshold_Demo(int, void*)
//{
//	/* 0: Binary
//	1: Binary Inverted
//	2: Threshold Truncated
//	3: Threshold to Zero
//	4: Threshold to Zero Inverted
//	*/
//
//	threshold(croppedImage_grey, dst, threshold_value, max_BINARY_value, threshold_type);
//
//	imshow("Croped", dst);
//
//
//	resize(dst, smallImage, cv::Size(), 0.15, 0.15, 0);
//	imshow("Small", smallImage);
//}
//
//Mat hwnd2mat(HWND hwnd)
//{
//	HDC hwindowDC, hwindowCompatibleDC;
//
//	int height, width, srcheight, srcwidth;
//	HBITMAP hbwindow;
//	Mat src;
//	BITMAPINFOHEADER  bi;
//
//	hwindowDC = GetDC(hwnd);
//	hwindowCompatibleDC = CreateCompatibleDC(hwindowDC);
//	SetStretchBltMode(hwindowCompatibleDC, COLORONCOLOR);
//
//	RECT windowsize;    // get the height and width of the screen
//	GetClientRect(hwnd, &windowsize);
//
//	//TODO: DIVIDI TUDO POR 2 AQUI
//	srcheight = windowsize.bottom;
//	srcwidth = windowsize.right;
//	height = windowsize.bottom;  //change this to whatever size you want to resize to
//	width = windowsize.right;
//
//
//	//srcheight = 320;
//	//srcwidth = 480;
//	//height = 320;  //change this to whatever size you want to resize to
//	//width = 480;
//
//	src.create(height, width, CV_8UC4);
//
//	// create a bitmap
//	hbwindow = CreateCompatibleBitmap(hwindowDC, width, height);
//	bi.biSize = sizeof(BITMAPINFOHEADER);    //http://msdn.microsoft.com/en-us/library/windows/window/dd183402%28v=vs.85%29.aspx
//	bi.biWidth = width;
//	bi.biHeight = -height;  //this is the line that makes it draw upside down or not
//	bi.biPlanes = 1;
//	bi.biBitCount = 32;
//	bi.biCompression = BI_RGB;
//	bi.biSizeImage = 0;
//	bi.biXPelsPerMeter = 0;
//	bi.biYPelsPerMeter = 0;
//	bi.biClrUsed = 0;
//	bi.biClrImportant = 0;
//
//	// use the previously created device context with the bitmap
//	SelectObject(hwindowCompatibleDC, hbwindow);
//	// copy from the window device context to the bitmap device context
//	StretchBlt(hwindowCompatibleDC, 0, 0, width, height, hwindowDC, 0, 0, srcwidth, srcheight, SRCCOPY); //change SRCCOPY to NOTSRCCOPY for wacky colors !
//	GetDIBits(hwindowCompatibleDC, hbwindow, 0, height, src.data, (BITMAPINFO *)&bi, DIB_RGB_COLORS);  //copy from hwindowCompatibleDC to hbwindow
//
//																									   // avoid memory leak
//	DeleteObject(hbwindow);
//	DeleteDC(hwindowCompatibleDC);
//	ReleaseDC(hwnd, hwindowDC);
//
//	return src;
//}
//
//void CallBackFunc(int event, int x, int y, int flags, void* userdata)
//{
//	if (event == EVENT_LBUTTONDOWN)
//	{
//		//xMin = x;
//		//yMin = y;
//		//cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
//	}
//	else if (event == EVENT_RBUTTONDOWN)
//	{
//		//cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
//	}
//	else if (event == EVENT_MBUTTONDOWN)
//	{
//		//cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
//	}
//	else if (event == EVENT_MOUSEMOVE)
//	{
//		//cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl;
//	}
//	else if (event == EVENT_LBUTTONUP)
//	{
//		//xMax = x;
//		//yMax = y;
//		xMin = x;
//		yMin = y;
//
//		xMax = xMin + 60;
//		yMax = yMin + 60;
//	}
//}
//
//int main(int argc, char **argv)
//{
//	HWND hwndDesktop = GetDesktopWindow();
//
//	/// Create a window to display results
//	namedWindow(window_name, CV_WINDOW_AUTOSIZE);
//	namedWindow("Croped", CV_WINDOW_AUTOSIZE);
//	namedWindow("Small", CV_WINDOW_AUTOSIZE);
//	int key = 0;
//
//
//	//set the callback function for any mouse event
//	setMouseCallback(window_name, CallBackFunc, NULL);
//
//	while (key != 27)
//	{
//		if (key == 65)
//		{
//			cropSaved = true;
//			destroyWindow(window_name);
//		}
//		Mat screen = hwnd2mat(hwndDesktop);
//		Mat ROI(screen, Rect(xMin, yMin, xMax, yMax));
//		
//
//		// Copy the data into new matrix
//		ROI.copyTo(croppedImage);
//
//		/// Convert the image to Gray
//		cvtColor(croppedImage, croppedImage_grey, CV_BGR2GRAY);
//
//
//		/// Create Trackbar to choose type of Threshold
//		//createTrackbar(trackbar_type,
//		//	window_name, &threshold_type,
//		//	max_type, Threshold_Demo);
//		//
//		//createTrackbar(trackbar_value,
//		//	window_name, &threshold_value,
//		//	max_value, Threshold_Demo);
//		
//		/// Call the function to initialize
//		Threshold_Demo(0, 0);
//
//		if (!cropSaved)
//		{
//			imshow(window_name, screen);
//		}
//		key = waitKey(20); // you can change wait time
//	}
//	
//	
//
//	/// Wait until user finishes program
//	while (true)
//	{
//		int c;
//		c = waitKey(20);
//		if ((char)c == 27)
//		{
//			break;
//		}
//	}
//
//}
//
