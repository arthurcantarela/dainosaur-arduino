#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject
{
public:
    int x, y, h, w, vx, vy, ax, ay;
    void move();
};

#endif // GAMEOBJECT_H