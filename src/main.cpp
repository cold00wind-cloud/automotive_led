#include <Arduino.h>
#include "config.h"
#include "Button.h"
#include "Led.h"
#include "Ldr.h"

Mode mode = Mode::NORMAL;

Button btnCrash(BTN_CRASHE);
Button btnBlink(BTN_BLINK);

Led ledY(LED_Y);
Led ledW(LED_W);

Ldr ldr(LDR, LDR_THRESHOLD_OFF, LDR_THRESHOLD_ON, ADC_PERIOD);

void setup()
{
  Serial.begin(115200);

  btnBlink.init();
  btnCrash.init();

  ledY.init();
  ledW.init();

  ldr.init();
}

void loop()
{ // нескінченний цикл — серце програми

  btnBlink.poll();
  btnCrash.poll();
  ldr.poll();

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
    ledW.set(ldr.isDark());
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