#ifndef BIRD_H
#define BIRD_H

#include "GameObject.h"

class Bird : public GameObject {
public:
    Bird();
    void updateState();
};

#endif // BIRD_H
