#include "FeatureFlags.h"
#include "Game.h"

Game *game;
void setup()
{
    Serial.begin(9600);
    Serial.println("hii1");
    game = new Game();
}

void loop()
{
    Serial.println("hii");
    game->run();
}