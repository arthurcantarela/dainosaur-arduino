#ifndef BIRDVIEW_H
#define BIRDVIEW_H

#include <Arduino.h>
#include "LiquidCrystal.h"
#include "Bird.h"
#include "LcdChars.h"
#include "Bitmap.h"

class BirdView
{
public:
    Bird *bird;
    LiquidCrystal *lcd;

    byte leftBitmap[8];
    byte rightBitmap[8];

    uint8_t position;

    BirdView(Bird *bird, LiquidCrystal *lcd);
    void updateBitmaps();
    void render();

private:
    byte birdBitmap[8] = {
        0b01011,
        0b11100,
        0b00111,
        0b00000,
        0b00000,
        0b00000,
        0b00000,
        0b00000};
};

#endif // BIRDVIEW_H
