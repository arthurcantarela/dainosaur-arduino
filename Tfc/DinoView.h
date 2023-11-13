#ifndef DINOVIEW_H
#define DINOVIEW_H

#include <Arduino.h>
#include "LiquidCrystal.h"
#include "Dino.h"
#include "LcdChars.h"

#define DINO_BASE_ADDR 1

class DinoView
{
public:
    Dino *dino;
    LiquidCrystal *lcd;

    byte upperBitmap[8];
    byte lowerBitmap[8];

    uint8_t position;

    DinoView(Dino *dino, LiquidCrystal *lcd);
    void setUpperBitmap(byte bitmap[]);
    void setLowerBitmap(byte bitmap[]);
    void resetBitmaps();
    void updateBitmaps();
    void render();

private:
    byte emptyBitmap[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    byte dinoBitmap[6] = {0x07, 0x07, 0x06, 0x0F, 0x1E, 0x0A};
    byte downBitmap[8] = {
        0b00000,
        0b00000,
        0b00000,
        0b00000,
        0b00111,
        0b01111,
        0b11110,
        0b01010};
};

#endif // DINOVIEW_H
