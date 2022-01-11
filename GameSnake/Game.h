#pragma once
#include "Snake.h"
#include <iostream>
#include <windows.h>
#include <random>
#include <ctime>
#include <thread>
#include <chrono>
#include <stdio.h>
#include <conio.h>

enum Elements
{
	HEAD = 'O',
	TAIL = 'o',
	FOOD = '*',
	CORNER = '+',
	HORIZONTAL_BOUND = '-',
	VERTICAL_BOUND = '|'
};

class Game
{
private:
	int height;
	int width;
	Snake* snake;
	Cell* food;
	std::vector<std::vector<char>> map;

	void set_color(int color = 7);
	void hide_cursor();
	void set_cursor(int x, int y);
	void draw_cell(int x, int y, char c);
	void input();

public:
	bool game_over();
	Cell* get_food();
	void set_food();
	void draw_field();
	void tact();
	Game(Snake* _snake, int _height, int _width);
	~Game();
};