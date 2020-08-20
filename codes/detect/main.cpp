#include <opencv2/opencv.hpp>
#include <iostream>
#include "./opencv/face_yolo.hpp"

using namespace cv;
using namespace std;

int main()
{
	dnn::Net net = dnn::readNetFromDarknet(YOLO_CFG_PATH, YOLO_WEIGHT_PATH);
	net.setPreferableBackend(dnn::DNN_BACKEND_OPENCV);
	net.setPreferableTarget(dnn::DNN_TARGET_CPU);
	
	
	VideoCapture cap(-1);

	Mat blob;
	Mat frame;

	std::vector<Mat> outs;

	while (true) {
		// VideoCapture cap(-1);
		cap >> frame;
		resize(frame, frame, Size(width, height));

		dnn::blobFromImage(frame, blob, 1 / 255.0, Size(416, 416), Scalar(), true, false);
		net.setInput(blob);

		net.forward(outs, getOutPutsNames(net));

		PostProcess(frame, outs);
		imshow("result", frame);
		outs.clear();
		
		if (waitKey(10) == 27) {
			break;
		}
	}
		
	destroyAllWindows();
	return 0;
}