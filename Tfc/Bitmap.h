#ifndef BITMAP_H
#define BITMAP_H

#include <Arduino.h>

class Bitmap
{
public:
    static byte emptyBitmap[8];
    Bitmap();
    static void copy(byte dest[8], byte src[8]);
    static void shiftLeft(byte dest[8], byte src[8], int n);
    static void shiftRight(byte dest[8], byte src[8], int n);
};

#endif // BITMAP_H
