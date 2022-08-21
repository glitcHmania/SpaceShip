#pragma once
#include "Ion.h"
#include <random>
#include "Graphics.h"
#include "Ship.h"
class Rock
{
public:
	void Init(int in_x, int in_y);
	void Draw(Graphics& gfx);
	void Move();
	void ShipCollision(Ship& ship);
	bool GetIonRockCollision();
	void SetIonRockCollision(bool boolean);
	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();
	bool GetShipColission();
private:
	int x;
	int y;
	int width = 20;
	int height = 20;
	bool ionRockCollision = false;
	bool shipCollision = false;
};

