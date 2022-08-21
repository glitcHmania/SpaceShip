#include "Speeder.h"

void Speeder::Init(int in_x, int in_y)
{
	x = in_x;
	y = in_y;
}

void Speeder::Draw(Graphics& gfx)
{
	if (
		x + width < gfx.ScreenWidth &&
		x>0 &&
		y + height < gfx.ScreenHeight &&
		y>0
		)
	{
		gfx.PutPixel(2 + x, 2 + y, 0, 1, 0);
		gfx.PutPixel(7 + x, 2 + y, 1, 3, 0);
		gfx.PutPixel(8 + x, 2 + y, 0, 4, 0);
		gfx.PutPixel(1 + x, 3 + y, 30, 255, 0);
		gfx.PutPixel(2 + x, 3 + y, 30, 255, 0);
		gfx.PutPixel(3 + x, 3 + y, 0, 1, 0);
		gfx.PutPixel(7 + x, 3 + y, 30, 255, 0);
		gfx.PutPixel(8 + x, 3 + y, 30, 255, 0);
		gfx.PutPixel(9 + x, 3 + y, 1, 5, 0);
		gfx.PutPixel(10 + x, 3 + y, 1, 2, 0);
		gfx.PutPixel(1 + x, 4 + y, 0, 1, 0);
		gfx.PutPixel(2 + x, 4 + y, 30, 255, 0);
		gfx.PutPixel(3 + x, 4 + y, 30, 255, 0);
		gfx.PutPixel(4 + x, 4 + y, 30, 255, 0);
		gfx.PutPixel(5 + x, 4 + y, 0, 1, 0);
		gfx.PutPixel(7 + x, 4 + y, 1, 4, 0);
		gfx.PutPixel(8 + x, 4 + y, 30, 255, 0);
		gfx.PutPixel(9 + x, 4 + y, 30, 255, 0);
		gfx.PutPixel(10 + x, 4 + y, 30, 255, 0);
		gfx.PutPixel(11 + x, 4 + y, 1, 6, 0);
		gfx.PutPixel(12 + x, 4 + y, 1, 1, 0);
		gfx.PutPixel(2 + x, 5 + y, 0, 1, 0);
		gfx.PutPixel(3 + x, 5 + y, 0, 1, 0);
		gfx.PutPixel(4 + x, 5 + y, 30, 255, 0);
		gfx.PutPixel(5 + x, 5 + y, 30, 255, 0);
		gfx.PutPixel(6 + x, 5 + y, 30, 255, 0);
		gfx.PutPixel(7 + x, 5 + y, 0, 1, 0);
		gfx.PutPixel(8 + x, 5 + y, 2, 5, 0);
		gfx.PutPixel(9 + x, 5 + y, 1, 8, 0);
		gfx.PutPixel(10 + x, 5 + y, 30, 255, 0);
		gfx.PutPixel(11 + x, 5 + y, 30, 255, 0);
		gfx.PutPixel(12 + x, 5 + y, 30, 255, 0);
		gfx.PutPixel(13 + x, 5 + y, 1, 3, 0);
		gfx.PutPixel(6 + x, 6 + y, 30, 255, 0);
		gfx.PutPixel(7 + x, 6 + y, 30, 255, 0);
		gfx.PutPixel(8 + x, 6 + y, 30, 255, 0);
		gfx.PutPixel(9 + x, 6 + y, 0, 1, 0);
		gfx.PutPixel(10 + x, 6 + y, 0, 1, 0);
		gfx.PutPixel(11 + x, 6 + y, 0, 1, 0);
		gfx.PutPixel(12 + x, 6 + y, 30, 255, 0);
		gfx.PutPixel(13 + x, 6 + y, 30, 255, 0);
		gfx.PutPixel(14 + x, 6 + y, 30, 255, 0);
		gfx.PutPixel(15 + x, 6 + y, 1, 7, 0);
		gfx.PutPixel(16 + x, 6 + y, 0, 1, 0);
		gfx.PutPixel(7 + x, 7 + y, 0, 2, 0);
		gfx.PutPixel(8 + x, 7 + y, 30, 255, 0);
		gfx.PutPixel(9 + x, 7 + y, 30, 255, 0);
		gfx.PutPixel(10 + x, 7 + y, 30, 255, 0);
		gfx.PutPixel(11 + x, 7 + y, 1, 1, 0);
		gfx.PutPixel(12 + x, 7 + y, 1, 2, 0);
		gfx.PutPixel(13 + x, 7 + y, 1, 12, 0);
		gfx.PutPixel(14 + x, 7 + y, 30, 255, 0);
		gfx.PutPixel(15 + x, 7 + y, 30, 255, 0);
		gfx.PutPixel(16 + x, 7 + y, 30, 255, 0);
		gfx.PutPixel(17 + x, 7 + y, 0, 1, 0);
		gfx.PutPixel(8 + x, 8 + y, 0, 1, 0);
		gfx.PutPixel(9 + x, 8 + y, 30, 253, 0);
		gfx.PutPixel(10 + x, 8 + y, 30, 255, 0);
		gfx.PutPixel(11 + x, 8 + y, 30, 255, 0);
		gfx.PutPixel(14 + x, 8 + y, 1, 9, 0);
		gfx.PutPixel(15 + x, 8 + y, 30, 253, 0);
		gfx.PutPixel(16 + x, 8 + y, 30, 255, 0);
		gfx.PutPixel(17 + x, 8 + y, 30, 255, 0);
		gfx.PutPixel(18 + x, 8 + y, 0, 1, 0);
		gfx.PutPixel(9 + x, 9 + y, 1, 5, 0);
		gfx.PutPixel(10 + x, 9 + y, 30, 254, 0);
		gfx.PutPixel(11 + x, 9 + y, 30, 255, 0);
		gfx.PutPixel(12 + x, 9 + y, 30, 255, 0);
		gfx.PutPixel(15 + x, 9 + y, 3, 21, 0);
		gfx.PutPixel(16 + x, 9 + y, 30, 254, 0);
		gfx.PutPixel(17 + x, 9 + y, 30, 255, 0);
		gfx.PutPixel(18 + x, 9 + y, 30, 255, 0);
		gfx.PutPixel(8 + x, 10 + y, 1, 7, 0);
		gfx.PutPixel(9 + x, 10 + y, 30, 252, 0);
		gfx.PutPixel(10 + x, 10 + y, 30, 255, 0);
		gfx.PutPixel(11 + x, 10 + y, 30, 255, 0);
		gfx.PutPixel(14 + x, 10 + y, 4, 28, 0);
		gfx.PutPixel(15 + x, 10 + y, 30, 252, 0);
		gfx.PutPixel(16 + x, 10 + y, 30, 255, 0);
		gfx.PutPixel(17 + x, 10 + y, 30, 255, 0);
		gfx.PutPixel(18 + x, 10 + y, 1, 2, 0);
		gfx.PutPixel(6 + x, 11 + y, 0, 2, 0);
		gfx.PutPixel(7 + x, 11 + y, 0, 2, 0);
		gfx.PutPixel(8 + x, 11 + y, 30, 255, 0);
		gfx.PutPixel(9 + x, 11 + y, 30, 255, 0);
		gfx.PutPixel(10 + x, 11 + y, 30, 253, 0);
		gfx.PutPixel(11 + x, 11 + y, 1, 5, 0);
		gfx.PutPixel(12 + x, 11 + y, 1, 11, 0);
		gfx.PutPixel(13 + x, 11 + y, 1, 13, 0);
		gfx.PutPixel(14 + x, 11 + y, 30, 255, 0);
		gfx.PutPixel(15 + x, 11 + y, 30, 255, 0);
		gfx.PutPixel(16 + x, 11 + y, 30, 253, 0);
		gfx.PutPixel(17 + x, 11 + y, 3, 19, 0);
		gfx.PutPixel(18 + x, 11 + y, 0, 2, 0);
		gfx.PutPixel(5 + x, 12 + y, 0, 3, 0);
		gfx.PutPixel(6 + x, 12 + y, 30, 255, 0);
		gfx.PutPixel(7 + x, 12 + y, 30, 255, 0);
		gfx.PutPixel(8 + x, 12 + y, 30, 254, 0);
		gfx.PutPixel(9 + x, 12 + y, 0, 1, 0);
		gfx.PutPixel(10 + x, 12 + y, 1, 2, 0);
		gfx.PutPixel(11 + x, 12 + y, 2, 15, 0);
		gfx.PutPixel(12 + x, 12 + y, 30, 255, 0);
		gfx.PutPixel(13 + x, 12 + y, 30, 255, 0);
		gfx.PutPixel(14 + x, 12 + y, 30, 254, 0);
		gfx.PutPixel(15 + x, 12 + y, 1, 5, 0);
		gfx.PutPixel(16 + x, 12 + y, 0, 1, 0);
		gfx.PutPixel(2 + x, 13 + y, 0, 1, 0);
		gfx.PutPixel(3 + x, 13 + y, 0, 2, 0);
		gfx.PutPixel(4 + x, 13 + y, 30, 255, 0);
		gfx.PutPixel(5 + x, 13 + y, 30, 255, 0);
		gfx.PutPixel(6 + x, 13 + y, 30, 254, 0);
		gfx.PutPixel(7 + x, 13 + y, 0, 4, 0);
		gfx.PutPixel(8 + x, 13 + y, 1, 10, 0);
		gfx.PutPixel(9 + x, 13 + y, 1, 10, 0);
		gfx.PutPixel(10 + x, 13 + y, 30, 255, 0);
		gfx.PutPixel(11 + x, 13 + y, 30, 255, 0);
		gfx.PutPixel(12 + x, 13 + y, 30, 254, 0);
		gfx.PutPixel(13 + x, 13 + y, 1, 15, 0);
		gfx.PutPixel(14 + x, 13 + y, 2, 19, 0);
		gfx.PutPixel(1 + x, 14 + y, 0, 2, 0);
		gfx.PutPixel(2 + x, 14 + y, 30, 255, 0);
		gfx.PutPixel(3 + x, 14 + y, 30, 255, 0);
		gfx.PutPixel(4 + x, 14 + y, 30, 255, 0);
		gfx.PutPixel(7 + x, 14 + y, 1, 12, 0);
		gfx.PutPixel(8 + x, 14 + y, 30, 255, 0);
		gfx.PutPixel(9 + x, 14 + y, 30, 255, 0);
		gfx.PutPixel(10 + x, 14 + y, 30, 255, 0);
		gfx.PutPixel(11 + x, 14 + y, 1, 3, 0);
		gfx.PutPixel(12 + x, 14 + y, 0, 1, 0);
		gfx.PutPixel(1 + x, 15 + y, 30, 255, 0);
		gfx.PutPixel(2 + x, 15 + y, 30, 255, 0);
		gfx.PutPixel(3 + x, 15 + y, 0, 3, 0);
		gfx.PutPixel(4 + x, 15 + y, 0, 1, 0);
		gfx.PutPixel(7 + x, 15 + y, 30, 255, 0);
		gfx.PutPixel(8 + x, 15 + y, 30, 255, 0);
		gfx.PutPixel(9 + x, 15 + y, 2, 15, 0);
		gfx.PutPixel(10 + x, 15 + y, 1, 4, 0);
		gfx.PutPixel(1 + x, 16 + y, 0, 3, 0);
		gfx.PutPixel(2 + x, 16 + y, 0, 1, 0);
		gfx.PutPixel(7 + x, 16 + y, 2, 15, 0);
		gfx.PutPixel(8 + x, 16 + y, 1, 6, 0);

	}
}

void Speeder::Move()
{
	x -= 2;
}

void Speeder::ShipCollision(Ship& ship)
{
	if (
		(x<ship.GetX() + ship.GetWidth() &&
			x + width > ship.GetX() &&
			y + height > ship.GetY() &&
			y < ship.GetY() + ship.GetHeight())
		)
	{
		shipCollision = true;
	}
}

bool Speeder::GetIsColliding()
{
	return isColliding;
}

void Speeder::SetIsColliding(bool boolean)
{
	isColliding = boolean;
}

int Speeder::GetX()
{
	return x;
}

int Speeder::GetY()
{
	return y;
}

int Speeder::GetWidth()
{
	return width;
}

int Speeder::GetHeight()
{
	return height;
}

bool Speeder::GetShipColission()
{
	return shipCollision;
}

void Speeder::SetShipColission(bool boolean)
{
	shipCollision = boolean;
}
