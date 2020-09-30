// use x64 debug

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>


#define w 400
using namespace cv;

void myelipse(cv::Mat img, double angle);
void fillcircle(cv::Mat img, cv::Point center);
void MyPolygon(Mat img);
void MyLine(Mat img, Point start, Point end);


// 1. basic drawing
void basic_draw() {
	// 2D point
	cv::Point pt(10, 8);
	cv::Point pt1; pt1.x = 10; pt1.y = 8;

	// scalar: 4-element vector. Last element does not need to be defined.
	cv::Scalar(1, 2, 4); // -> BGR

	char atom_window[] = "Drawing1: Atom";
	char rook_window[] = "Drawing1: Hook";
	cv::Mat atom_img = cv::Mat::zeros(w, w, CV_8UC3);
	cv::Mat rook_img = cv::Mat::zeros(w, w, CV_8UC3);

	// draw ellipse
	myelipse(atom_img, 90);
	myelipse(atom_img, 0);
	myelipse(atom_img, 45);
	myelipse(atom_img, -45);
	fillcircle(atom_img, cv::Point(w / 2, w / 2));
	imshow("atom", atom_img);
	cv::waitKey();
	destroyWindow("atom");

	MyPolygon(rook_img);
	rectangle(rook_img,
		Point(0, 7 * w / 8), 
		Point(w, w),
		Scalar(0, 255, 255),
		FILLED,   // FILLED = -1(thickness)
		LINE_8);
	MyLine(rook_img, Point(0, 15 * w / 16), Point(w, 15 * w / 16));
	MyLine(rook_img, Point(w / 4, 7 * w / 8), Point(w / 4, w));
	MyLine(rook_img, Point(w / 2, 7 * w / 8), Point(w / 2, w));
	MyLine(rook_img, Point(3 * w / 4, 7 * w / 8), Point(3 * w / 4, w));
	imshow("rook", rook_img);
	cv::waitKey();
	destroyAllWindows();
	
}

void myelipse(cv::Mat img, double angle) {
	int thick = 2;
	int lineType = 8;
	cv::ellipse(img, cv::Point(w/2, w/2), cv::Size(w/4, w/16),
		angle, 0, 360, cv::Scalar(255, 0, 0), thick, lineType);
}

void fillcircle(cv::Mat img, cv::Point center) {
	cv::circle(img, center, w / 32, cv::Scalar(0, 0, 255), cv::FILLED, cv::LINE_8);
}

void MyPolygon(Mat img)
{
	int lineType = LINE_8;
	Point rook_points[1][20];
	rook_points[0][0] = Point(w / 4, 7 * w / 8);
	rook_points[0][1] = Point(3 * w / 4, 7 * w / 8);
	rook_points[0][2] = Point(3 * w / 4, 13 * w / 16);
	rook_points[0][3] = Point(11 * w / 16, 13 * w / 16);
	rook_points[0][4] = Point(19 * w / 32, 3 * w / 8);
	rook_points[0][5] = Point(3 * w / 4, 3 * w / 8);
	rook_points[0][6] = Point(3 * w / 4, w / 8);
	rook_points[0][7] = Point(26 * w / 40, w / 8);
	rook_points[0][8] = Point(26 * w / 40, w / 4);
	rook_points[0][9] = Point(22 * w / 40, w / 4);
	rook_points[0][10] = Point(22 * w / 40, w / 8);
	rook_points[0][11] = Point(18 * w / 40, w / 8);
	rook_points[0][12] = Point(18 * w / 40, w / 4);
	rook_points[0][13] = Point(14 * w / 40, w / 4);
	rook_points[0][14] = Point(14 * w / 40, w / 8);
	rook_points[0][15] = Point(w / 4, w / 8);
	rook_points[0][16] = Point(w / 4, 3 * w / 8);
	rook_points[0][17] = Point(13 * w / 32, 3 * w / 8);
	rook_points[0][18] = Point(5 * w / 16, 13 * w / 16);
	rook_points[0][19] = Point(w / 4, 13 * w / 16);
	const Point* ppt[1] = { rook_points[0] };
	int npt[] = { 20 };
	fillPoly(img,
		ppt,
		npt,
		1,
		Scalar(255, 255, 255),
		lineType);
}

void MyLine(Mat img, Point start, Point end)
{
	int thickness = 2;
	int lineType = LINE_8;
	line(img,
		start,
		end,
		Scalar(0, 0, 0),
		thickness,
		lineType);
}

