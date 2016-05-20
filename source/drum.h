#ifndef CDRUM_H
#define CDRUM_H

#include "device.h"
#include <iostream>
#include "stick.h"


class CDrum
{

public:

	Point position;
	Size size;
	Scalar color;
	string sound;


	void create(Point pos, Size siz, string s, Scalar col);
	CDrum(Point pos, Size siz, string s, Scalar col) { create(pos, siz, s, col); };
	void draw();
	Rect getRect() { return Rect(position, size); };

};
extern std::vector<CDrum> drums;
void manageDrums(CStick st);

bool moveDrums(int ev, int x, int y);

#endif