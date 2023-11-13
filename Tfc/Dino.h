#ifndef DINO_H
#define DINO_H

#include "Arduino.h"
#include "GameObject.h"

enum DinoState
{
    GROUND,
    JUMPING,
    CROUCHED,
    DEAD
};

class Dino : public GameObject
{
public:
    DinoState state;

    Dino();
    void updateState();
    void crouch();
    void stand();
    void jump();
    bool checkColision(GameObject *obstacle);
};

#endif // DINO_H
