#pragma once
#include "Graphics.h"
#include "Ship.h"
class Speeder
{
public:
	void Init(float in_x, float in_y);
	void Draw(Graphics& gfx);
	void Move(float v, float deltaTime);
	void ShipCollision(Ship& ship);
	bool GetIsColliding();
	void SetIsColliding(bool boolean);
	float GetX();
	float GetY();
	float GetWidth();
	float GetHeight();
	bool GetShipColission();
	void SetShipColission(bool boolean);

private:
	float x;
	float y;
	float width = 25;
	float height = 25;
	bool isColliding = false;
	bool shipCollision = false;
};

