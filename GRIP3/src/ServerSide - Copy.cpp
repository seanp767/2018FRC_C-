#include <opencv2/opencv.hpp>
#include "GRIPPIPELINE.h"
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

Point pt;
vector<double> aiming_pt(2);
Mat frame;
int red_x = -1, blue_x = -1;


void markPoint(Point, int = 0, int = 0, int = 255);

Point getMaxCenter(vector<vector<Point> > table, bool red) {
	Point maxCenter = cv::Point(-1, -1);
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
			if (red == true) markPoint(table[maxIndex][i], 0, 0, 255);
			else markPoint(table[maxIndex][i], 255, 0, 0);
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

	VideoCapture cap(1);
	grip::GRIPPIPELINE gp;
	vector<vector<Point> > table;

	// if not success, exit program
	if (cap.isOpened()==false) {
		cout << "Cannot open the video camera" << endl;
		cin.get(); //wait for any key press
		return -1;
	}
	string window_name = "cam_red&blue";

	namedWindow(window_name);


	while (true) {
 // read a new frame from video
		bool bSuccess = cap.read(frame);

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

		gp.GRIPPIPELINE::process_red(frame);
		table = *gp.GRIPPIPELINE::getfindContoursOutput_r();
		if (!table.empty()) {
			pt = getMaxCenter(table, true);

			red_x=pt.x;
		}
		gp.GRIPPIPELINE::process_blue(frame);
		table = *gp.GRIPPIPELINE::getfindContoursOutput_b();
		if (!table.empty()) {
			pt = getMaxCenter(table, false);

			blue_x=pt.x;
		}

		if (red_x != -1 && blue_x != -1) {
			if (red_x > blue_x) cout << "blue: left; red: right"<<endl;
			else cout << "red: left; blue: right"<<endl;
		} else if (red_x == -1 && blue_x != -1) {
			if (blue_x >= 160) cout << "blue: left; red: right"<<endl;
			else cout << "red: left; blue: right"<<endl;
		} else if (red_x != -1 && blue_x == -1) {
			if (red_x >= 160) cout << "red: left; blue: right"<<endl;
			else cout << "blue: left; red: right"<<endl;
		}
		imshow(window_name, frame);

		if (waitKey(10) >= 0) {
			cout << "Esc key pressed or time passed by user. Stopping the video." << endl;
			break;
		}

	}
	return 0;
}

