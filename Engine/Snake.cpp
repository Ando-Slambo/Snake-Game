#include "Snake.h"

void Snake::Initialize()
{
	x = 1;
	y = 1;
	segments = 0;
	direction = 2;

	for (int i = 0; i < max_segments; i++) {
		segs[i].x = x - (i + 1);
		segs[i].y = y;
	}
}

bool Snake::MoveHead(Keyboard& kbd)
{
	//all directions are from perspective of user
	
	//left (not allowed if moving right)
	if (kbd.KeyIsPressed(0x25) && !(direction == 2)) { direction = 0; }
	//up (not allowed if moving down)
	if (kbd.KeyIsPressed(0x26) && !(direction == 3)) { direction = 1; }
	//right (not allowed if moving left)
	if (kbd.KeyIsPressed(0x27) && !(direction == 0)) { direction = 2; }
	//down (not allowed if moving up)
	if (kbd.KeyIsPressed(0x28) && !(direction == 1)) { direction = 3; }

	//ONLY EVER PASS MAX_SEGMENTS - 1 INTO MOVEBODY
	MoveBody(max_segments - 1);

	//returns true when head hits wall
	bool return_val = false;
	switch (direction) {
	case 0:
		return_val = x - 1 == 0;
		x -= 1;
		break;
	case 1:
		return_val = y - 1 == 0;
		y -= 1;
		break;
	case 2:
		return_val = x + 1 == Board::cells_x;
		x += 1;
		break;
	case 3:
		return_val = y + 1 == Board::cells_y;
		y += 1;
	}
	return return_val;
}

void Snake::Draw(Board& brd, Graphics& gfx)
{
	//draws the head
	brd.DrawCell(gfx, x, y, 255, 255, 255);

	//draws the body
	for (int i = 0; i < segments; i++) {
		brd.DrawCell(gfx, segs[i].x, segs[i].y, segs[i].r, segs[i].g, segs[i].b);
	}
}

void Snake::MoveBody(int segment)
{
	if (segment == 0) {
		segs[segment].x = x;
		segs[segment].y = y;
		return;
	}

	segs[segment].x = segs[segment - 1].x;
	segs[segment].y = segs[segment - 1].y;

	MoveBody(segment - 1);
}

bool Snake::BodyCollision()
{
	//check if head's co-ords are in the segment arrays and return true if so
	// (only want to return false after checking every element)
	for (int i = 0; i < segments; i++) {
		if (x == segs[i].x && y == segs[i].y) { return true; }
	}
	return false;
}

bool Snake::FoodCollision(int food_x, int food_y)
{
	return (x == food_x && y == food_y);
}

bool Snake::Grow(int r, int g, int b)
{
	bool grew = (segments < max_segments);
	//segments will grow by 1 if grew is true
	segments += grew;

	segs[segments-1].r = r;
	segs[segments-1].g = g;
	segs[segments-1].b = b;

	//return true if we grew else return false to signify player has won
	return grew;
}
