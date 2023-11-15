#include <iostream>
#include <chrono>
#include <thread>
#include "Game.h"

int main()
{
    setup();

    Game game;

    // Main loop
    while (true)
    {
        game.run();
    }

    return 0;
}
