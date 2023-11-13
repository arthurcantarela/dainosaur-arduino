#include "CactusView.h"

CactusView::CactusView(Cactus *cactus, LiquidCrystal *lcd)
{
    this->cactus = cactus;
    this->lcd = lcd;
}

void CactusView::updateBitmaps()
{
    int shiftAmout = cactus->x % 5;

    Bitmap::shiftRight(leftBitmap, cactusBitmap, shiftAmout);
    lcd->createChar(CACTUS_CHAR, leftBitmap);

    Bitmap::shiftLeft(rightBitmap, cactusBitmap, 5 - shiftAmout);
    lcd->createChar(CACTUS_RIGHT_CHAR, rightBitmap);
    position = cactus->x / 5;
}

void CactusView::render()
{
    updateBitmaps();
    lcd->setCursor(position, 1);
    lcd->write(byte(CACTUS_CHAR));
    lcd->setCursor(1 + (position), 1);
    lcd->write(byte(CACTUS_RIGHT_CHAR));
}