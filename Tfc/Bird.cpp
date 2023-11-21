#include "Bird.h"

Bird::Bird()
{
  w = 4;
  h = 3;
  x = 18 * 5;
  y = 4;
  vx = -3;
  vy = 0;
  ax = ay = 0;
}

void Bird::updateState()
{
  if (x <= -150)
    x = 18 * 5;
}