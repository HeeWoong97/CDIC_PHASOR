#ifndef __FACE_YOLO_H__
#define __FACE_YOLO_H__

#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using namespace std;
using namespace cv;

std::string YOLO_CFG_PATH = "./face-yolov3-tiny.cfg";
std::string YOLO_WEIGHT_PATH = "./face-yolov3-tiny_41000.weights";
std::string YOLO_NAME_PATH = "./coco.names";
std::string test_file = "./pothole4.jpg";

int width = 640;
int height = 480;
float min_confidence = 0.5;
float nms_confidence = 0.4;


std::vector<String> getYOLONames(const std::string path);
std::vector<String> getOutPutsNames(const dnn::Net& net);
void PostProcess(Mat& frame, std::vector<Mat>& outs);
std::vector<string> classes = getYOLONames(YOLO_NAME_PATH);

#endif