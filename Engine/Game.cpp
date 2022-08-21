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
	ship(10,gfx.ScreenHeight/2-22),
	rng(rd()),
	yDist(40,560)
{
	rocks[rockIndex].Init(820, yDist(rng));
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
	// Checking if "Enter" is pressed
	if (wnd.kbd.KeyIsPressed(VK_RETURN))
	{
		gameStarted = true;
	}

	// Calculating the collision of ship
	speeders[speederIndex].ShipCollision(ship);
	rocks[rockIndex].ShipCollision(ship);

	// Keeping the ship inside the screen
	ship.ClampScreen(gfx);

	// Incrementing the fireCounter to adjust fire rate
	fireCounter++;

	// Checking if the game started by pressing "Enter"
	if (gameStarted)
	{
		// Checking if the game is over
		if (!gameOver)
		{
			// Processing the movement of ship
			ship.ProcessMovement(wnd, gfx);

			// Making the existing rock move left
			rocks[rockIndex].Move();

			// Making the existing speeder move left
			speeders[speederIndex].Move();

			// Checking if the speeder is colliding with the ship
			// and increasing the fire rate
			if (speeders[speederIndex].GetShipColission())
			{
				fireCounterLimit = 20;
				ionColor = Colors::Green;
				ionVelocity = 5;
			}

			// Making the fire rate turn back to normal after a while
			if (speederRoundCounter % 19 == 0)
			{
				speeders[speederIndex].SetShipColission(false);
				fireCounterLimit = 150;
				ionColor = Colors::Red;
				ionVelocity = 2;
			}

			// Spawning the speeder
			if (speederRoundCounter % 13 == 0)
			{
				speederIndex++;
				speeders[speederIndex].Init(gfx.ScreenWidth, yDist(rng));
			}

			// Checking if the existing rock is colliding with ship
			// and checking the gameOver status
			if (rocks[rockIndex].GetShipColission())
			{
				gameOver = true;
			}

			// Spawning a new rock and incrementing the speederRoundCounter
			if (rocks[rockIndex].GetIonRockCollision())
			{
				++rockIndex;
				rocks[rockIndex].Init(gfx.ScreenWidth, yDist(rng));
				++speederRoundCounter;
				rocks[rockIndex].SetIonRockCollision(false);
			}

			// Adjusting the fire rate
			if (fireCounter > fireCounterLimit)
			{

				// Checking if the "Space" is pressed
				// and spawning/charging a new ion
				if (wnd.kbd.KeyIsPressed(VK_SPACE))
				{
					ionIndex++;
					ions[ionIndex].Init(
						ship.GetX() + ship.GetWidth(),
						gfx.ScreenWidth,
						ship.GetY() + ship.GetHeight() / 2 - 1,
						ship.GetY() + ship.GetHeight() / 2 + 1,
						ionColor, ionVelocity);
					fireCounter = 0;
					ions[ionIndex].SetIsCharged(true);
				}
			}

			// Checking if a ion is spawned/charged
			// and firing it
			for (int t = 0; t <= ionIndex; ++t)
			{
				if (ions[t].GetIsCharged())
				{
					ions[t].Fire(gfx);
				}
			}
		}

		// Drawing the game over title
		else
		{
			gfx.DrawGameOver(gfx.ScreenWidth / 2 - 25, gfx.ScreenHeight / 2 - 25);
		}
	}

	// Drawing the start game title
	else
	{
		gfx.DrawStartGame(gfx.ScreenWidth / 2 - 25, gfx.ScreenHeight / 2 - 25);
	}

	// Checking if the existing rock colliding with the existing ion
	for (int t = 0; t <= ionIndex; ++t)
	{
		if (
			rocks[rockIndex].GetX() < ions[t].GetStartX() + 15 &&
			rocks[rockIndex].GetX() + rocks[rockIndex].GetWidth() > ions[t].GetStartX() &&
			rocks[rockIndex].GetY() + rocks[rockIndex].GetHeight() > ions[t].GetStartY() &&
			rocks[rockIndex].GetY() < ions[t].GetEndY()
			)
		{
			rocks[rockIndex].SetIonRockCollision(true);
		}
	}

	
}

void Game::ComposeFrame()
{
	// Drawing all existing objects
	if (gameStarted)
	{
		if (!speeders[speederIndex].GetShipColission() && speederIndex > -1)
		{
			speeders[speederIndex].Draw(gfx);
		}
		rocks[rockIndex].Draw(gfx);
		gfx.DrawShip(ship.GetX(), ship.GetY());
	}
}
