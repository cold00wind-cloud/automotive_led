#include <Arduino.h>
#include "config.h"
#include "Button.h"
#include "Led.h"

Mode mode = Mode::NORMAL;

Button btnCrash(BTN_CRASHE);
Button btnBlink(BTN_BLINK);

Led ledY(LED_Y);
Led ledW(LED_W);

u16_t readings[N];
u8_t idx = 0;
u32_t sum = 0;

u32_t lastTimeChange = 0;

u16_t movingAvg(u16_t rawData)
{
  sum -= readings[idx];
  sum += rawData;
  readings[idx] = rawData;
  idx++;

  if (idx >= N)
  {
    idx = 0;
  }

  return sum / N;
}

void filterInit(u16_t initData)
{
  for (u8_t i = 0; i < N; i++)
  {
    readings[i] = initData;
    sum += initData;
  }
}

void setup()
{
  pinMode(LDR, INPUT);
  btnBlink.init();
  btnCrash.init();

  ledY.init();
  ledW.init();

  Serial.begin(115200);
  filterInit(analogRead(LDR));
}

void ldr_blink()
{
  if (millis() - lastTimeChange > ADC_PERIOD)
  {

    u16_t adc_value = analogRead(LDR);
    u16_t filtered_adc_value = movingAvg(adc_value);
    Serial.printf("adc raw value %d adc filtered  %d Last time change %d\n", adc_value, filtered_adc_value, lastTimeChange);
    if (filtered_adc_value < LDR_THRESHOLD_ON)
    {
      ledW.set(true);
    }
    if (filtered_adc_value > LDR_THRESHOLD_OFF)
    {
      ledW.set(false);
    }

    lastTimeChange = millis();
  }
}

void loop()
{ // нескінченний цикл — серце програми

  btnBlink.poll();
  btnCrash.poll();

  if (btnBlink.wasPressed())
  {
    mode = (mode != Mode::BLINK) ? Mode::BLINK : Mode::NORMAL;
    ledY.set(false);
    ledW.set(false);
  }

  if (btnCrash.wasPressed())
  {
    mode = (mode != Mode::CRASHED) ? Mode::CRASHED : Mode::NORMAL;
    ledY.set(false);
    ledW.set(false);
  }

  switch (mode)
  {
  case Mode::NORMAL:
    ldr_blink();
    break;

  case Mode::BLINK:
    ledY.blink(700);
    break;

  case Mode::CRASHED:
    ledY.blink(200);
    ledW.blink(300);
    break;
  }
}