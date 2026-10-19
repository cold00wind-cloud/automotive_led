#pragma once
#include <Arduino.h>

class Button
{
private:
    u8_t _pin;
    u8_t _lastState = LOW;
    u32_t _lastTimeChagne = 0;
    bool _state = false;

public:
    Button(u8_t pin);
    void init();
    void poll();
    bool wasPressed();
};
