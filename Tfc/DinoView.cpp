#include "DinoView.h"

DinoView::DinoView(Dino *dino, LiquidCrystal *lcd)
{
    this->dino = dino;
    this->lcd = lcd;
}
void DinoView::resetBitmaps()
{
    setLowerBitmap(emptyBitmap);
    setUpperBitmap(emptyBitmap);
}

void DinoView::updateBitmaps()
{
    int i;
    resetBitmaps();
    if (dino->state == DUCKED)
    {
        setLowerBitmap(downBitmap);
    }
    else
    {

        for (i = 0; i < 16; i++)
        {
            if (i >= dino->y && i < dino->y + dino->h)
            {
                if (i < 8)
                {
                    lowerBitmap[7 - i] = dinoBitmap[5 - (i - dino->y)];
                }
                else
                {
                    upperBitmap[15 - i] = dinoBitmap[5 - (i - dino->y)];
                }
            }
        }
    }
    lcd->createChar(DINO_UPPER_CHAR, upperBitmap);
    lcd->createChar(DINO_LOWER_CHAR, lowerBitmap);

    position = dino->x / 5;
}

void DinoView::setLowerBitmap(byte bitmap[])
{
    for (int i = 0; i < 8; i++)
    {
        lowerBitmap[i] = bitmap[i];
    }
}

void DinoView::setUpperBitmap(byte bitmap[])
{
    for (int i = 0; i < 8; i++)
    {
        upperBitmap[i] = bitmap[i];
    }
}

void DinoView::render()
{
    updateBitmaps();
    lcd->setCursor(position, 0);
    lcd->write(byte(DINO_UPPER_CHAR));
    lcd->setCursor(position, 1);
    lcd->write(byte(DINO_LOWER_CHAR));
}