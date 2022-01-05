#include <iostream>
#include "Snake.h"
#include "Game.h"

int main()
{
    int height = 30;
    int width = 20;
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
