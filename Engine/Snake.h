#pragma once
#include "Keyboard.h"
#include "Board.h"

class Snake
{
public:
	void Initialize();
	bool MoveHead(Keyboard& kbd);
	bool BodyCollision();
	bool FoodCollision(int food_x, int food_y);
	bool Grow(int r, int g, int b);
	void Draw(Board& brd, Graphics& gfx);

	static constexpr int max_segments = 200;

private:
	void MoveBody(int segment);
	int x = 1;
	int y = 1;
	int direction = 2;
	bool initialized = false;

	//no following data include the head
	int segments = 0;
	//arrays that will hold the co-ords of each segment
	int xs[max_segments];
	int ys[max_segments];

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