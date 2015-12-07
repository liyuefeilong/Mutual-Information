#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "highgui.h"
#include <vector>
#include <iostream>

using namespace std;
using namespace cv;

int main( )
{
	Mat img=imread("boy.jpg", 1);
	int img_height = img.rows;
	int img_width = img.cols;
	vector<Point2f> corners(4);
	corners[0] = Point2f(0,0);
	corners[1] = Point2f(img_width-1,0);
	corners[2] = Point2f(0,img_height-1);
	corners[3] = Point2f(img_width-1,img_height-1);
	vector<Point2f> corners_trans(4);
	corners_trans[0] = Point2f(150,250);
	corners_trans[1] = Point2f(300,0);
	corners_trans[2] = Point2f(0,img_height-1);
	corners_trans[3] = Point2f(500,img_height-1);

	Mat transform = getPerspectiveTransform(corners,corners_trans);
	cout<<transform<<endl;
	vector<Point2f> ponits, points_trans;
	for(int i=0;i<img_height;i++){
		for(int j=0;j<img_width;j++){
			ponits.push_back(Point2f(j,i));
		}
	}

	perspectiveTransform( ponits, points_trans, transform);
	Mat img_trans = Mat::zeros(img_height,img_width,CV_8UC3);
	int count = 0;

	
	for(int i=0;i<img_height;i++){
		uchar* p = img.ptr<uchar>(i);
		for(int j=0;j<img_width;j++){
			int y = points_trans[count].y;
			int x = points_trans[count].x;
			uchar* t = img_trans.ptr<uchar>(y);
			t[x*3]  = p[j*3];
			t[x*3+1]  = p[j*3+1];
			t[x*3+2]  = p[j*3+2];
			count++;
		}
	}
	
	imwrite("boy_trans.jpg",img_trans);

	return 0;
}