// 2. Smoothing image
void smooth() {
	cv::Mat src = imread("win95-logo.jpg", IMREAD_GRAYSCALE);
	// box filter
	cv::Mat src_box;
	cv::blur(src, src_box, cv::Size(3, 3));
	imshow("box_blur", src_box);
	waitKey();
	destroyWindow("box_blur");
	// gaussian blur
	cv::Mat src_gau;
	cv::GaussianBlur(src, src_gau, cv::Size(3, 3), 0, 0);
	imshow("gaussian_blur", src_gau);
	waitKey();
	destroyWindow("gaussian_blur");
	// median blur
	cv::Mat src_med;
	cv::medianBlur(src, src_med, 3);
	imshow("median_blur", src_med);
	waitKey();
	destroyWindow("median_blur");
	// bilateral filter
	cv::Mat src_bila;
	cv::bilateralFilter(src, src_bila, 5, 5, 5);
	imshow("bilateral_blur", src_bila);
	waitKey();
	destroyWindow("bilateral_blur");
}

// 3. erode and dilate image
void morph() {
	cv::Mat img = imread("win95-logo.jpg", IMREAD_GRAYSCALE);
	cv::Mat dst1, dst2;
	// erode
	cv::Mat element = getStructuringElement(MORPH_RECT, Size(7, 7));
	cv::erode(img, dst1, element);
	
	// dilate
	cv::dilate(img, dst2, element);

	cv::hconcat(dst1, dst2, img);
	imshow("result", img);
	waitKey();
}

// 4. other morphological transformation
void more_morph() {
	cv::Mat img = imread("win95-logo.jpg", IMREAD_GRAYSCALE);
	cv::Mat dst1, dst2;
	Mat element = getStructuringElement(MORPH_CROSS, Size(2 * 3 + 1, 2 * 3 + 1));
	
	// open = dilate(erode) remove small bright object
	cv::morphologyEx(img, dst1, MORPH_OPEN, element);
	
	// close = erode(dilate) remove small dark holes
	cv::morphologyEx(img, dst2, MORPH_CLOSE, element);
	cv::hconcat(dst1, dst2, dst1);
	imshow("open and close", dst1);
	waitKey();
	destroyWindow("open and close");

	// morphological gradient: dilate-erode.  Finding contour
	cv::morphologyEx(img, dst1, MORPH_GRADIENT, element);
	imshow("gradient", dst1);
	waitKey();
	destroyWindow("gradient");

	// top hat: src - open
	cv::morphologyEx(img, dst1, MORPH_TOPHAT, element);
	imshow("tophat", dst1);
	waitKey();
	destroyWindow("tophat");

	// black hat: close - src
	cv::morphologyEx(img, dst1, MORPH_BLACKHAT, element);
	imshow("blackhat", dst1);
	waitKey();
	destroyWindow("blackhat");
}

// 5. hit or miss
void hit_or_miss() {
	cv::Mat input = (Mat_<uchar>(8, 8) <<
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 255, 255, 255, 0, 0, 0, 255,
		0, 255, 255, 255, 0, 0, 0, 0,
		0, 255, 255, 255, 0, 255, 0, 0,
		0, 0, 255, 0, 0, 0, 0, 0,
		0, 0, 255, 0, 0, 255, 255, 0,
		0, 255, 0, 255, 0, 0, 255, 0,
		0, 255, 255, 255, 0, 0, 0, 0);

	cv::Mat kernel = (Mat_<int>(3, 3) <<
		0, 1, 0,
		1, -1, 1,
		0, 1, 0);

	cv::Mat output;
	cv::morphologyEx(input, output, MORPH_HITMISS, kernel);

	cv::resize(output, output, cv::Size(), 50, 50, INTER_NEAREST);
	imshow("Hit or Miss", output);
	moveWindow("Hit or Miss", 500, 200);

	waitKey(0);
}

// 6. line detection
void line_detect() {
	cv::Mat img = imread(samples::findFile("music_note.png"), IMREAD_GRAYSCALE);
	cv::adaptiveThreshold(~img, img, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, -2);
	
	cv::Mat horizontal = img.clone();
	cv::Mat vertical = img.clone();
	int hor_size = horizontal.cols / 30;
	cv::Mat horizontalStructure = cv::getStructuringElement(MORPH_RECT, cv::Size(hor_size, 1));

	erode(horizontal, horizontal, horizontalStructure, Point(-1, -1));  // kernel内有黑就全黑
	dilate(horizontal, horizontal, horizontalStructure, Point(-1, -1)); // kernel内有白就全白
	// cv::morphologyEx(img, img, MORPH_OPEN, horizontalStructure, Point(-1, -1));

	imshow("result", horizontal);
	waitKey();
}

int main(){
	// basic_draw();
	// smooth();
	// morph();
	// more_morph();
	// hit_or_miss();
	line_detect();
	return 0;
}