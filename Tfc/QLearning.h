#ifndef QLEARNING_H
#define QLEARNING_H

#define NUM_STATES 16
#define NUM_ACTIONS 3

#include "FeatureFlags.h"

#if FEATURE_ARDUINO
#include <Arduino.h>
#else
#include <cstdlib>
#include <iostream>
#endif

enum QLState
{
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

private:
    float q_table[NUM_STATES][NUM_ACTIONS];
    float learning_rate;
    float discount_factor;

    int getMaxIndex(QLState state);
};

#endif // QLEARNING_H
