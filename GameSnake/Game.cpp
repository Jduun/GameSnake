#include "Game.h"

void Game::set_color(int color)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, color);
}

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
	hide_cursor();
	set_cursor(width + 10, 0);
	set_color();
	std::cout << "Score: " << snake->get_length();
	set_color();

	std::vector<std::vector<char>> new_map(height + 3, std::vector<char>(width + 3, ' '));
    new_map[0][0] = CORNER;
	for (int i = 0; i <= width; i++)
	{
		new_map[0][i + 1] = HORIZONTAL_BOUND;
	}
	new_map[0][width + 2] = CORNER;
	for (int i = 0; i <= height; i++)
	{
		set_color(10);
		new_map[i + 1][0] = VERTICAL_BOUND;
		new_map[i + 1][width + 2] = VERTICAL_BOUND;
		set_color();
	}
	new_map[height + 2][0] = CORNER;
	for (int i = 0; i <= width; i++)
	{
		new_map[height + 2][i + 1] = HORIZONTAL_BOUND;
	}
	new_map[height + 2][width + 2] = CORNER;
	for (auto cell : *snake->get_body())
	{
		if (cell.x == snake->get_head()->x && cell.y == snake->get_head()->y)
		{
			new_map[cell.y + 1][cell.x + 1] = HEAD;
		}
		else
		{
			new_map[cell.y + 1][cell.x + 1] = TAIL;
		}
	}
	new_map[food->y + 1][food->x + 1] = FOOD;

	for (int i = 0; i < height + 3; i++)
	{
		for (int j = 0; j < width + 3; j++)
		{
			if (map[i][j] != new_map[i][j])
			{
				int color;
				switch (new_map[i][j])
				{
				case VERTICAL_BOUND:
					color = 9;
					break;
				case CORNER:
					color = 9;
					break;
				case HORIZONTAL_BOUND:
					color = 9;
					break;
				case HEAD:
					color = 15;
					break;
				case TAIL:
					color = 4;
					break;
				case FOOD:
					color = 10;
					break;
				default:
					color = 7;
					break;
				}
				set_cursor(j, i);
				set_color(color);
				std::cout << new_map[i][j];
				set_color();
			}
		}
	}
	map = new_map;
}

void Game::input()
{
	if (_kbhit())
	{
		if (_getch() == 224)
		{
			switch (_getch())
			{
			case 72: snake->set_direction(UP); break;
			case 75: snake->set_direction(LEFT); break;
			case 77: snake->set_direction(RIGHT); break;
			case 80: snake->set_direction(DOWN); break;
			default: break;
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
		return true;
		
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
	int speed = 40;
	if (snake->get_direction() == RIGHT || snake->get_direction() == LEFT)
		std::this_thread::sleep_for(std::chrono::milliseconds(speed));
	else std::this_thread::sleep_for(std::chrono::milliseconds((int)(2.4 * speed)));
}

Game::Game(Snake* _snake, int _height, int _width)
{
	snake = _snake;
	height = _height;
	width = _width;
	for (int i = 0; i < height + 3; i++)
	{
		std::vector<char> str(width + 3, ' ');
		map.push_back(str);
	}
	set_food();
}

Game::~Game()
{
	delete food;
}