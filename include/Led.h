#pragma once
#include <Arduino.h>

class Led
{
private:
    u8_t _pin;
    u32_t _lastTimeChange = 0;
    bool _state = false;


public:
    Led(u8_t pin);
    void init();
    void set(bool on);
    void blink(u32_t periodMs);
    bool isOn() const;
};