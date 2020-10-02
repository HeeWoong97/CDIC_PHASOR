#include "PotholeDetection.hpp"
#include <utility>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <ctime>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	std::string YOLO_CFG_PATH;
	std::string YOLO_WEIGHT_PATH;
	std::string YOLO_NAME_PATH;

	if (argc < 2) {
		cout << "Not Option Error!!" << endl;
	}
	if (strcmp(argv[1], "real") == 0) {
		cout << "real" << endl;
		YOLO_CFG_PATH = "./cfg/phasor_real_local_gray.cfg";
		YOLO_WEIGHT_PATH = "./weight/phasor_real_local_gray.weights";
		YOLO_NAME_PATH = "./name/phasor-classes.names";
	}
	else if (strcmp(argv[1], "woodRock") == 0) {
		cout << "woodRock" << endl;
		YOLO_CFG_PATH = "./cfg/phasor_woodRock_local_gray.cfg";
		YOLO_WEIGHT_PATH = "./weight/phasor_woodRock_local_gray.weights";
		YOLO_NAME_PATH = "./name/phasor-classes.names";
	}

	PotholeDetection detector(YOLO_CFG_PATH, YOLO_WEIGHT_PATH, YOLO_NAME_PATH);
	detector.setMinConfidence(0.3);
	detector.setInputSize(Size(256, 256));
	
	VideoCapture cap(-1);
	Mat frame;
	double fps = cap.get(CAP_PROP_FPS);
	int delay = cvRound(1000 / fps);

	int lastCount = 0;

	while (true) {
		time_t start = clock();
		cap >> frame;
		if (frame.empty()) {
			break;
		}
		flip(frame, frame, 0);
		flip(frame, frame, 1);

		Mat src = frame.clone();
		detector.predict(src, true);
		detector.PostProcess(src);

		if (detector.outs.size() > 0 && detector.outs.size() > lastCount)  {
			// save img file
			string img_route;
			
			struct tm curr_tm;
			time_t curr_time = time(nullptr);

			localtime_r(&curr_time, &curr_tm);

			string curr_year = to_string(curr_tm.tm_year + 1900);
			string curr_month = to_string(curr_tm.tm_mon + 1);
			string curr_day = to_string(curr_tm.tm_mday);
			string curr_hour = to_string(curr_tm.tm_hour);
			string curr_minute = to_string(curr_tm.tm_min);
			string curr_second = to_string(curr_tm.tm_sec);

			img_route = "../images/" + curr_year + "-" + curr_month + "-" + curr_day + " " + curr_hour + ":" + curr_minute + ":" + curr_second + ".jpg";
		        char route[100];
			strcpy(route, img_route.c_str());
			cout << img_route << endl;
			imwrite(img_route, frame);
		
			/*
			string img_command = "python3 camera/takePicture.py ";
			img_command += img_route;
			char img_cmd[100];
			strcpy(img_cmd, img_command.c_str());
		        system(img_cmd);	
			cout << img_command << endl;
			*/

			// run index.py
			cout << "num of potholes: " << detector.outs.size() << endl;
			lastCount = detector.outs.size();
			string command = "python3 ../index.py ";
			string pothole_num = to_string(detector.outs.size());
			command += pothole_num;
			command = command + " " + "\'" + img_route + "\'";

			char cmd[100];
			strcpy(cmd, command.c_str());
			cout<< command << endl;
			system(cmd);	
		}
		lastCount = detector.outs.size();

		for (int i = 0; i < detector.outs.size(); i++) {
			Rect box = detector.outs[i];
			rectangle(frame, box, Scalar(92, 92, 205), 2);
		}

		imshow("result", frame);
		detector.outs.clear();
		
		if (waitKey(delay) == 27) {
			break;
		}
		time_t end = clock();
		cout << "Time: " << (double)(end - start)/CLOCKS_PER_SEC << endl;
	}

	cap.release();
	return 0;
}
