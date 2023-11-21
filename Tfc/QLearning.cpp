#include "QLearning.h"

QLearning::QLearning()
{
    epsilon = maxEpsilon; // Default value, can be adjusted
    learning_rate = 0.05;
    discount_factor = .85;

    // Initialize Q-table with zeros
    for (int i = 0; i < NUM_STATES; i++)
    {
        for (int j = 0; j < NUM_ACTIONS; j++)
        {
            q_table[i][j] = 0.0;
        }
    }
}

static const char stateDictionary[][35] = {
    "DINO_JUMPING\t\t\t",
    "BIRD_VERY_FAR_CACTUS_VERY_FAR\t",
    "BIRD_VERY_FAR_CACTUS_FAR\t",
    "BIRD_VERY_FAR_CACTUS_CLOSE\t",
    "BIRD_VERY_FAR_CACTUS_VERY_CLOSE\t",
    "BIRD_FAR_CACTUS_VERY_FAR\t",
    "BIRD_FAR_CACTUS_FAR\t\t",
    "BIRD_FAR_CACTUS_CLOSE\t\t",
    "BIRD_FAR_CACTUS_VERY_CLOSE\t",
    "BIRD_CLOSE_CACTUS_VERY_FAR\t",
    "BIRD_CLOSE_CACTUS_FAR\t\t",
    "BIRD_CLOSE_CACTUS_CLOSE\t\t",
    "BIRD_CLOSE_CACTUS_VERY_CLOSE\t",
    "BIRD_VERY_CLOSE_CACTUS_VERY_FAR\t",
    "BIRD_VERY_CLOSE_CACTUS_FAR\t",
    "BIRD_VERY_CLOSE_CACTUS_CLOSE\t",
    "BIRD_VERY_CLOSE_CACTUS_VERY_CLOSE"};
static const char actionDictionary[][8] = {
    "NOTHING",
    "JUMP",
    "DUCK"};

void QLearning::printQTable()
{
#if !FEATURE_ARDUINO
    std::cout << std::endl;
    std::cout << "QTable" << std::endl;
    std::cout << "\t\t\t\t\t";
    for (int j = 0; j < NUM_ACTIONS; j++)
    {
        std::cout << actionDictionary[j] << "\t";
    }
    std::cout << std::endl;
    for (int i = 0; i < NUM_STATES; i++)
    {
        std::cout << stateDictionary[i] << "\t";
        for (int j = 0; j < NUM_ACTIONS; j++)
        {
            std::cout << q_table[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
#endif
}

void QLearning::updateQTable(QLState state, QLAction action, int reward, QLState newState)
{
    float max_future_q = q_table[newState][getMaxIndex(newState)];
    q_table[state][action] = q_table[state][action] +
                             learning_rate * (reward + discount_factor * max_future_q - q_table[state][action]);
}

QLAction QLearning::chooseAction(QLState state)
{
#if FEATURE_ARDUINO
    if (random(0, 100) < epsilon * 100)
    {
        return (QLAction)(random(0, NUM_ACTIONS));
    }
#else
    if (rand() % 100 < epsilon * 100)
    {
        return (QLAction)(rand() % NUM_ACTIONS);
    }
#endif
    else
    {
        return (QLAction)getMaxIndex(state);
    }
}

void QLearning::setEpsilon(float newEpsilon)
{
    if (newEpsilon > 1)
        epsilon = 1;
    else if (newEpsilon < 0)
        epsilon = 0;
    else
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
