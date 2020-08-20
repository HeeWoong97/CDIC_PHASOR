#include "face_yolo.h"

void PostProcess(Mat& frame, std::vector<Mat>& outs) {
	std::vector<String> names;
	std::vector<float> confidences;
	std::vector<Rect> boxes;

	for (size_t i = 0; i < outs.size(); i++) {
		float* data = (float*)outs[i].data;
		for (int j = 0; j < outs[i].rows; ++j, data += outs[i].cols)
		{
			Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
			Point classId;
			double confidence;
			minMaxLoc(scores, 0, &confidence, 0, &classId);
			if (confidence > min_confidence) {
				int center_x = (int)(data[0] * width) < 0 ? 0 : (int)(data[0] * width);
				int center_y = (int)(data[1] * height) < 0 ? 0 : (int)(data[1] * height);
				int w = center_x + int(data[2] * width) > frame.cols ? frame.cols - center_x : int(data[2] * width);
				int h = center_y + int(data[3] * height) > frame.rows ? frame.rows - center_y : int(data[3] * height);
				int left = center_x - w / 2 < 0 ? 0 : center_x - w / 2;
				int top = center_y - h / 2 < 0 ? 0 : center_y - h / 2;

				confidences.push_back((float)confidence);
				boxes.push_back(Rect(left, top, w, h));
				names.push_back(classes[classId.x]);
			}
		}
	}
	std::vector<int> indices;
	dnn::NMSBoxes(boxes, confidences, min_confidence, nms_confidence, indices);
	cout << "num of faces: " << indices.size() << endl;

	

	for (size_t i = 0; i < indices.size(); i++) {
		int idx = indices[i];
		Rect box = boxes[idx];
		String label = names[i];
		cout << box.x << " " << box.y << " " << box.width << " " << box.height << endl;
		//imshow(label, frame(Rect(box.x, box.y, box.width, box.height)));
		rectangle(frame, Point(box.x, box.y), Point(box.x + box.width, box.y + box.height), Scalar(0, 0, 255));
		putText(frame, label, Point(box.x, box.y), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255));
	}
}
std::vector<String> getYOLONames(const std::string path) {
	std::vector<String> classes;
	std::ifstream f;
	std::string line;
	f.open(path);
	if (!f) {
		std::cout << "YOLO-Name file is not opened" << std::endl;
		exit(0);
	}
	while (getline(f, line)) {
		classes.push_back(line);
	}
	f.close();
	return classes;
}

std::vector<String> getOutPutsNames(const dnn::Net& net) {
	vector<String> names;
	if (names.empty()) {
		std::vector<int> outLayers = net.getUnconnectedOutLayers();
		std::vector<String> layersNames = net.getLayerNames();
		names.resize(outLayers.size());
		for (size_t i = 0; i < outLayers.size(); i++) {
			names[i] = layersNames[outLayers[i] - 1];
		}
	}
	return names;
}