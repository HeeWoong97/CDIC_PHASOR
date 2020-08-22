#include <opencv2/opencv.hpp>
#include <iostream>
#include "./opencv/face_yolo.hpp"
#include <time.h>

using namespace cv;
using namespace std;

int main()
{
	dnn::Net net = dnn::readNetFromDarknet(YOLO_CFG_PATH, YOLO_WEIGHT_PATH);
	net.setPreferableBackend(dnn::DNN_BACKEND_OPENCV);
	net.setPreferableTarget(dnn::DNN_TARGET_CPU);
	
	int loop = 1;
	clock_t start;
	clock_t end;
	clock_t loopStart;
	clock_t loopEnd;
	clock_t totalStart;
	clock_t totalEnd;

	VideoCapture cap(-1);

	Mat blob;
	Mat frame;

	std::vector<Mat> outs;

	totalStart = clock();

	while (true) {
		cout << "========== loop: " << loop << " ==========" << endl;

		loopStart = clock();

		cap >> frame;
		resize(frame, frame, Size(width, height));

		start = clock();
		dnn::blobFromImage(frame, blob, 1 / 255.0, Size(416, 416), Scalar(), true, false);
		net.setInput(blob);
		end = clock();
		printf("\nblobFromImage Time: %lf s\n", (double)(end - start)/CLOCKS_PER_SEC);
		
		start = clock();
		net.forward(outs, getOutPutsNames(net));
		end = clock();
		printf("\nforward Time: %lf s\n", (double)(end - start)/CLOCKS_PER_SEC);
		
		start = clock();
		PostProcess(frame, outs);
		end = clock();
		printf("\nPostProcess Time: %lf s\n", (double)(end - start)/CLOCKS_PER_SEC);
		
		start = clock();
		// imshow("result", frame);
		outs.clear();
		end = clock();
		printf("\nimShow Time: %lf s\n", (double)(end - start)/CLOCKS_PER_SEC);

		start = clock();
		if (waitKey(300) == 27) {
			break;
		}
		end = clock();
		printf("\nwaitKey Time: %lf\n", (double)(end - start)/CLOCKS_PER_SEC);
		
		loopEnd = clock();
		printf("\ntotal loop Time: %lf\n", (double)(loopEnd - loopStart)/CLOCKS_PER_SEC);
		
		totalEnd = clock();
		printf("\ntotal Time until loop %d: %lf\n\n", loop, (double)(totalEnd - totalStart)/CLOCKS_PER_SEC);

		loop++;
	}
		
	// destroyAllWindows();
	return 0;
}