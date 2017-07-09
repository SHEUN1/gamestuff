/*
 * SeperateObjects.cpp
 *
 *  Created on: 9 Jul 2017
 *      Author: sheun
 */

#include "SeperateObjects.h"
#include <vector>
#include <stdlib.h>

//using namespace std;

SeperateObjects::SeperateObjects() {
	// TODO Auto-generated constructor stub

}

SeperateObjects::~SeperateObjects() {
	// TODO Auto-generated destructor stub
}

Mat1b SeperateObjects::BoundBox(Mat1b Binary)
{
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	//find contours
	findContours(Binary, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0,0));

	//Approximate contours to polygons + get bounding rects
	vector<vector<Point> > contours_poly(contours.size());
	vector<Rect> boundRect (contours.size());

	for(int i = 0; i < contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
		boundRect[i] = boundingRect(Mat(contours_poly[i]));
	}

	//Draw polygon contour + bounding rects


	Mat drawing = Mat::zeros(Binary.size(), CV_8UC3);
	for (int i = 0; i<contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0,255), rng.uniform(0,255), rng.uniform(0,255));
		drawContours(Binary, contours_poly, i, color, 1,8, vector<Vec4i>(), 0, Point());
		rectangle (Binary, boundRect[i].tl(), boundRect[i].br(), color, 2,8,0);
	}

	return Binary;
}

