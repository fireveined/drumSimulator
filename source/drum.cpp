#include "drum.h"
#include "stick.h"

std::vector<CDrum> drums;

void CDrum::create(Point pos, Size siz, string s, Scalar col)
{
	position = pos;
	size = siz;
	sound = s;
	color = col;
}


void CDrum::draw()
{
	rectangle(getFrame(),
		Rect(position, size),
		color,
		2,
		8);
}


void manageDrums(CStick st)
{

	for (int a = 0; a < drums.size(); a++)
	{
		drums[a].draw();

		for (int s = 0; s < 2; s++)
			if (drums[a].getRect().contains(st.sticks[s]) && !drums[a].getRect().contains(st.old_sticks[s]))
			{
				ISound* sound = getSoundEngine()->play2D(drums[a].sound.c_str(), false, true, true);
				//sound->setVolume(min(st.getSpeed(s)/38.0f,1.0f)+0.1);		
				sound->setIsPaused(false);
				sound->drop();
			}

	}


}
int movingdrum = -1, movex, movey;

bool moveDrums(int ev, int x, int y)
{
	bool evgone = 0;
	if (ev == EVENT_LBUTTONDOWN)
	{
		for (int a = 0; a < drums.size(); a++)
		{
			if (drums[a].getRect().contains(Point(x, y)))movingdrum = a, movex = x - drums[a].position.x, movey = y - drums[a].position.y, evgone = 1;;
			if (Rect(drums[a].getRect().br() - Point(3, 3), Size(6, 6)).contains(Point(x, y)))movingdrum = a * 1000 + 1000, movex = drums[a].position.x, movey = drums[a].position.y, evgone = 1;
		}
	}

	if (movingdrum != -1 && ev == EVENT_MOUSEMOVE)
	{
		if (movingdrum < 1000)
		{
			drums[movingdrum].position.x = x - movex;
			drums[movingdrum].position.y = y - movey;
		}
		else
		{
			drums[movingdrum / 1000 - 1].size.width = x - movex;
			drums[movingdrum / 1000 - 1].size.height = y - movey;
		}
	}

	if (ev == EVENT_LBUTTONUP)
	{
		movingdrum = -1;
	}


	return evgone;
}