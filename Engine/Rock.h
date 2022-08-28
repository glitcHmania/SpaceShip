#pragma once
#include "Ion.h"
#include <random>
#include "Graphics.h"
#include "Ship.h"
class Rock
{
public:
	void Init(float in_x, float in_y);
	void Draw(Graphics& gfx);
	void Move(float v, float deltaTime);
	void ShipCollision(Ship& ship);
	bool GetIonRockCollision();
	void SetIonRockCollision(bool boolean);
	float GetX();
	float GetY();
	float GetWidth();
	float GetHeight();
	bool GetShipColission();
private:
	float x;
	float y;
	float width = 20;
	float height = 20;
	bool ionRockCollision = false;
	bool shipCollision = false;
};

