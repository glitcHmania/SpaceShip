#pragma once
#include "Graphics.h"
class Laser
{
public:
	void Init(int in_startX, int in_endX, int in_startY, int in_endY);
	void Fire(Graphics& gfx);
	bool GetIsFired();
	void SetIsFired(bool boolean);
private:
	int startX;
	int endX;
	int startY;
	int endY;
	bool isFired = false;
};

