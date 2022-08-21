#pragma once
#include "Graphics.h"
#include "Rock.h"
#include "Colors.h"
class Ion
{
public:
	void Init(int in_startX, int in_endX, int in_startY, int in_endY, Color in_color, int in_velocity);
	void Fire(Graphics& gfx);
	bool GetIsCharged();
	void SetIsCharged(bool boolean);
	bool GetIsColliding();
	int GetStartX();
	int GetStartY();
	int GetEndY();
private:
	Color color = Colors::Red;
	int startX;
	int endX;
	int startY;
	int endY;
	int velocity = 2;
	bool isCharged = false;
	bool isColliding = false;
};
