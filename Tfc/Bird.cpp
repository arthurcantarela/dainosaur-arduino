#include "Bird.h"

Bird::Bird() {
    w = 5;
    h = 3;
    x = 15*5;
    y = 5;
    vx = -7;
    vy = 0;
    ax = ay = 0;
}

void Bird::updateState() {
  if(x <= -5) x = 15*5;
}