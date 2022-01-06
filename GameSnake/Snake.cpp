#include "Snake.h"

void Snake::set_direction(int _direction)
{
	if (get_length() > 1)
	{
		if ((_direction == RIGHT && direction != LEFT) ||
			(_direction == LEFT && direction != RIGHT) ||
			(_direction == UP && direction != DOWN)    ||
			(_direction == DOWN && direction != UP))
			direction = _direction;
	}
	else if (_direction == RIGHT || _direction == LEFT || _direction == DOWN || _direction == UP)
	{
		direction = _direction;
	}
}

void Snake::move()
{
	for (int i = get_length() - 1; i > 0; i--)
	{
		body[i] = body[i - 1];
	}
	switch (direction)
	{
	case RIGHT:
		body[0].x++;
		break;
	case LEFT:
		body[0].x--;
		break;
	case UP:
		body[0].y--;
		break;
	case DOWN:
		body[0].y++;
		break;
	}
}

int Snake::get_length()
{
	return body.size();
}

void Snake::grow()
{
	Cell cell(body[get_length() - 1].x, body[get_length() - 1].y);
	body.push_back(cell);
	for (int i = get_length() - 1; i > 0; i--)
	{
		body[i] = body[i - 1];
	}
	switch (direction)
	{
	case RIGHT: body[0].x++; break;
	case LEFT: body[0].x--; break;
	case UP: body[0].y--; break;
	case DOWN: body[0].y++; break;
	}
}

std::vector<Cell>* Snake::get_body()
{
	return &body;
}

int Snake::get_direction()
{
	return direction;
}

Cell* Snake::get_head()
{
	return &body[0];
}

Snake::Snake(int x_head, int y_head)
{
	set_direction();
	Cell cell(x_head, y_head);
	body.push_back(cell);
}