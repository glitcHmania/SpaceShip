#include "Ion.h"

void Ion::Init(int in_startX, int in_endX, int in_startY, int in_endY, Color in_color, int in_velocity)
{
	startX = in_startX;
	endX = in_endX;
	startY = in_startY;
	endY = in_endY;
	color = in_color;
	velocity = in_velocity;
}

void Ion::Fire(Graphics& gfx)
{
	for (int i = startX; i < startX + 15; ++i)
	{

		for (int j = startY; j < endY; ++j)
		{
			if (i < gfx.ScreenWidth)
			{
				gfx.PutPixel(i, j, color);
			}
		}

	}
	startX += velocity;
}

bool Ion::GetIsCharged()
{
	return isCharged;
}

void Ion::SetIsCharged(bool boolean)
{
	isCharged = boolean;
}

bool Ion::GetIsColliding()
{
	return isColliding;
}

int Ion::GetStartX()
{
	return startX;
}

int Ion::GetStartY()
{
	return startY;
}

int Ion::GetEndY()
{
	return endY;
}

