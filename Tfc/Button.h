#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

enum ButtonState
{
    NONE,
    UP,
    DOWN
};

class Button
{
public:
    Button(int pin);
    void update();
    void reset();
    ButtonState getState();

private:
    int buttonPin;
    ButtonState currentState;
    ButtonState readButton(int buttonVal);
};

#endif // BUTTON_H
