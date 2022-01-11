#include <iostream>
#include "Snake.h"
#include "Game.h"

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int height = 20;
    int width = 60;
    Snake* snake = new Snake(width / 2, height / 2);
    Game* game = new Game(snake, height, width);
    bool exit = false;
    while (!exit)
    {
        game->tact();
        if (game->game_over())
        {
            std::cout << "GAME OVER\n";
            exit = true;
        }
    }
    delete game;
    delete snake;
    return 0;
}
