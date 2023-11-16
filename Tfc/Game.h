#ifndef GAME_H
#define GAME_H

#include "Dino.h"
#include "Cactus.h"
#include "Bird.h"
#include "FeatureFlags.h"
#include "QLearning.h"

#if FEATURE_ARDUINO
#include <Arduino.h>
#include "Button.h"
#include "DinoView.h"
#include "CactusView.h"
#include "BirdView.h"
#else
#include <iostream>
#endif

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
    QLState getState();

private:
    GameState state;
    int score;
    int attempts;

    Dino *dino;
    Cactus *cactus;
    Bird *bird;

    QLearning qLearning;

#if FEATURE_ARDUINO
    DinoView *dinoView;
    CactusView *cactusView;
    BirdView *birdView;

    unsigned long previousMillis;
    const unsigned long interval = 50;

    LiquidCrystal *lcd;
    Button *button;
#endif

    void startGame();
    void handleUserInput();
    void handleUserInput(QLAction action);
    void update();

#if FEATURE_ARDUINO
    void render();
#endif
};

#endif // GAME_H
