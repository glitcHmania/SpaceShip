#include "Ship.h"

Ship::Ship(int in_x, int in_y)
{
	x = in_x;
	y = in_y;
}

void Ship::Draw(Graphics& gfx)
{
	for (int i = x; i < x + width; ++i)
	{
		for (int j = y; j < y + height; ++j)
		{
			gfx.PutPixel(i, j, Colors::White);
		}
	}
}

void Ship::ProcessMovement(const MainWindow& wnd, const Graphics& gfx)
{
	if (wnd.kbd.KeyIsPressed(VK_SPACE))
	{
		v = 1;
	}
	else
	{
		v = 3;
	}
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		y = y - v;
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		y = y + v;
	}
}

void Ship::ClampScreen(const Graphics& gfx)
{
	if (y > gfx.ScreenHeight-height-10)
	{
		y = gfx.ScreenHeight-height-10;
	}
	if (y < 10)
	{
		y = 10;
	}
}

int Ship::GetX()
{
	return x;
}

int Ship::GetY()
{
	return y;
}

int Ship::GetWidth()
{
	return width;
}

int Ship::GetHeight()
{
	return height;
}

