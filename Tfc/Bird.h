#ifndef BIRD_H
#define BIRD_H

#include "GameObject.h"

class Bird : public GameObject
{
public:
    bool canMove;

    Bird();
    void updateState();
};

#endif // BIRD_H
