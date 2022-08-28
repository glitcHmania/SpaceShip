#pragma once
#include "Graphics.h"
#include "Rock.h"
#include "Colors.h"
class Ion
{
public:
	void Init(float in_startX, float in_endX, float in_startY, float in_endY, Color in_color, float in_velocity);
	void Fire(Graphics& gfx, float deltaTime);
	bool GetIsCharged();
	void SetIsCharged(bool boolean);
	bool GetIsColliding();
	float GetStartX();
	float GetStartY();
	float GetEndY();
private:
	Color color = Colors::Red;
	float startX;
	float endX;
	float startY;
	float endY;
	float velocity = 300;
	bool isCharged = false;
	bool isColliding = false;
};
