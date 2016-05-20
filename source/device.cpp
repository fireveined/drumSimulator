#include "device.h"
#include "drum.h"
CDevice device;
Mat getFrame() { return device.getFrame(); };
ISoundEngine* getSoundEngine() { return device.getSoundEngine(); };

void CallBackFunc(int ev, int x, int y, int flags, void* userdata)
{
	moveDrums(ev, x, y);

}

void CDevice::init()
{
	cap.open(0);
	sound_engine = createIrrKlangDevice();

	cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);

	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
	int dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); 
	int dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

	cout << "Frame size : " << dWidth << " x " << dHeight << endl;
	cout << "fps: " << cap.get(CV_CAP_PROP_ISO_SPEED);
	namedWindow("MyVideo", CV_WINDOW_AUTOSIZE);
	setMouseCallback("MyVideo", CallBackFunc, NULL);

}



void CDevice::run()
{
	bool bSuccess = cap.read(frame); 
	if (!bSuccess) 
	{
		cout << "Cannot read a frame from video stream" << endl;
	}
}