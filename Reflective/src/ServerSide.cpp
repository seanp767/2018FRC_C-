#include <opencv2/opencv.hpp>
#include "GripReflective.h"
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

Point pt;
vector<double> aiming_pt(2);
Mat frame;

void markPoint(Point, int = 0, int = 0, int = 255);

Point getMaxCenter(vector<vector<Point> > table) {
	Point maxCenter = cv::Point(160, 120);
	int maxIndex = 0;
	int sumX = 0;
	int sumY = 0;
	for (unsigned i = 1; i < table.size(); i++) {
		if (cv::contourArea(table[i]) > cv::contourArea(table[maxIndex]) && cv::contourArea(table[i]) > 4000) {
			maxIndex = i;
		}
	}
	if(cv::contourArea(table[maxIndex]) > 4000) {
		for (unsigned i = 0; i < table[maxIndex].size(); i++) {
			sumX += table[maxIndex][i].x;
			sumY += table[maxIndex][i].y;
			markPoint(table[maxIndex][i], 255, 255, 255);
		}
		maxCenter.x = ((int) (sumX / table[maxIndex].size() / 20)) * 20;
		maxCenter.y = ((int) (sumY / table[maxIndex].size() / 20)) * 20;
	}
	return maxCenter;

}

void getAimingXY(Point pt) {
	aiming_pt[0] = (double) (pt.x - 160) / 160;
	aiming_pt[1] = (double) (pt.y - 120) / -120;
}

void markPoint(Point point, int b, int g, int r) {
	frame.at<Vec3b>(Point(point.x * 2, point.y * 2 - 1)) = Vec3b(b, g, r);
	frame.at<Vec3b>(Point(point.x * 2 - 1, point.y * 2)) = Vec3b(b, g, r);
	frame.at<Vec3b>(Point(point.x * 2, point.y * 2)) = Vec3b(b, g, r);
	frame.at<Vec3b>(Point(point.x * 2 + 1, point.y * 2)) = Vec3b(b, g, r);
	frame.at<Vec3b>(Point(point.x * 2, point.y * 2 + 1)) = Vec3b(b, g, r);
}

int main(void) {
	int count = 0;
	VideoCapture cap(0);
	grip::GripReflective gp;
	vector<vector<Point> > table;

	// if not success, exit program
	if (cap.isOpened() == false) {
		cout << "Cannot open the video camera" << endl;
		cin.get(); //wait for any key press
		return -1;
	}
	string window_name = "My Camera Feed";
	namedWindow(window_name); //create a window called "My Camera Feed"

	while (true) {
		bool bSuccess = cap.read(frame); // read a new frame from video

		//Breaking the while loop if the frames cannot be captured
		if (bSuccess == false) {
			cout << "Video camera is disconnected" << endl;
			cin.get(); //Wait for any key press
			break;
		}
		if (cap.isOpened() == false) {
			cout << "Cannot open the video camera" << endl;
			cin.get(); //wait for any key press
			return -1;
		}

		gp.GripReflective::process(frame);
		table = *gp.GripReflective::getfindContoursOutput();
		if (!table.empty()) {
			pt = getMaxCenter(table);
			getAimingXY(pt);
			if (pt != cv::Point(160,120) )
				cout << pt.x << ", " << pt.y << "\t(" << aiming_pt[0] << ", "
					<< aiming_pt[1] << ")" << endl;
			markPoint(pt);
		}

		imshow(window_name, frame);
		if (count >= 480 || waitKey(10) >= 0) {
			cout << "Esc key pressed or time passed by user. Stopping the video." << endl;
			break;
		}
		count++;
	}
	return 0;
}
