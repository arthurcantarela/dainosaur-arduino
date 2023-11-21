#include "Cactus.h"

Cactus::Cactus()
{
  w = 5;
  h = 4;
  x = 15 * 5;
  y = 0;
  vx = -2;
  vy = 0;
  ax = ay = 0;
}

void Cactus::updateState()
{
  if (x <= 0)
    x = 15 * 5;
}