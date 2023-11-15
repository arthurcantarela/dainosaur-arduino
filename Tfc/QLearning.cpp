// QLearning.cpp

#include "QLearning.h"
#include <Arduino.h>

QLearning::QLearning()
{
    epsilon = 0.2; // Default value, can be adjusted
    learning_rate = 0.1;
    discount_factor = 0.9;

    // Initialize Q-table with zeros
    for (int i = 0; i < NUM_STATES; i++)
    {
        for (int j = 0; j < NUM_ACTIONS; j++)
        {
            q_table[i][j] = 0.0;
        }
    }
}

void QLearning::updateQTable(QLState state, QLAction action, int reward, QLState newState)
{
    float max_future_q = q_table[newState][getMaxIndex(newState)];
    q_table[state][action] = q_table[state][action] +
                             learning_rate * (reward + discount_factor * max_future_q - q_table[state][action]);
}

QLAction QLearning::chooseAction(QLState state)
{
    if (random(0, 100) < epsilon * 100)
    {
        return (QLAction)random(0, NUM_ACTIONS);
    }
    else
    {
        return (QLAction)getMaxIndex(state);
    }
}

void QLearning::setEpsilon(float newEpsilon)
{
    epsilon = newEpsilon;
}

int QLearning::getMaxIndex(QLState state)
{
    int maxIndex = 0;
    for (int i = 1; i < NUM_ACTIONS; i++)
    {
        if (q_table[state][i] > q_table[state][maxIndex])
        {
            maxIndex = i;
        }
    }
    return maxIndex;
}
