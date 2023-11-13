#ifndef CACTUSVIEW_H
#define CACTUSVIEW_H

#include <Arduino.h>
#include "LiquidCrystal.h"
#include "Cactus.h"
#include "LcdChars.h"
#include "Bitmap.h"

class CactusView
{
public:
    Cactus *cactus;
    LiquidCrystal *lcd;

    byte leftBitmap[8];
    byte rightBitmap[8];

    uint8_t position;

    CactusView(Cactus *cactus, LiquidCrystal *lcd);
    void updateBitmaps();
    void render();

private:
    byte cactusBitmap[8] = {
        0b00000,
        0b00000,
        0b00101,
        0b10101,
        0b10110,
        0b10100,
        0b01100,
        0b00100};
};

#endif // CACTUSVIEW_H
