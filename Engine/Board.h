#pragma once
#include "Graphics.h"

struct Board
{
	void DrawCell(Graphics& gfx, int x, int y, int r, int g, int b);
	static constexpr int dimensions = 20;
	static constexpr int cells_x = Graphics::ScreenWidth / dimensions - 1;
	static constexpr int cells_y = Graphics::ScreenHeight / dimensions - 1;
};