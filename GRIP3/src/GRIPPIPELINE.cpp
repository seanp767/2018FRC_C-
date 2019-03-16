#include "GRIPPIPELINE.h"
/**
* Initializes a GRIPPIPELINE.
*/

namespace grip {

GRIPPIPELINE::GRIPPIPELINE() : red_x(-1), blue_x(-1){
}
/**
* Runs an iteration of the Pipeline and updates outputs.
*
* Sources need to be set before calling this method. 
*
*/
void GRIPPIPELINE::process_red(cv::Mat source0){
	//Step CV_resize0:
	//input
	cv::Mat cvResizeSrc = source0;
	cv::Size cvResizeDsize(0, 0);
	double cvResizeFx = 0.5;  // default Double
	double cvResizeFy = 0.5;  // default Double
    int cvResizeInterpolation = cv::INTER_LINEAR;
	cvResize(cvResizeSrc, cvResizeDsize, cvResizeFx, cvResizeFy, cvResizeInterpolation, this->cvResizeOutput);
	//Step Blur0:
	//input
	cv::Mat blurInput = cvResizeOutput;
	BlurType blurType = BlurType::BOX;
	double blurRadius = 10.242584259362355;  // default Double
	blur(blurInput, blurType, blurRadius, this->blurOutput);
	//Step HSV_Threshold0:
	//input
	cv::Mat hsvThresholdInput = blurOutput;
	double hsvThresholdHue[] = {0.0, 16.0};
	double hsvThresholdSaturation[] = {84.0, 255.0};
	double hsvThresholdValue[] = {0.0, 255.0};
	hsvThreshold(hsvThresholdInput, hsvThresholdHue, hsvThresholdSaturation, hsvThresholdValue, this->hsvThresholdOutput_r);
	//Step CV_erode0:
	//input
	cv::Mat cvErodeSrc = hsvThresholdOutput_r;
	cv::Mat cvErodeKernel;
	cv::Point cvErodeAnchor(-1, -1);
	double cvErodeIterations = 1;  // default Double
    int cvErodeBordertype = cv::BORDER_CONSTANT;
	cv::Scalar cvErodeBordervalue(-1);
	cvErode(cvErodeSrc, cvErodeKernel, cvErodeAnchor, cvErodeIterations, cvErodeBordertype, cvErodeBordervalue, this->cvErodeOutput);
	//Step Find_Contours0:
	//input
	cv::Mat findContoursInput = cvErodeOutput;
	bool findContoursExternalOnly = false;  // default Boolean
	findContours_r(findContoursInput, findContoursExternalOnly, this->findContoursOutput_r);
	//Step Filter_Contours0:
	//input
	std::vector<std::vector<cv::Point> > filterContoursContours = findContoursOutput_r;
	double filterContoursMinArea = 2500.0;  // default Double
	double filterContoursMinPerimeter = 0.0;  // default Double
	double filterContoursMinWidth = 40.0;  // default Double
	double filterContoursMaxWidth = 1000.0;  // default Double
	double filterContoursMinHeight = 0.0;  // default Double
	double filterContoursMaxHeight = 1000.0;  // default Double
	double filterContoursSolidity[] = {0, 100};
	double filterContoursMaxVertices = 1000000.0;  // default Double
	double filterContoursMinVertices = 0.0;  // default Double
	double filterContoursMinRatio = 0.0;  // default Double
	double filterContoursMaxRatio = 1000.0;  // default Double
	filterContours(filterContoursContours, filterContoursMinArea, filterContoursMinPerimeter, filterContoursMinWidth, filterContoursMaxWidth, filterContoursMinHeight, filterContoursMaxHeight, filterContoursSolidity, filterContoursMaxVertices, filterContoursMinVertices, filterContoursMinRatio, filterContoursMaxRatio, this->filterContoursOutput);
}

void GRIPPIPELINE::process_blue(cv::Mat source0){
	//Step CV_resize0:
	//input
	cv::Mat cvResizeSrc = source0;
	cv::Size cvResizeDsize(0, 0);
	double cvResizeFx = 0.5;  // default Double
	double cvResizeFy = 0.5;  // default Double
    int cvResizeInterpolation = cv::INTER_LINEAR;
	cvResize(cvResizeSrc, cvResizeDsize, cvResizeFx, cvResizeFy, cvResizeInterpolation, this->cvResizeOutput);
	//Step Blur0:
	//input
	cv::Mat blurInput = cvResizeOutput;
	BlurType blurType = BlurType::BOX;
	double blurRadius = 20;  // default Double
	blur(blurInput, blurType, blurRadius, this->blurOutput);
	//Step HSV_Threshold0:
	//input
	cv::Mat hsvThresholdInput = blurOutput;
	double hsvThresholdHue[] = {44, 116};
	double hsvThresholdSaturation[] = {134.0, 255.0};
	double hsvThresholdValue[] = {122, 255.0};
	hsvThreshold(hsvThresholdInput, hsvThresholdHue, hsvThresholdSaturation, hsvThresholdValue, this->hsvThresholdOutput_b);
	//Step CV_erode0:
	//input
	cv::Mat cvErodeSrc = hsvThresholdOutput_b;
	cv::Mat cvErodeKernel;
	cv::Point cvErodeAnchor(-1, -1);
	double cvErodeIterations = 1;  // default Double
    int cvErodeBordertype = cv::BORDER_CONSTANT;
	cv::Scalar cvErodeBordervalue(-1);
	cvErode(cvErodeSrc, cvErodeKernel, cvErodeAnchor, cvErodeIterations, cvErodeBordertype, cvErodeBordervalue, this->cvErodeOutput);
	//Step Find_Contours0:
	//input
	cv::Mat findContoursInput = cvErodeOutput;
	bool findContoursExternalOnly = false;  // default Boolean
	findContours_b(findContoursInput, findContoursExternalOnly, this->findContoursOutput_b);
	//Step Filter_Contours0:
	//input
	std::vector<std::vector<cv::Point> > filterContoursContours = findContoursOutput_b;
	double filterContoursMinArea = 3500.0;  // default Double
	double filterContoursMinPerimeter = 0.0;  // default Double
	double filterContoursMinWidth = 40.0;  // default Double
	double filterContoursMaxWidth = 1000.0;  // default Double
	double filterContoursMinHeight = 0.0;  // default Double
	double filterContoursMaxHeight = 1000.0;  // default Double
	double filterContoursSolidity[] = {0, 100};
	double filterContoursMaxVertices = 1000000.0;  // default Double
	double filterContoursMinVertices = 0.0;  // default Double
	double filterContoursMinRatio = 0.0;  // default Double
	double filterContoursMaxRatio = 1000.0;  // default Double
	filterContours(filterContoursContours, filterContoursMinArea, filterContoursMinPerimeter, filterContoursMinWidth, filterContoursMaxWidth, filterContoursMinHeight, filterContoursMaxHeight, filterContoursSolidity, filterContoursMaxVertices, filterContoursMinVertices, filterContoursMinRatio, filterContoursMaxRatio, this->filterContoursOutput);
}
/**
 * This method is a generated setter for source0.
 * @param source the Mat to set
 */


/**
 * This method is a generated getter for the output of a CV_resize.
 * @return Mat output from CV_resize.
 */
cv::Mat* GRIPPIPELINE::getcvResizeOutput(){
	return &(this->cvResizeOutput);
}
/**
 * This method is a generated getter for the output of a Blur.
 * @return Mat output from Blur.
 */
cv::Mat* GRIPPIPELINE::getblurOutput(){
	return &(this->blurOutput);
}
/**
 * This method is a generated getter for the output of a HSV_Threshold.
 * @return Mat output from HSV_Threshold.
 */
cv::Mat* GRIPPIPELINE::gethsvThresholdOutput_r(){
	return &(this->hsvThresholdOutput_r);
}
cv::Mat* GRIPPIPELINE::gethsvThresholdOutput_b(){
	return &(this->hsvThresholdOutput_b);
}
/**
 * This method is a generated getter for the output of a CV_erode.
 * @return Mat output from CV_erode.
 */
cv::Mat* GRIPPIPELINE::getcvErodeOutput(){
	return &(this->cvErodeOutput);
}
/**
 * This method is a generated getter for the output of a Find_Contours.
 * @return ContoursReport output from Find_Contours.
 */
std::vector<std::vector<cv::Point> >* GRIPPIPELINE::getfindContoursOutput_r(){
	return &(this->findContoursOutput_r);
}
std::vector<std::vector<cv::Point> >* GRIPPIPELINE::getfindContoursOutput_b(){
	return &(this->findContoursOutput_b);
}
/**
 * This method is a generated getter for the output of a Filter_Contours.
 * @return ContoursReport output from Filter_Contours.
 */
std::vector<std::vector<cv::Point> >* GRIPPIPELINE::getfilterContoursOutput(){
	return &(this->filterContoursOutput);
}
	/**
	 * Resizes an Image.
	 * @param src The image to resize.
	 * @param dSize size to set the image.
	 * @param fx scale factor along X axis.
	 * @param fy scale factor along Y axis.
	 * @param interpolation type of interpolation to use.
	 * @param dst output image.
	 */
	void GRIPPIPELINE::cvResize(cv::Mat &src, cv::Size &dSize, double fx, double fy, int interpolation, cv::Mat &dst) {
		cv::resize(src, dst, dSize, fx, fy, interpolation);
	}

