#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(void)
{
	VideoCapture cap(-1);
	double fps = cap.get(CAP_PROP_FPS);
	int w = cvRound(cap.get(CAP_PROP_FRAME_WIDTH));
	int h = cvRound(cap.get(CAP_PROP_FRAME_HEIGHT));
	int delay = cvRound(1000 / fps);
	Mat frame;
	VideoWriter writer;
	int fourcc = VideoWriter::fourcc('D', 'I', 'V', 'X');
	writer.open("output.avi", fourcc, fps, Size(w, h));

	while (true) {
		cap >> frame;
		flip(frame, frame, 0);
		flip(frame, frame, 1);
		writer << frame;

		imshow("frame", frame);

		if (waitKey(10) == 27) {
			break;
		}
	}
	cap.release();
	writer.release();

	return 0;
}
