#include "Board.h"

void Board::DrawCell(Graphics& gfx, int x, int y)
{
	int left = x * dimensions;
	int right = left + dimensions;
	int top = y * dimensions;
	int bottom = top + dimensions;

	for (int i = left; i < right; i++) {
		for (int j = top; j < bottom; j++) {
			gfx.PutPixel(i, j, 255, 255, 255);
		}
	}
}

void Board::DrawFood(Graphics& gfx, int x, int y)
{
	int left = x * dimensions;
	int right = left + dimensions;
	int top = y * dimensions;
	int bottom = top + dimensions;

	for (int i = left; i < right; i++) {
		for (int j = top; j < bottom; j++) {
			gfx.PutPixel(i, j, 255, 0, 0);
		}
	}
}
