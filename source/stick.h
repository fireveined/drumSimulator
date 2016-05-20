#ifndef CSTICK_H
#define CSTICK_H

#include "device.h"
#include <iostream>

class CStick
{

public:
	Point sticks[2];
	Point old_sticks[2];
	float speeds[2][15];
	void update();
	void draw();
	float getSpeed(int spi);
};

#endif