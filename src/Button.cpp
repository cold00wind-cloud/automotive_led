#include <Arduino.h>
#include "Button.h"
#include "config.h"

Button::Button(u8_t pin) : _pin(pin) {}

void Button::init()
{
    pinMode(_pin, INPUT_PULLDOWN);
}

void Button::poll()
{
    if (millis() - _lastTimeChagne > DEBOUNCE_MC)
    {
        u8_t buttonState = digitalRead(_pin);
        if (buttonState != _lastState)
        {
            _lastState = buttonState;
            _lastTimeChagne = millis();
            if (buttonState == HIGH)
            {
                _state = true;
            }
        }
    }
}

bool Button::wasPressed(){
    bool state = _state;
    _state = false;
    return state;
}