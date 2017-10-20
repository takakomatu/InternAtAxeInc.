/* get_rect.cpp */

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;

#define WIN_NAME_INPUT "Input"
#define N 10

struct mouse {
	int x;
	int y;
	int event;
	int flags;
};

void mouse_callback(int eventType, int x, int y, int flags, void *userdata)
{
	struct mouse *ptr = static_cast<struct mouse *>(userdata);

	ptr->x = x;
	ptr->y = y;
	ptr->event = eventType;
	ptr->flags = flags;
}

int
main(int argc, char *argv[])
{
	struct mouse ev;

	if (argc <= 1) {
		std::cerr << "Usage: " << argv[0] << " image-file ..." << std::endl;
		exit(1);
	}

	namedWindow(WIN_NAME_INPUT,WINDOW_NORMAL);

	for (int i = 1; i < argc; i++) {
		char *input_file = argv[i];
		int n = 0, x[N], y[N], w[N], h[N];

		Mat img = imread(input_file, 1);
		if (img.empty()) {
			std::cerr << "input file error" << std::endl;
			exit(1);
		}

		imshow(WIN_NAME_INPUT, img);
		Mat tmp = img.clone();

		setMouseCallback(WIN_NAME_INPUT, mouse_callback, &ev);

		while (1) {
			char k = waitKey(20);
			if (k == 'q') return 1;
			if (k == '\n') break;
			if (k == ' ') {
				imshow(WIN_NAME_INPUT, img);
				tmp = img.clone();
				n = 0;
			}

			if (n >= N) continue;
			if (ev.event == EVENT_LBUTTONDOWN) {
				ev.event = 0;
				x[n] = ev.x;
				y[n] = ev.y;
				line(tmp, Point(0, y[n]), Point(img.cols, y[n]), Scalar(0,0,0), 1);
				line(tmp, Point(x[n], 0), Point(x[n], img.rows), Scalar(0,0,0), 1);
				imshow(WIN_NAME_INPUT, tmp);
			}
			if (ev.event == EVENT_LBUTTONUP) {
				ev.event = 0;
				w[n] = ev.x - x[n];
				h[n] = ev.y - y[n];
				if (ev.x > img.cols) w[n] = img.cols - x[n];
				if (ev.y > img.rows) h[n] = img.rows - y[n];
				rectangle(tmp, Rect(Point(x[n], y[n]), Size(w[n], h[n])), Scalar(0,0,255), 1);
				imshow(WIN_NAME_INPUT, tmp);
				n++;
			}
		}

		if (n > 0) {
			std::cout << input_file;
			std::cout << "  " << n;
			for (int j = 0; j < n; j++) {
				std::cout << "  " << x[j] << " " << y[j] << " " << w[j] << " " << h[j];
			}
			std::cout << std::endl;
		} else {
			std::cout << input_file << " skipped." << std::endl;
		}
	}
	return 0;
}
