#pragma once
#include "Graphics.h"
#include "Ship.h"
class Speeder
{
public:
	void Init(int in_x, int in_y);
	void Draw(Graphics& gfx);
	void Move();
	void ShipCollision(Ship& ship);
	bool GetIsColliding();
	void SetIsColliding(bool boolean);
	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();
	bool GetShipColission();
	void SetShipColission(bool boolean);
	
private:
	int x;
	int y;
	int width = 25;
	int height = 25;
	bool isColliding = false;
	bool shipCollision = false;
};

