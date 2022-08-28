#include "Ion.h"

void Ion::Init(float in_startX, float in_endX, float in_startY, float in_endY, Color in_color, float in_velocity)
{
	startX = in_startX;
	endX = in_endX;
	startY = in_startY;
	endY = in_endY;
	color = in_color;
	velocity = in_velocity;
}

void Ion::Fire(Graphics& gfx, float deltaTime)
{
	for (float i = startX; i < startX + 15; ++i)
	{

		for (float j = startY; j < endY; ++j)
		{
			if (i < gfx.ScreenWidth)
			{
				int i_int = int(i);
				int j_int = int(j);
				gfx.PutPixel(i_int, j_int, color);
			}
		}

	}
	startX += velocity * deltaTime;
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

float Ion::GetStartX()
{
	return startX;
}

float Ion::GetStartY()
{
	return startY;
}

float Ion::GetEndY()
{
	return endY;
}

