#include "Cactus.h"

Cactus::Cactus() {
    w = 5;
    h = 3;
    x = 15*5;
    y = 5;
    vx = -2;
    vy = 0;
    ax = ay = 0;
}

void Cactus::updateState() {
  if(x <= 0) x = 15*5;
}