#ifndef HELPER_H
#define HELPER_H

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <Windows.h>
#include <iostream>

using namespace std;
using namespace cv;

enum ThresholdType
{
	Binary = 0,
	Binary_Inverted = 1,
	Truncated = 2,
	ToZero = 3,
	ToZero_Inverted = 4
};

struct vec2
{
	int x;
	int y;

	vec2()
	{
		this->x = 0;
		this->y = 0;
	}

	vec2(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	vec2& operator=(const vec2& v)
	{
		x = v.x;
		y = v.y;
		return *this;
	}

	bool operator==(const vec2& v)
	{
		if (x == v.x && y == v.y)
			return true;
		else
			return false;
	}

	vec2& operator+(const vec2& v)
	{
		x += v.x;
		y += v.y;

		return *this;
	}

	vec2& operator-(const vec2& v)
	{
		x -= v.x;
		y -= v.y;

		return *this;
	}
};

static Mat CropMatrix(Mat screen, vec2 topLeft, vec2 size)
{
	Mat ROI(screen, Rect(topLeft.x, topLeft.y, size.x, size.y));

	// Copy the data into new matrix
	Mat croppedImage;
	ROI.copyTo(croppedImage);

	return croppedImage;
}


static Mat ApplyThreshold(Mat image, int thresholdValue, ThresholdType type)
{
	Mat dst;
	threshold(image, dst, thresholdValue, 255, type);

	return dst;
}

static Mat ResizeMatrix(Mat image, float scaleX, float scaleY, bool interpolate)
{
	Mat dst;
	resize(image, dst, cv::Size(), scaleX, scaleY, interpolate);

	return dst;
}

static int Flash_TrackBar(String trackBarName, String windowName, int *value, int maxValue)
{
	createTrackbar(trackBarName, windowName, value, maxValue);
	return *value;
}

#endif