	/**
	 * Softens an image using one of several filters.
	 *
	 * @param input The image on which to perform the blur.
	 * @param type The blurType to perform.
	 * @param doubleRadius The radius for the blur.
	 * @param output The image in which to store the output.
	 */
	void GRIPPIPELINE::blur(cv::Mat &input, BlurType &type, double doubleRadius, cv::Mat &output) {
		int radius = (int)(doubleRadius + 0.5);
		int kernelSize;
		switch(type) {
			case BOX:
				kernelSize = 2 * radius + 1;
				cv::blur(input,output,cv::Size(kernelSize, kernelSize));
				break;
			case GAUSSIAN:
				kernelSize = 6 * radius + 1;
				cv::GaussianBlur(input, output, cv::Size(kernelSize, kernelSize), radius);
				break;
			case MEDIAN:
				kernelSize = 2 * radius + 1;
				cv::medianBlur(input, output, kernelSize);
				break;
			case BILATERAL:
				cv::bilateralFilter(input, output, -1, radius, radius);
				break;
        }
	}
	/**
	 * Segment an image based on hue, saturation, and value ranges.
	 *
	 * @param input The image on which to perform the HSL threshold.
	 * @param hue The min and max hue.
	 * @param sat The min and max saturation.
	 * @param val The min and max value.
	 * @param output The image in which to store the output.
	 */
	void GRIPPIPELINE::hsvThreshold(cv::Mat &input, double hue[], double sat[], double val[], cv::Mat &out) {
		cv::cvtColor(input, out, cv::COLOR_BGR2HSV);
		cv::inRange(out,cv::Scalar(hue[0], sat[0], val[0]), cv::Scalar(hue[1], sat[1], val[1]), out);
	}

