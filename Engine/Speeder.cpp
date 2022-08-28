#include "Speeder.h"

void Speeder::Init(float in_x, float in_y)
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
		int x_int = int(x);
		int y_int = int(y);
		gfx.PutPixel(2 + x_int, 2 + y_int, 0, 1, 0);
		gfx.PutPixel(7 + x_int, 2 + y_int, 1, 3, 0);
		gfx.PutPixel(8 + x_int, 2 + y_int, 0, 4, 0);
		gfx.PutPixel(1 + x_int, 3 + y_int, 30, 255, 0);
		gfx.PutPixel(2 + x_int, 3 + y_int, 30, 255, 0);
		gfx.PutPixel(3 + x_int, 3 + y_int, 0, 1, 0);
		gfx.PutPixel(7 + x_int, 3 + y_int, 30, 255, 0);
		gfx.PutPixel(8 + x_int, 3 + y_int, 30, 255, 0);
		gfx.PutPixel(9 + x_int, 3 + y_int, 1, 5, 0);
		gfx.PutPixel(10 + x_int, 3 + y_int, 1, 2, 0);
		gfx.PutPixel(1 + x_int, 4 + y_int, 0, 1, 0);
		gfx.PutPixel(2 + x_int, 4 + y_int, 30, 255, 0);
		gfx.PutPixel(3 + x_int, 4 + y_int, 30, 255, 0);
		gfx.PutPixel(4 + x_int, 4 + y_int, 30, 255, 0);
		gfx.PutPixel(5 + x_int, 4 + y_int, 0, 1, 0);
		gfx.PutPixel(7 + x_int, 4 + y_int, 1, 4, 0);
		gfx.PutPixel(8 + x_int, 4 + y_int, 30, 255, 0);
		gfx.PutPixel(9 + x_int, 4 + y_int, 30, 255, 0);
		gfx.PutPixel(10 + x_int, 4 + y_int, 30, 255, 0);
		gfx.PutPixel(11 + x_int, 4 + y_int, 1, 6, 0);
		gfx.PutPixel(12 + x_int, 4 + y_int, 1, 1, 0);
		gfx.PutPixel(2 + x_int, 5 + y_int, 0, 1, 0);
		gfx.PutPixel(3 + x_int, 5 + y_int, 0, 1, 0);
		gfx.PutPixel(4 + x_int, 5 + y_int, 30, 255, 0);
		gfx.PutPixel(5 + x_int, 5 + y_int, 30, 255, 0);
		gfx.PutPixel(6 + x_int, 5 + y_int, 30, 255, 0);
		gfx.PutPixel(7 + x_int, 5 + y_int, 0, 1, 0);
		gfx.PutPixel(8 + x_int, 5 + y_int, 2, 5, 0);
		gfx.PutPixel(9 + x_int, 5 + y_int, 1, 8, 0);
		gfx.PutPixel(10 + x_int, 5 + y_int, 30, 255, 0);
		gfx.PutPixel(11 + x_int, 5 + y_int, 30, 255, 0);
		gfx.PutPixel(12 + x_int, 5 + y_int, 30, 255, 0);
		gfx.PutPixel(13 + x_int, 5 + y_int, 1, 3, 0);
		gfx.PutPixel(6 + x_int, 6 + y_int, 30, 255, 0);
		gfx.PutPixel(7 + x_int, 6 + y_int, 30, 255, 0);
		gfx.PutPixel(8 + x_int, 6 + y_int, 30, 255, 0);
		gfx.PutPixel(9 + x_int, 6 + y_int, 0, 1, 0);
		gfx.PutPixel(10 + x_int, 6 + y_int, 0, 1, 0);
		gfx.PutPixel(11 + x_int, 6 + y_int, 0, 1, 0);
		gfx.PutPixel(12 + x_int, 6 + y_int, 30, 255, 0);
		gfx.PutPixel(13 + x_int, 6 + y_int, 30, 255, 0);
		gfx.PutPixel(14 + x_int, 6 + y_int, 30, 255, 0);
		gfx.PutPixel(15 + x_int, 6 + y_int, 1, 7, 0);
		gfx.PutPixel(16 + x_int, 6 + y_int, 0, 1, 0);
		gfx.PutPixel(7 + x_int, 7 + y_int, 0, 2, 0);
		gfx.PutPixel(8 + x_int, 7 + y_int, 30, 255, 0);
		gfx.PutPixel(9 + x_int, 7 + y_int, 30, 255, 0);
		gfx.PutPixel(10 + x_int, 7 + y_int, 30, 255, 0);
		gfx.PutPixel(11 + x_int, 7 + y_int, 1, 1, 0);
		gfx.PutPixel(12 + x_int, 7 + y_int, 1, 2, 0);
		gfx.PutPixel(13 + x_int, 7 + y_int, 1, 12, 0);
		gfx.PutPixel(14 + x_int, 7 + y_int, 30, 255, 0);
		gfx.PutPixel(15 + x_int, 7 + y_int, 30, 255, 0);
		gfx.PutPixel(16 + x_int, 7 + y_int, 30, 255, 0);
		gfx.PutPixel(17 + x_int, 7 + y_int, 0, 1, 0);
		gfx.PutPixel(8 + x_int, 8 + y_int, 0, 1, 0);
		gfx.PutPixel(9 + x_int, 8 + y_int, 30, 253, 0);
		gfx.PutPixel(10 + x_int, 8 + y_int, 30, 255, 0);
		gfx.PutPixel(11 + x_int, 8 + y_int, 30, 255, 0);
		gfx.PutPixel(14 + x_int, 8 + y_int, 1, 9, 0);
		gfx.PutPixel(15 + x_int, 8 + y_int, 30, 253, 0);
		gfx.PutPixel(16 + x_int, 8 + y_int, 30, 255, 0);
		gfx.PutPixel(17 + x_int, 8 + y_int, 30, 255, 0);
		gfx.PutPixel(18 + x_int, 8 + y_int, 0, 1, 0);
		gfx.PutPixel(9 + x_int, 9 + y_int, 1, 5, 0);
		gfx.PutPixel(10 + x_int, 9 + y_int, 30, 254, 0);
		gfx.PutPixel(11 + x_int, 9 + y_int, 30, 255, 0);
		gfx.PutPixel(12 + x_int, 9 + y_int, 30, 255, 0);
		gfx.PutPixel(15 + x_int, 9 + y_int, 3, 21, 0);
		gfx.PutPixel(16 + x_int, 9 + y_int, 30, 254, 0);
		gfx.PutPixel(17 + x_int, 9 + y_int, 30, 255, 0);
		gfx.PutPixel(18 + x_int, 9 + y_int, 30, 255, 0);
		gfx.PutPixel(8 + x_int, 10 + y_int, 1, 7, 0);
		gfx.PutPixel(9 + x_int, 10 + y_int, 30, 252, 0);
		gfx.PutPixel(10 + x_int, 10 + y_int, 30, 255, 0);
		gfx.PutPixel(11 + x_int, 10 + y_int, 30, 255, 0);
		gfx.PutPixel(14 + x_int, 10 + y_int, 4, 28, 0);
		gfx.PutPixel(15 + x_int, 10 + y_int, 30, 252, 0);
		gfx.PutPixel(16 + x_int, 10 + y_int, 30, 255, 0);
		gfx.PutPixel(17 + x_int, 10 + y_int, 30, 255, 0);
		gfx.PutPixel(18 + x_int, 10 + y_int, 1, 2, 0);
		gfx.PutPixel(6 + x_int, 11 + y_int, 0, 2, 0);
		gfx.PutPixel(7 + x_int, 11 + y_int, 0, 2, 0);
		gfx.PutPixel(8 + x_int, 11 + y_int, 30, 255, 0);
		gfx.PutPixel(9 + x_int, 11 + y_int, 30, 255, 0);
		gfx.PutPixel(10 + x_int, 11 + y_int, 30, 253, 0);
		gfx.PutPixel(11 + x_int, 11 + y_int, 1, 5, 0);
		gfx.PutPixel(12 + x_int, 11 + y_int, 1, 11, 0);
		gfx.PutPixel(13 + x_int, 11 + y_int, 1, 13, 0);
		gfx.PutPixel(14 + x_int, 11 + y_int, 30, 255, 0);
		gfx.PutPixel(15 + x_int, 11 + y_int, 30, 255, 0);
		gfx.PutPixel(16 + x_int, 11 + y_int, 30, 253, 0);
		gfx.PutPixel(17 + x_int, 11 + y_int, 3, 19, 0);
		gfx.PutPixel(18 + x_int, 11 + y_int, 0, 2, 0);
		gfx.PutPixel(5 + x_int, 12 + y_int, 0, 3, 0);
		gfx.PutPixel(6 + x_int, 12 + y_int, 30, 255, 0);
		gfx.PutPixel(7 + x_int, 12 + y_int, 30, 255, 0);
		gfx.PutPixel(8 + x_int, 12 + y_int, 30, 254, 0);
		gfx.PutPixel(9 + x_int, 12 + y_int, 0, 1, 0);
		gfx.PutPixel(10 + x_int, 12 + y_int, 1, 2, 0);
		gfx.PutPixel(11 + x_int, 12 + y_int, 2, 15, 0);
		gfx.PutPixel(12 + x_int, 12 + y_int, 30, 255, 0);
		gfx.PutPixel(13 + x_int, 12 + y_int, 30, 255, 0);
		gfx.PutPixel(14 + x_int, 12 + y_int, 30, 254, 0);
		gfx.PutPixel(15 + x_int, 12 + y_int, 1, 5, 0);
		gfx.PutPixel(16 + x_int, 12 + y_int, 0, 1, 0);
		gfx.PutPixel(2 + x_int, 13 + y_int, 0, 1, 0);
		gfx.PutPixel(3 + x_int, 13 + y_int, 0, 2, 0);
		gfx.PutPixel(4 + x_int, 13 + y_int, 30, 255, 0);
		gfx.PutPixel(5 + x_int, 13 + y_int, 30, 255, 0);
		gfx.PutPixel(6 + x_int, 13 + y_int, 30, 254, 0);
		gfx.PutPixel(7 + x_int, 13 + y_int, 0, 4, 0);
		gfx.PutPixel(8 + x_int, 13 + y_int, 1, 10, 0);
		gfx.PutPixel(9 + x_int, 13 + y_int, 1, 10, 0);
		gfx.PutPixel(10 + x_int, 13 + y_int, 30, 255, 0);
		gfx.PutPixel(11 + x_int, 13 + y_int, 30, 255, 0);
		gfx.PutPixel(12 + x_int, 13 + y_int, 30, 254, 0);
		gfx.PutPixel(13 + x_int, 13 + y_int, 1, 15, 0);
		gfx.PutPixel(14 + x_int, 13 + y_int, 2, 19, 0);
		gfx.PutPixel(1 + x_int, 14 + y_int, 0, 2, 0);
		gfx.PutPixel(2 + x_int, 14 + y_int, 30, 255, 0);
		gfx.PutPixel(3 + x_int, 14 + y_int, 30, 255, 0);
		gfx.PutPixel(4 + x_int, 14 + y_int, 30, 255, 0);
		gfx.PutPixel(7 + x_int, 14 + y_int, 1, 12, 0);
		gfx.PutPixel(8 + x_int, 14 + y_int, 30, 255, 0);
		gfx.PutPixel(9 + x_int, 14 + y_int, 30, 255, 0);
		gfx.PutPixel(10 + x_int, 14 + y_int, 30, 255, 0);
		gfx.PutPixel(11 + x_int, 14 + y_int, 1, 3, 0);
		gfx.PutPixel(12 + x_int, 14 + y_int, 0, 1, 0);
		gfx.PutPixel(1 + x_int, 15 + y_int, 30, 255, 0);
		gfx.PutPixel(2 + x_int, 15 + y_int, 30, 255, 0);
		gfx.PutPixel(3 + x_int, 15 + y_int, 0, 3, 0);
		gfx.PutPixel(4 + x_int, 15 + y_int, 0, 1, 0);
		gfx.PutPixel(7 + x_int, 15 + y_int, 30, 255, 0);
		gfx.PutPixel(8 + x_int, 15 + y_int, 30, 255, 0);
		gfx.PutPixel(9 + x_int, 15 + y_int, 2, 15, 0);
		gfx.PutPixel(10 + x_int, 15 + y_int, 1, 4, 0);
		gfx.PutPixel(1 + x_int, 16 + y_int, 0, 3, 0);
		gfx.PutPixel(2 + x_int, 16 + y_int, 0, 1, 0);
		gfx.PutPixel(7 + x_int, 16 + y_int, 2, 15, 0);
		gfx.PutPixel(8 + x_int, 16 + y_int, 1, 6, 0);

	}
}

void Speeder::Move(float v, float deltaTime)
{
	x -= v * deltaTime;
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

float Speeder::GetX()
{
	return x;
}

float Speeder::GetY()
{
	return y;
}

float Speeder::GetWidth()
{
	return width;
}

float Speeder::GetHeight()
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
