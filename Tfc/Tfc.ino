#include <Arduino.h>
#include "Game.h"

Game *game;
void setup()
{
    game = new Game();
    Serial.begin(9600);
}

void loop()
{
    game->run();
}