	/**
	 * Expands area of lower value in an image.
	 * @param src the Image to erode.
	 * @param kernel the kernel for erosion.
	 * @param anchor the center of the kernel.
	 * @param iterations the number of times to perform the erosion.
	 * @param borderType pixel extrapolation method.
	 * @param borderValue value to be used for a constant border.
	 * @param dst Output Image.
	 */
	void GRIPPIPELINE::cvErode(cv::Mat &src, cv::Mat &kernel, cv::Point &anchor, double iterations, int borderType, cv::Scalar &borderValue, cv::Mat &dst) {
		cv::erode(src, dst, kernel, anchor, (int)iterations, borderType, borderValue);
	}

	/**
	 * Finds contours in an image.
	 *
	 * @param input The image to find contours in.
	 * @param externalOnly if only external contours are to be found.
	 * @param contours vector of contours to put contours in.
	 */
	void GRIPPIPELINE::findContours_r(cv::Mat &input, bool externalOnly, std::vector<std::vector<cv::Point> > &contours) {
		std::vector<cv::Vec4i> hierarchy;
		contours.clear();
		int mode = externalOnly ? cv::RETR_EXTERNAL : cv::RETR_LIST;
		int method = cv::CHAIN_APPROX_SIMPLE;
		cv::findContours(input, contours, hierarchy, mode, method);
	}
	void GRIPPIPELINE::findContours_b(cv::Mat &input, bool externalOnly, std::vector<std::vector<cv::Point> > &contours) {
			std::vector<cv::Vec4i> hierarchy;
			contours.clear();
			int mode = externalOnly ? cv::RETR_EXTERNAL : cv::RETR_LIST;
			int method = cv::CHAIN_APPROX_SIMPLE;
			cv::findContours(input, contours, hierarchy, mode, method);
		}



