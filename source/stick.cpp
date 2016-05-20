#include "stick.h"
#include "drum.h"
#include "opencv2/highgui/highgui.hpp"

#define is_green(x, y) getFrame().at<Vec3b>(y, x)[1]*0.7> getFrame().at<Vec3b>(y, x)[0] && getFrame().at<Vec3b>(y, x)[1]*0.7>getFrame().at<Vec3b>(y, x)[2]
#define is_blue(x, y) getFrame().at<Vec3b>(y, x)[0]*0.7> getFrame().at<Vec3b>(y, x)[1] && getFrame().at<Vec3b>(y, x)[0]*0.7>getFrame().at<Vec3b>(y, x)[2]

using namespace cv;

void CStick::update()
{
	int z = 122;
	int b = 180;

	std::vector<Point> points;
	std::vector<Point> points2;

	int x1 = 2, x2 = device.getWidth() - 2;
	int y1 = 2, y2 = device.getHeight() - 2;
	if (old_sticks[0].x != -1)
	{
		x1 = old_sticks[0].x - 60; x2 = old_sticks[0].x + 60;
		y1 = old_sticks[0].y - 70; y2 = old_sticks[0].y + 70;
	}

	for (int y = std::max(y1, 2); y < std::min(y2, device.getHeight() - 2); y += 3)
		for (int x = std::max(x1, 2); x < std::min(x2, device.getWidth() - 2); x += 3)
		{
			uchar g = getFrame().at<Vec3b>(y, x)[1];
			if (is_green(x, y) && is_green(x - 2, y) && is_green(x + 2, y) && is_green(x, y - 2) && is_green(x, y + 2))
				points.push_back(Point(x, y));
		}


	x1 = 2, x2 = device.getWidth() - 2;
	y1 = 2, y2 = device.getHeight() - 2;
	if (old_sticks[1].x != -1)
	{
		x1 = old_sticks[1].x - 60; x2 = old_sticks[1].x + 60;
		y1 = old_sticks[1].y - 70; y2 = old_sticks[1].y + 70;
	}

	for (int y = std::max(y1, 2); y < std::min(y2, device.getHeight() - 2); y += 3)
		for (int x = std::max(x1, 2); x < std::min(x2, device.getWidth() - 2); x += 3)
		{
			uchar g = getFrame().at<Vec3b>(y, x)[2];
			if (is_blue(x, y) && is_blue(x - 2, y) && is_blue(x + 2, y) && is_blue(x, y - 2) && is_blue(x, y + 2))
				points2.push_back(Point(x, y));
		}


	int x = 0, y = 0;
	for (int a = 0; a < points.size(); a++)
		x += points[a].x, y += points[a].y;
	if (points.size() > 0)
	{
		old_sticks[0] = sticks[0];
		sticks[0].x = x / points.size();
		sticks[0].y = y / points.size();
		for (int z = 0; z < 14; z++)
			speeds[0][z + 1] = speeds[0][z];
		Point dis = sticks[0] - old_sticks[0];
		speeds[0][0] = abs(sqrt(float(dis.x*dis.x + dis.y*dis.y)));

	}
	else
		old_sticks[0].x = -1;

	x = 0, y = 0;
	for (int a = 0; a < points2.size(); a++)
		x += points2[a].x, y += points2[a].y;
	if (points2.size() > 0)
	{
		old_sticks[1] = sticks[1];
		sticks[1].x = x / points2.size();
		sticks[1].y = y / points2.size();
		for (int z = 0; z < 14; z++)
			speeds[1][z + 1] = speeds[1][z];
		Point dis = sticks[1] - old_sticks[1];
		speeds[1][0] = abs(sqrt(float(dis.x*dis.x + dis.y*dis.y)));
		//ISound* sound = getSoundEngine()->play2D(drums[a].sound.c_str(),false, true, true);
	}
	else
		old_sticks[1].x = -1;

}

float CStick::getSpeed(int sti)
{
	float s = 1;
	for (int z = 0; z < 4; z++)
		s += speeds[sti][z] / 4.0f;
	return s;
}

void CStick::draw()
{

	rectangle(getFrame(),
		Rect(sticks[0], Size(4, 4)),
		Scalar(0, 255, 0),
		2,
		8);

	rectangle(getFrame(),
		Rect(sticks[1], Size(4, 4)), 
		Scalar(0, 0, 255),
		2,
		8);
}