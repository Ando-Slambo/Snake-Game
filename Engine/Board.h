#pragma once
#include "Graphics.h"

struct Board
{
	void DrawCell(Graphics& gfx, int x, int y);
	void DrawFood(Graphics& gfx, int x, int y);
	static constexpr int dimensions = 10;
	static constexpr int cells_x = Graphics::ScreenWidth / dimensions - 1;
	static constexpr int cells_y = Graphics::ScreenHeight / dimensions - 1;
};