#include "Bird.h"

Bird::Bird()
{
  w = 4;
  h = 3;
  x = 16 * 5;
  y = 4;
  vx = -6;
  vy = 0;
  ax = ay = 0;
  canMove = true;
}

void Bird::updateState()
{
  if (x < 0)
  {
    x = 16 * 5;
    canMove = false;
  }
}