	/**
	 * Filters through contours.
	 * @param inputContours is the input vector of contours.
	 * @param minArea is the minimum area of a contour that will be kept.
	 * @param minPerimeter is the minimum perimeter of a contour that will be kept.
	 * @param minWidth minimum width of a contour.
	 * @param maxWidth maximum width.
	 * @param minHeight minimum height.
	 * @param maxHeight  maximimum height.
	 * @param solidity the minimum and maximum solidity of a contour.
	 * @param minVertexCount minimum vertex Count of the contours.
	 * @param maxVertexCount maximum vertex Count.
	 * @param minRatio minimum ratio of width to height.
	 * @param maxRatio maximum ratio of width to height.
	 * @param output vector of filtered contours.
	 */
	void GRIPPIPELINE::filterContours(std::vector<std::vector<cv::Point> > &inputContours, double minArea, double minPerimeter, double minWidth, double maxWidth, double minHeight, double maxHeight, double solidity[], double maxVertexCount, double minVertexCount, double minRatio, double maxRatio, std::vector<std::vector<cv::Point> > &output) {
		std::vector<cv::Point> hull;
		output.clear();
		for (std::vector<cv::Point> contour: inputContours) {
			cv::Rect bb = boundingRect(contour);
			if (bb.width < minWidth || bb.width > maxWidth) continue;
			if (bb.height < minHeight || bb.height > maxHeight) continue;
			double area = cv::contourArea(contour);
			if (area < minArea) continue;
			if (arcLength(contour, true) < minPerimeter) continue;
			cv::convexHull(cv::Mat(contour, true), hull);
			double solid = 100 * area / cv::contourArea(hull);
			if (solid < solidity[0] || solid > solidity[1]) continue;
			if (contour.size() < minVertexCount || contour.size() > maxVertexCount)	continue;
			double ratio = bb.width / bb.height;
			if (ratio < minRatio || ratio > maxRatio) continue;
			output.push_back(contour);
		}
	}

	void GRIPPIPELINE::getAimingXY(cv::Point pt)
	{
		aiming_pt[0] = (double) (pt.x - 160) / 160;
		aiming_pt[1] = (double) (pt.y - 120) / -120;
	}

	cv::Point GRIPPIPELINE::getMaxCenter(std::vector<std::vector<cv::Point> > table, bool red)
	{
		cv::Point maxCenter = cv::Point(-1, -1);
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


	void GRIPPIPELINE::markPoint(cv::Point point, int b=0, int g=0, int r=255){
		frame.at<cv::Vec3b>(cv::Point(point.x * 2, point.y * 2 - 1)) = cv::Vec3b(b, g, r);
		frame.at<cv::Vec3b>(cv::Point(point.x * 2 - 1, point.y * 2)) = cv::Vec3b(b, g, r);
		frame.at<cv::Vec3b>(cv::Point(point.x * 2, point.y * 2)) = cv::Vec3b(b, g, r);
		frame.at<cv::Vec3b>(cv::Point(point.x * 2 + 1, point.y * 2)) = cv::Vec3b(b, g, r);
		frame.at<cv::Vec3b>(cv::Point(point.x * 2, point.y * 2 + 1)) =cv:: Vec3b(b, g, r);

}
	int GRIPPIPELINE::serverside(void){
			cv::VideoCapture cap(1);
			grip::GRIPPIPELINE gp;
			std::vector<std::vector<cv::Point> > table;



			if (cap.isOpened()==false) {
				std::cout << "Cannot open the video camera" << std::endl;
				std::cin.get();
				return -1;
			}
			std::string window_name = "cam_red&blue";
			cv::namedWindow(window_name);
			while (true) {
				bool bSuccess = cap.read(frame);
				if (bSuccess == false) {
					std::cout << "Video camera is disconnected" << std::endl;
					std::cin.get(); //Wait for any key press
					break;
				}
				if (cap.isOpened() == false) {
					std::cout << "Cannot open the video camera" << std::endl;
					std::cin.get(); //wait for any key press
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
					if (red_x > blue_x)
					{
						std::cout << "move right";

					}else
						{
						std::cout << "move left";

						}
				} else if (red_x == -1 && blue_x != -1) {
					if (blue_x >= 160)
					{
						std::cout << "move right";

					}else
					{
						std::cout << "move left";

					}
				} else if (red_x != -1 && blue_x == -1) {
					if (red_x >= 160)
					{
						std::cout << "move right";

					}else {
						std::cout << "move left";

					}
				}
				std::cout << std::endl;
				imshow(window_name, frame);
				if (cv::waitKey(10) >= 0) {
					std::cout << "Esc key pressed or time passed by user. Stopping the video." << std::endl;
					break;
				}
			}
			return 0;
	}
}
