#pragma once
#include <Arduino.h>
#include "MovingAverage.h"

class Ldr
{
private:
    u8_t pin;
    u16_t threshold_top;     // вище — стало світло
    u16_t threshold_bottom;  // нижче — стало темно
    u32_t periodMs;
    u32_t lastTimeChange = 0;
    u16_t filtered = 0;
    bool dark = false;
    MovingAverage filter;

public:
    Ldr(u8_t pin, u16_t threshold_top, u16_t threshold_bottom, u32_t periodMs);
    void init();
    void poll();
    bool isDark() const;
    u16_t getValue() const;
};