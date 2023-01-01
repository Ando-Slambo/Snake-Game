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
	RespawnFood(rd);
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
		game_over = snake.MoveHead(wnd.kbd) || snake.BodyCollision();

		if (snake.FoodCollision(food_x, food_y)) {

			if (snake.Grow(food_r, food_g, food_b)) {
				RespawnFood(rd);
			}
			else { game_win = true; }
		}
	}
}

void Game::ComposeFrame()
{
	//draws red bars on top and bottom
	for (int x = 0; x < Graphics::ScreenWidth; x++) {
		//top bar
		for (int y = 0; y < Board::dimensions; y++) {
			gfx.PutPixel(x, y, 255, 0, 0);
		}
		//bottom bar
		for (int y = Graphics::ScreenHeight - Board::dimensions; y < Graphics::ScreenHeight; y++) {
			gfx.PutPixel(x, y, 255, 0, 0);
		}
	}
	//draws red bars on left and right
	for (int y = Board::dimensions; y < Graphics::ScreenHeight - Board::dimensions; y++) {
		//left bar
		for (int x = 0; x < Board::dimensions; x++) {
			gfx.PutPixel(x, y, 255, 0, 0);
		}
		//right bar
		for (int x = Graphics::ScreenWidth - Board::dimensions; x < Graphics::ScreenWidth; x++) {
			gfx.PutPixel(x, y, 255, 0, 0);
		}
	}


	snake.Draw(brd, gfx);
	if (!game_win) { brd.DrawCell(gfx, food_x, food_y, food_r, food_g, food_b); }
	if (game_over) { sprite.DrawGameOver(100, 100, gfx); }

	if (game_over || game_win) {
		if (wnd.kbd.KeyIsPressed(VK_RETURN)) {
			snake.Initialize();
			RespawnFood(rd);
			game_over = false;
			game_win = false;
		}
	}
}

void Game::RespawnFood(std::random_device& rd)
{
	std::uniform_int_distribution<int> x_cells(1, Board::cells_x - 1);
	std::uniform_int_distribution<int> y_cells(1, Board::cells_y - 1);
	std::uniform_int_distribution<int> rgb(10, 255);

	food_x = x_cells(rd);
	food_y = y_cells(rd);
	food_r = rgb(rd);
	food_g = rgb(rd);
	food_b = rgb(rd);
}
