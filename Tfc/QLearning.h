// QLearning.h

#ifndef QLEARNING_H
#define QLEARNING_H

#define NUM_STATES 7
#define NUM_ACTIONS 3

#include "FeatureFlags.h"

#if FEATURE_ARDUINO
#include <Arduino.h>
#else
#include <cstdlib>
#endif

enum QLState
{
    BIRD_CLOSE,
    BIRD_FAR,
    CACTUS_CLOSE,
    CACTUS_FAR,
    BOTH_CLOSE,
    BOTH_FAR,
    NOTHING_ON_SIGHT
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
    void setEpsilon(float epsilon);

private:
    float q_table[NUM_STATES][NUM_ACTIONS];
    float epsilon;
    float learning_rate;
    float discount_factor;

    int getMaxIndex(QLState state);
};

#endif // QLEARNING_H
