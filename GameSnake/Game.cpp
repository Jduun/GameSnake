#include "Game.h"

void Game::hide_cursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void Game::set_cursor(int x, int y)
{
	HANDLE handle;
	COORD coordinates;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	coordinates.X = x;
	coordinates.Y = y;
	SetConsoleCursorPosition(handle, coordinates);
}

void Game::draw_cell(int x, int y, char c)
{
	hide_cursor();
	set_cursor(x, y);
	std::cout << c;
}

Cell* Game::get_food()
{
	return food;
}

void Game::set_food()
{
	srand(time(0));
	bool empty = false;
	int x, y;
	while (!empty)
	{
		empty = true;
		x = rand() % width;
		y = rand() % height;
		for (auto cell : *snake->get_body())
		{
			if (cell.x == x && cell.y == y)
			{
				empty = false;
				break;
			}
		}
	}
	food = new Cell(x, y);
}

void Game::draw_field()
{
	set_cursor(0, 0);
	std::cout << "(" << snake->get_head()->x << ", " << snake->get_head()->y << ") [" << height << "x" << width << "]";
	system("cls");
	for (auto cell : *snake->get_body())
	{
		draw_cell(cell.x, cell.y, '*');
	}
	draw_cell(food->x, food->y, 'x');
}

void Game::input()
{
	if (_kbhit())
	{
		if (_getch() == 224)
		{
			switch (_getch())
			{
			case 72:
				snake->set_direction(UP);
				break;
			case 75:
				snake->set_direction(LEFT);
				break;
			case 77:
				snake->set_direction(RIGHT);
				break;
			case 80:
				snake->set_direction(DOWN);
				break;
			default:
				break;
			}
		}
	}
}

bool Game::game_over()
{
	if (snake->get_head()->x > width ||
		snake->get_head()->y > height ||
		snake->get_head()->x < 0 ||
		snake->get_head()->y < 0)
		return false;

	int count = 0;
	for (auto cell : *snake->get_body())
	{
		if (cell.x == snake->get_head()->x &&
			cell.y == snake->get_head()->y)
		{
			count++;
			if (count == 2) return true;
		}
	}
	return false;
}

void Game::tact()
{
	snake->move();
	if (snake->get_head()->x == food->x && snake->get_head()->y == food->y)
	{
		snake->grow();
		set_food();
	}
	input();
	draw_field();
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

Game::Game(Snake* _snake, int _height, int _width)
{
	snake = _snake;
	height = _height;
	width = _width;
	set_food();
}

Game::~Game()
{
	delete food;
}