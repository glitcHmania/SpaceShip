/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	ship(10,10)
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	ship.ProcessMovement(wnd,gfx);
	ship.ClampScreen(gfx);
	fireCounter++;
	
	if (wnd.kbd.KeyIsPressed(VK_SPACE))
	{
		laserIndex++;
		if (fireCounter > fireCounterLimit)
		{
			lasers[laserIndex].Init(
				ship.GetX() + ship.GetWidth(),
				gfx.ScreenWidth,
				ship.GetY() + ship.GetHeight() / 2 - 1,
				ship.GetY() + ship.GetHeight() / 2 + 1);
			fireCounter = 0;
		}
		lasers[laserIndex].SetIsFired(true);
	}

	for (int t = 0; t <= laserIndex; ++t)
	{
		if (lasers[t].GetIsFired())
		{
			lasers[t].Fire(gfx);
		}
	}
}

void Game::ComposeFrame()
{
	gfx.DrawShip(ship.GetX(),ship.GetY());
}
