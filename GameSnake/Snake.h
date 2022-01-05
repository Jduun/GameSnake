#pragma once
#include <vector>

struct Cell
{
	int x;
	int y;

	Cell(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
};

enum Direction
{
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Snake
{
private:
	int direction;
	std::vector<Cell> body;

public:
	int get_length();
	void move();
	void grow();
	void set_direction(int _direction = RIGHT);
	int get_direction();
	Cell* get_head();
	std::vector<Cell>* get_body();
	Snake(int x_head, int y_head);
};