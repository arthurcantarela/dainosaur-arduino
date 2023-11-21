#include "../Tfc/Game.h"
#if !FEATURE_ARDUINO
#include <iostream>
#include <chrono>
#include <thread>
#endif

int main()
{
    Game game;

    // Main loop
    while (true)
    {
        game.run();
    }

    return 0;
}
