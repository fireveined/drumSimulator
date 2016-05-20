#ifndef CDEVICE_H
#define CDEVICE_H

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <algorithm>
#include <irrKlang.h>

#pragma comment(lib, "irrKlang.lib")

using namespace irrklang;
using namespace cv;
using namespace std;

class CDevice
{
public:
	Mat frame;
	VideoCapture cap;
	ISoundEngine* sound_engine;

	void run();
	void init();
	Mat getFrame() { return frame; }
	ISoundEngine* getSoundEngine() { return sound_engine; }
	int getWidth() { return cap.get(CV_CAP_PROP_FRAME_WIDTH); };
	int getHeight() { return cap.get(CV_CAP_PROP_FRAME_HEIGHT); };
};

extern CDevice device;
Mat getFrame();
ISoundEngine* getSoundEngine();

#endif
