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
    else if (state == CROUCHED)
    {
        h = 6;
        state = GROUND;
    }
}

void Dino::crouch()
{
    if (state == GROUND)
    {
        h = 4;
        state = CROUCHED;
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
    int hh = h - 2;
    if (x + w > obstacle->x && x < obstacle->x + obstacle->w &&
        y + h > obstacle->y && y < obstacle->y + obstacle->h)
    {
        if (state == CROUCHED)
        {
            Serial.println("1:\t" + x + w > obstacle->x ? "true" : "false");
            Serial.println("2:\t" + x < obstacle->x + obstacle->w ? "true" : "false");
            Serial.println("3:\t" + y + hh > obstacle->y ? "true" : "false");
            Serial.println("4:\t" + y < obstacle->y + obstacle->h ? "true" : "false");
        }
        state = DEAD;
        return true; // Collision detected.
    }
    return false; // No collision.
}
