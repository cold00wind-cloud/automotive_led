#include "Ldr.h"

Ldr::Ldr(u8_t pin, u16_t threshold_top, u16_t threshold_bottom, u32_t periodMs)
    : pin(pin), threshold_top(threshold_top),
      threshold_bottom(threshold_bottom), periodMs(periodMs) {}

void Ldr::init()
{
    pinMode(pin, INPUT);
    filtered = analogRead(pin);
    filter.init(filtered);
    dark = filtered < threshold_bottom;  
}

void Ldr::poll()
{
    if (millis() - lastTimeChange > periodMs)
    {
        lastTimeChange = millis();

        u16_t raw = analogRead(pin);
        filtered = filter.add(raw);

        if (filtered < threshold_bottom)
        {
            dark = true;
        }
        else if (filtered > threshold_top)
        {
            dark = false;
        }   
    }
}

bool Ldr::isDark() const
{
    return dark;
}

u16_t Ldr::getValue() const
{
    return filtered;
}