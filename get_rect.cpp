/* get_rect.cpp */

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;

#define WIN_NAME_INPUT "Input"

struct mouse {
	int x;
	int y;
	int event;
	int flags;
};

void CallBackFunc(int eventType, int x, int y, int flags, void* userdata)
{
	struct mouse *ptr = static_cast<struct mouse*> (userdata);

	ptr->x = x;
	ptr->y = y;
	ptr->event = eventType;
	ptr->flags = flags;
}

int
main(int argc, char *argv[])
{
	struct mouse ev;
	int x, y, w, h;

	int d = atoi(argv[1]);
	if (d <= 0) d = 1;

	for (int i = 2; i < argc; i++) {
		char *input_file = argv[i];
		namedWindow(WIN_NAME_INPUT);

		Mat src = imread(input_file, 1);
		if (src.empty()) {
			std::cerr << "input file error" << std::endl;
			exit(1);
		}

		Mat img;
		resize(src, img, Size(), (float)1/d, (float)1/d);
		imshow(WIN_NAME_INPUT, img);
		Mat tmp = img.clone();

		setMouseCallback(WIN_NAME_INPUT, CallBackFunc, &ev);

		while (1) {
			if (ev.event == EVENT_LBUTTONDOWN) {
				x = ev.x;
				y = ev.y;
				ev.event = 0;
			}
			if (ev.event == EVENT_LBUTTONUP) {
				w = ev.x - x;
				h = ev.y - y;
				ev.event = 0;
				rectangle(tmp, Point(x, y), Point(ev.x, ev.y), Scalar(0,0,255), 1);
				imshow(WIN_NAME_INPUT, tmp);
			}

			char k = waitKey(20);
			if (k == '\n') {
				std::cout << input_file << " 1 " << x * d << " " << y * d << " ";
				std::cout << (ev.x - x) * d << " " << (ev.y - y) * d << std::endl;
				break;
			}
			if (k == ' ') {
				imshow(WIN_NAME_INPUT, img);
				tmp = img.clone();
			}
		}
	}
	return 0;
}
