#include "Laser.h"

void Laser::Init(int in_startX, int in_endX, int in_startY, int in_endY)
{
	startX = in_startX;
	endX = in_endX;
	startY = in_startY;
	endY = in_endY;
}

void Laser::Fire(Graphics& gfx)
{
	for (int i = startX; i < startX + 15; ++i)
	{

		for (int j = startY; j < endY; ++j)
		{
			if (i < gfx.ScreenWidth)
			{
				gfx.PutPixel(i, j, Colors::Red);
			}
		}

	}
	startX++;
}

bool Laser::GetIsFired()
{
	return isFired;
}

void Laser::SetIsFired(bool boolean)
{
	isFired = boolean;
}
