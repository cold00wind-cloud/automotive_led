#pragma once
#include <Arduino.h>

#define LDR 2
#define LED_W 17
#define LED_Y 16
#define BTN_CRASHE 20 // blue
#define BTN_BLINK 21  // red

#define N 32

constexpr u16_t LDR_THRESHOLD_ON = 1000;
constexpr u16_t LDR_THRESHOLD_OFF = 1100;
constexpr u32_t ADC_PERIOD = 10;
constexpr u32_t DEBOUNCE_MC = 100;

enum class Mode
{
  NORMAL,
  BLINK,
  CRASHED
};