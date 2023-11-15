#include "Dino.h"

Dino::Dino()
{
    w = 5;
    h = 6;
    x = y = 0;
    vx = vy = 0;
    ax = ay = 0;
    state = GROUND;
}

void Dino::updateState()
{
    if (state == JUMPING && y == 0)
    {
        state = GROUND;
    }
    else if (state == DUCKED)
    {
        h = 6;
        state = GROUND;
    }
}

void Dino::duck()
{
    if (state == GROUND)
    {
        h = 4;
        state = DUCKED;
    }
}

void Dino::jump()
{
    if (state == GROUND)
    {
        vy = 5;
        ay = -2;
        state = JUMPING;
        // logic
    }
}

bool Dino::checkColision(GameObject *obstacle)
{
    if (x + w > obstacle->x && x < obstacle->x + obstacle->w &&
        y + h > obstacle->y && y < obstacle->y + obstacle->h)
    {
        state = DEAD;
        return true; // Collision detected.
    }
    return false; // No collision.
}
