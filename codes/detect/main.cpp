#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include "./opencv/find_pothole.hpp"
#include <time.h>

using namespace cv;
using namespace std;

Mat rotate(Mat src, double angle)
{
	Mat dst;
	Point2f pt(src.cols/2., src.rows/2.);
	Mat r = getRotationMatrix2D(pt, angle, 1.0);
	warpAffine(src, dst, r, Size(src.cols, src.rows));

	return dst;
}

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
	Mat src;

	std::vector<Mat> outs;

	totalStart = clock();

	while (true) {
		cout << "========== loop: " << loop << " ==========" << endl;

		loopStart = clock();

		cap >> frame;
		frame = rotate(frame, 180);
		src = frame.clone();
		cvtColor(frame, src, COLOR_BGR2GRAY);

		resize(src, src, Size(width, height));

		start = clock();
		dnn::blobFromImage(src, blob, 1 / 255.0, Size(416, 416), Scalar(), true, false);
		net.setInput(blob);
		end = clock();
		printf("\nblobFromImage Time: %lf s\n", (double)(end - start)/CLOCKS_PER_SEC);
		
		start = clock();
		net.forward(outs, getOutPutsNames(net));
		end = clock();
		printf("\nforward Time: %lf s\n", (double)(end - start)/CLOCKS_PER_SEC);
		
		start = clock();
		PostProcess(frame, outs);
		imshow("result", frame);
		end = clock();
		printf("\nPostProcess Time: %lf s\n", (double)(end - start)/CLOCKS_PER_SEC);
		
		start = clock();
		outs.clear();
		end = clock();
		printf("\nimShow Time: %lf s\n", (double)(end - start)/CLOCKS_PER_SEC);

		start = clock();
		if (waitKey(30) == 27) {
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
		
	destroyAllWindows();
	return 0;
}
