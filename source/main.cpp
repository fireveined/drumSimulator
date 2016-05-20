#include "device.h"
#include <iostream>
#include "stick.h"
#include "drum.h"



int main(int argc, char* argv[])
{


	device.init();
	CStick sticks;

	drums.push_back(CDrum(Point(20, 10), Size(20, 30), "data/snare.wav", Scalar(10, 80, 170)));
	drums.push_back(CDrum(Point(40, 50), Size(10, 30), "data/openh.wav", Scalar(0, 255, 255)));
	drums.push_back(CDrum(Point(170, 50), Size(10, 30), "data/crash.wav", Scalar(0, 170, 170)));
	drums.push_back(CDrum(Point(270, 50), Size(10, 30), "data/bass.wav", Scalar(0, 0, 0)));

	while (1)
	{

		device.run();


		sticks.update();
		sticks.draw();

		manageDrums(sticks);
		imshow("MyVideo", getFrame()); 

		waitKey(1);


	}
	return 0;

}