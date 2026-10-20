#include <Arduino.h>
#include "config.h"
#include "Led.h"

Led::Led(u8_t pin) : _pin(pin) {}

void Led::init(){
      pinMode(_pin, OUTPUT);
}

void Led::set(bool on)
{
    _state = on;
    digitalWrite(_pin, _state);
}   

void Led::blink(u32_t periodMs)
{
    if (millis() - _lastTimeChange > periodMs)
    {
        _lastTimeChange = millis();
        set(!_state);
    }
}

bool Led::isOn() const
{
    return _state;
}