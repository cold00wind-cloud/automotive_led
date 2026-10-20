#pragma once
#include <Arduino.h>
#include "config.h"

class MovingAverage
{
private:
    u16_t readings[N];
    u8_t idx = 0;
    u32_t sum = 0;

public:
    void init(u16_t initData);
    u16_t add(u16_t rawData);   // повертає відфільтроване значення
};