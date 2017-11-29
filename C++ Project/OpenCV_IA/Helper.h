#ifndef HELPER_H
#define HELPER_H

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>
#include <Windows.h>
#include <map>
#include <cmath>
#include <algorithm>
#include <limits>
#include <vector>
#include <iterator>

#include <cstdio>
#include <ctime>
#include <fstream>

using namespace std;
using namespace cv; 

enum PopulationGeneratorType
{
	ROULETTE = 0
};

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

	float euclidianDistance(vec2 A)
	{
		float x = (float)x - (float)A.x;
		float y = (float)y - (float)A.y;
		float dist;

		dist = pow(x, 2) + pow(y, 2);
		dist = sqrt(dist);

		return dist;
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

static Mat ResizeMatrix(Mat image, float scaleX, float scaleY, bool interpolate)
{
	Mat dst;
	resize(image, dst, cv::Size(), scaleX, scaleY, interpolate);

	return dst;
}

static Mat ApplyThreshold(Mat image, int thresholdValue, ThresholdType type)
{
	Mat dst;
	threshold(image, dst, thresholdValue, 255, type);

	return dst;
}

static int Flash_TrackBar(String trackBarName, String windowName, int *value, int maxValue)
{
	createTrackbar(trackBarName, windowName, value, maxValue);
	return *value;
}

static float RandWeight(float min, float max)
{
	float randWeight = min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
	return randWeight;
}

static string GetDateTime()
{
	time_t t = time(0);   // get time now
	struct tm * now = localtime(&t);
	string dateTime = to_string(now->tm_mday) + "-" + to_string(now->tm_mon + 1) + "-" + to_string(now->tm_hour) + "-" + to_string(now->tm_min) + "-" + to_string(now->tm_sec);

	return dateTime;
}

#endif
