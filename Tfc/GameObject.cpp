#include "GameObject.h"

void GameObject::move() {
    x = x + vx;
    y = y + vy;
    if (y < 0)
        y = 0;
    vx = vx + ax;
    vy = vy + ay;
}
