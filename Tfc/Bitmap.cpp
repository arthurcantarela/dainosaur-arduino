#include "Bitmap.h"

byte Bitmap::emptyBitmap[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

void Bitmap::copy(byte dest[8], byte src[8])
{
    for (int i = 0; i < 8; i++)
    {
        dest[i] = src[i];
    }
}
void Bitmap::shiftLeft(byte dest[8], byte src[8], int n)
{
    for (int i = 0; i < 8; i++)
    {
        dest[i] = src[i] << n;
    }
}
void Bitmap::shiftRight(byte dest[8], byte src[8], int n)
{
    for (int i = 0; i < 8; i++)
    {
        dest[i] = src[i] >> n;
    }
}