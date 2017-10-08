/* sample1.cpp */
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;

#define WIN_NAME_INPUT "Input"
#define WIN_NAME_OUTPUT "Output"

int
main(int argc, char *argv[])
{
??? const char *input_file = "sample.jpg";

??? if (argc > 1) input_file = argv[1];

??? namedWindow(WIN_NAME_INPUT);
??? namedWindow(WIN_NAME_OUTPUT);

??? Mat src = imread(input_file, 1);
??? if (src.empty()) {
??? ??? std::cerr << "input file error" << std::endl;
??? ??? exit(1);
??? }
??? imshow(WIN_NAME_INPUT, src);

??? Mat dst, work;

??? dst = src.clone();
??? cvtColor(src, work, CV_BGR2GRAY);

??? std::string cascadeName =
??? ??? "/usr/share/opencv/haarcascades/"
??? ??? "haarcascade_frontalface_alt.xml";
??? CascadeClassifier cascade;
??? if (!cascade.load(cascadeName)) {
??? ??? std::cerr << "cascade file error" << std::endl;
??? ??? exit(1);
??? }

??? std::vector<Rect> objs;
??? cascade.detectMultiScale(work, objs);

??? std::vector<Rect>::iterator it = objs.begin();
??? for (; it != objs.end(); it++) {
??? ??? rectangle(dst, *it, Scalar(0,0,255), 2);
??? }

??? imshow(WIN_NAME_OUTPUT, dst);
??? imwrite("result.jpg", dst);

??? waitKey(0);
??? exit(0);
}