#ifndef GAME_H
#define GAME_H

#include <Arduino.h>
#include "Dino.h"
#include "Cactus.h"
#include "Bird.h"
#include "DinoView.h"
#include "CactusView.h"
#include "BirdView.h"
#include "Button.h"

#define pinRs 8
#define pinEn 9
#define pinD4 4
#define pinD5 5
#define pinD6 6
#define pinD7 7
#define pinBackLight 10

enum GameState
{
    MENU,
    RUNNING,
    GAME_OVER
};

class Game
{
public:
    Game();

    void run();

private:
    GameState state;
    int score;

    Dino *dino;
    Cactus *cactus;
    Bird *bird;

    DinoView *dinoView;
    CactusView *cactusView;
    BirdView *birdView;

    unsigned long previousMillis;
    const unsigned long interval = 200;

    LiquidCrystal *lcd;
    Button *button;

    void startGame();
    void handleUserInput();
    void update();
    void render();
};

#endif // GAME_H
