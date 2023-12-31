#ifndef DINO_H
#define DINO_H

#include "GameObject.h"
#include "FeatureFlags.h"

#if !FEATURE_ARDUINO
#include <iostream>
#endif

enum DinoState
{
    GROUND,
    JUMPING,
    DUCKED,
    DEAD
};

class Dino : public GameObject
{
public:
    DinoState state;

    Dino();
    void updateState();
    void duck();
    void stand();
    void jump();
    bool checkColision(GameObject *obstacle);
};

#endif // DINO_H
