#include "Board.h"

void Board::DrawCell(Graphics& gfx, int x, int y, int r, int g, int b)
{
	int left = x * dimensions;
	int right = left + dimensions;
	int top = y * dimensions;
	int bottom = top + dimensions;

	int x_iterations = 0;
	int y_iterations = 0;
	const int spacing = 2;

	for (int i = left; i < right; i++) {
		for (int j = top; j < bottom; j++) {
			if (x_iterations < spacing || 
				x_iterations > dimensions - spacing - 1 ||
				y_iterations < spacing ||
				y_iterations > dimensions - spacing - 1)
			{ 
				gfx.PutPixel(i, j, 0, 0, 0); 
			}
			else { gfx.PutPixel(i, j, r, g, b); }
			y_iterations++;
		}
		x_iterations++;
		y_iterations = 0;
	}
}
