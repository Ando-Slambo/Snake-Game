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
	gfx( wnd )
{
	std::random_device rd;
	std::uniform_int_distribution<int> x_cells(0, Board::cells_x);
	std::uniform_int_distribution<int> y_cells(0, Board::cells_y);

	for (int i = 0; i < Snake::max_segments; i++) {
		food_xs[i] = x_cells(rd);
		food_ys[i] = y_cells(rd);
	}

	SpawnFood();
	snake.Initialize();
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
	frame_counter++;

	if (game_over || game_win) { return; }

	if (frame_counter % 4 == 0) {
		snake.MoveHead(wnd.kbd);
		game_over = snake.BodyCollision();

		if (snake.FoodCollision(food_x, food_y)) {
			food_eaten++;

			if (snake.Grow()) { SpawnFood(); }
			else { game_win = true; }
		}
	}
}

void Game::ComposeFrame()
{
	snake.Draw(brd, gfx);

	if (!game_win) { brd.DrawFood(gfx, food_x, food_y); }

	if (game_over) { sprite.DrawGameOver(100, 100, gfx); }
}

void Game::SpawnFood()
{
	food_x = food_xs[food_eaten];
	food_y = food_ys[food_eaten];
}
