#ifndef QLEARNING_H
#define QLEARNING_H

#define NUM_STATES 17
#define NUM_ACTIONS 3

#include "FeatureFlags.h"

#if FEATURE_ARDUINO
#include <Arduino.h>
#else
#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"

#include <cstdlib>
#include <iostream>
#endif

enum QLState
{
    DINO_JUMPING,
    BIRD_VERY_FAR_CACTUS_VERY_FAR,
    BIRD_VERY_FAR_CACTUS_FAR,
    BIRD_VERY_FAR_CACTUS_CLOSE,
    BIRD_VERY_FAR_CACTUS_VERY_CLOSE,
    BIRD_FAR_CACTUS_VERY_FAR,
    BIRD_FAR_CACTUS_FAR,
    BIRD_FAR_CACTUS_CLOSE,
    BIRD_FAR_CACTUS_VERY_CLOSE,
    BIRD_CLOSE_CACTUS_VERY_FAR,
    BIRD_CLOSE_CACTUS_FAR,
    BIRD_CLOSE_CACTUS_CLOSE,
    BIRD_CLOSE_CACTUS_VERY_CLOSE,
    BIRD_VERY_CLOSE_CACTUS_VERY_FAR,
    BIRD_VERY_CLOSE_CACTUS_FAR,
    BIRD_VERY_CLOSE_CACTUS_CLOSE,
    BIRD_VERY_CLOSE_CACTUS_VERY_CLOSE
};

enum QLAction
{
    NOTHING,
    JUMP,
    DUCK
};

class QLearning
{
public:
    QLearning();
    void updateQTable(QLState state, QLAction action, int reward, QLState newState);
    QLAction chooseAction(QLState state);
    void printQTable();
    void setEpsilon(float epsilon);
    float epsilon;
    const float maxEpsilon = .1;

private:
    float q_table[NUM_STATES][NUM_ACTIONS];
    float learning_rate;
    float discount_factor;

    int getMaxIndex(QLState state);
};

#endif // QLEARNING_H
