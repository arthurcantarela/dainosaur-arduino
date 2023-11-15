// QLearning.h

#ifndef QLEARNING_H
#define QLEARNING_H

#define NUM_STATES 4
#define NUM_ACTIONS 3

enum QLState
{
    BIRD_CLOSE,
    CACTUS_CLOSE,
    BOTH_CLOSE,
    NONE_CLOSE
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
