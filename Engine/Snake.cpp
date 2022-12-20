#include "Snake.h"

void Snake::Initialize()
{
	if (initialized) { return;  }

	for (int i = 0; i < max_segments; i++) {
		segs[i].x = x - (i + 1);
		segs[i].y = y;
	}

	initialized = true;
}

void Snake::MoveHead(Keyboard& kbd)
{
	//left
	if (kbd.KeyIsPressed(0x25) && !(direction == 2)) {
		direction = 0;
	}
	//up
	if (kbd.KeyIsPressed(0x26) && !(direction == 3)) {
		direction = 1;
	}
	//right
	if (kbd.KeyIsPressed(0x27) && !(direction == 0)) {
		direction = 2;
	}
	//down
	if (kbd.KeyIsPressed(0x28) && !(direction == 1)) {
		direction = 3;
	}

	MoveBody(x, y);

	if (direction == 0) {
		//turn snake up if hit wall
		if (x - 1 == 0) { direction = 1; }
		x -= 1;
	}
	if (direction == 1) {
		//turn snake right if hit wall
		if (y - 1 == 0) { direction = 2; }
		y -= 1;
	}
	if (direction == 2) {
		//turn snake down if hit wall
		if (x + 1 == Board::cells_x) { direction = 3; }
		x += 1;
	}
	if (direction == 3) {
		y += 1;
		//turn snake left if hit wall
		if (y == Board::cells_y) {
			y = Board::cells_y;
			x -= 1;
			direction = 0;
		}
	}
}

void Snake::Draw(Board& brd, Graphics& gfx)
{
	//draws the head
	brd.DrawCell(gfx, x, y);

	//draws the body
	for (int i = 0; i < segments; i++) {
		brd.DrawCell(gfx, segs[i].x, segs[i].y);
	}
}

void Snake::MoveBody(int head_x, int head_y)
{
	//putting head co-ords into segment's array for the 0th segment to move to
	//(head will move to new co-ords as soon as this function terminates)
	xs[0] = head_x;
	ys[0] = head_y;

	//max_segments-1 because no segment will be moving to the last segment's location
	//i+1 because 0 is occupied by the head and segs[0] cannot be skipped
	for (int i = 0; i < max_segments-1; i++) {
		xs[i+1] = segs[i].x;
		ys[i+1] = segs[i].y;
	}

	//set every segments co-ords to those in the arrays
	for (int i = 0; i < max_segments; i++) {
		segs[i].x = xs[i];
		segs[i].y = ys[i];
	}
}

bool Snake::BodyCollision()
{
	for (int i = 0; i < segments; i++) {
		//check if head's co-ords are in the segment arrays and return true if so
		//(only want to return false after checking every element)
		if (x == segs[i].x && y == segs[i].y) { return true; }
	}
	//else return false
	return false;
}

bool Snake::FoodCollision(int food_x, int food_y)
{
	return (x == food_x && y == food_y);
}

bool Snake::Grow()
{
	bool grew = (segments < max_segments);
	//segments will grow by 1 if grew is true
	segments += grew;

	//return true if we grew else return false to signify player has won
	return grew;
}
