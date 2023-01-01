#pragma once
#include "Keyboard.h"
#include "Board.h"

class Snake
{
public:
	void Initialize();
	bool Move(Keyboard& kbd);
	bool BodyCollision();
	bool FoodCollision(int food_x, int food_y);
	bool Grow(int r, int g, int b);
	void Draw(Board& brd, Graphics& gfx);

	static constexpr int max_segments = 63;

private:
	void MoveBody(int segment);
	int x;
	int y;
	int direction;
	int segments;

	struct Segments
	{
		int x;
		int y;
		int r;
		int g;
		int b;
	};

	Segments segs[max_segments];
};