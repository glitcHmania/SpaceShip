#pragma once
#include "Graphics.h"
#include "Colors.h"
#include "MainWindow.h"
class Ship
{
public:
	Ship(int in_x,int in_y);
	void Draw(Graphics& gfx);
	void ProcessMovement(const MainWindow& wnd, const Graphics& gfx);
	void ClampScreen(const Graphics& gfx);
	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();
private:
	bool hasFired = false;
	int x;
	int y;
	int width = 45;
	int height = 44;
	int v;
	
};

