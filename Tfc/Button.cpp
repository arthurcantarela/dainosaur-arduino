#include "Button.h"

Button::Button(int pin) : buttonPin(pin), currentState(NONE)
{
    pinMode(buttonPin, INPUT);
}

void Button::update()
{
    int buttonVal = analogRead(buttonPin);
    ButtonState tempButton = readButton(buttonVal);
    if (tempButton != NONE)
    {
        currentState = tempButton;
    }
}

void Button::reset()
{
    currentState = NONE;
}

ButtonState Button::getState()
{
    return currentState;
}

ButtonState Button::readButton(int buttonVal)
{
    if ((buttonVal > 600) && (buttonVal < 800))
        return SELECT;
    if ((buttonVal < 400) && (buttonVal >= 200))
        return DOWN;
    if ((buttonVal < 200) && (buttonVal >= 60))
        return UP;
    return NONE;
}
