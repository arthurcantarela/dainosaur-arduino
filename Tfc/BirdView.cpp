#include "BirdView.h"

BirdView::BirdView(Bird *bird, LiquidCrystal *lcd)
{
    this->bird = bird;
    this->lcd = lcd;
}

void BirdView::updateBitmaps()
{
    int shiftAmout = bird->x % 5;

    Bitmap::shiftRight(leftBitmap, birdBitmap, shiftAmout);
    lcd->createChar(BIRD_CHAR, leftBitmap);

    Bitmap::shiftLeft(rightBitmap, birdBitmap, 5 - shiftAmout);
    lcd->createChar(BIRD_RIGHT_CHAR, rightBitmap);
    position = bird->x / 5;
}

void BirdView::render()
{
    updateBitmaps();
    lcd->setCursor(position, 1);
    lcd->write(byte(BIRD_CHAR));
    lcd->setCursor(1 + (position), 1);
    lcd->write(byte(BIRD_RIGHT_CHAR));
}