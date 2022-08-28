#pragma once
#include "Graphics.h"
#include "Colors.h"
#include "MainWindow.h"
class Ship
{
public:
	Ship(float in_x, float in_y);
	void Draw(Graphics& gfx, float x, float y);
	void ProcessMovement(const MainWindow& wnd, const Graphics& gfx, float deltaTime);
	void ClampScreen(const Graphics& gfx);
	float GetX();
	float GetY();
	float GetWidth();
	float GetHeight();
	void fixSpeed(Keyboard& kbd, float new_v);
private:
	bool hasFired = false;
	float x;
	float y;
	float width = 45;
	float height = 44;
	float v;
};

