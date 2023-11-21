#ifndef GAME_H
#define GAME_H

#define SHORT_INTERVAL 150
#define LONG_INTERVAL 1000
#define MAX_ATTEMPTS 1000000
#define LOG_EACH_N_ATTEMPTS 1000
#define MAX_SCORE 1000

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
    bool isTraining();
    void setTraining(bool newTraining);

private:
    GameState state;
    int score;
    int maxScore;
    int attempts;
    bool training;

    Dino *dino;
    Cactus *cactus;
    Bird *bird;

    QLearning qLearning;
    unsigned long interval;

#if FEATURE_ARDUINO
    DinoView *dinoView;
    CactusView *cactusView;
    BirdView *birdView;

    unsigned long previousMillis;

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
