#include <Arduino.h>
#include <LiquidCrystal.h>
#include "Game.h"
#include "Dino.h"
#include "DinoView.h"
#include "Bird.h"
#include "BirdView.h"
#include "Cactus.h"
#include "CactusView.h"
#include "Button.h"
#include "LiquidCrystal.h"

Dino *dino = new Dino();
DinoView *dinoView = new DinoView(dino, &lcd);

Bird *bird = new Bird();
BirdView *birdView = new BirdView(bird, &lcd);

Cactus *cactus = new Cactus();
CactusView *cactusView = new CactusView(cactus, &lcd);

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