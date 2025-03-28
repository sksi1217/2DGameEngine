#include "src/core/Game.h"

#include <iostream>

int main()
{
    try
    {
        Game game(800, 600); // Создаем игру с размером окна 800x600
        game.Start();        // Запускаем игровой цикл
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
