#pragma once
#include "Keyboard.h"
#include "Board.h"

class Snake
{
public:
	void Initialize();
	void MoveHead(Keyboard& kbd);
	bool BodyCollision();
	bool FoodCollision(int food_x, int food_y);
	bool Grow();
	void Draw(Board& brd, Graphics& gfx);

	static constexpr int max_segments = 200;

private:
	void MoveBody(int last_x, int last_y);
	int x = 4;
	int y = 0;
	int direction = 2;
	bool initialized = false;

	//no following data include the head
	int segments = 2;
	//arrays that will hold the co-ords of each segment
	int xs[max_segments];
	int ys[max_segments];

	struct Segments
	{
		int x;
		int y;
	};

	Segments segs[max_segments];
};