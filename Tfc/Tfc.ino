#include "FeatureFlags.h"
#include "Game.h"

Game *game;
void setup()
{
    Serial.begin(9600);
    Serial.println();
    Serial.println("setup");
    game = new Game();
}

void loop()
{
    game->run();
}