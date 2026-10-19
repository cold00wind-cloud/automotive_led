#include <Arduino.h>
#include "config.h"
#include "Button.h"

Mode mode = Mode::NORMAL;

Button btnCrash(BTN_CRASHE);
Button btnBlink(BTN_BLINK);

u16_t readings[N];
u8_t idx = 0;
u32_t sum = 0;

u8_t lastButtonCrashState = 0;
u8_t lastButtonBlinkState = 0;

u8_t ledState_W = 0;
u8_t ledState_Y = 0;

u32_t lastTimeChange_buttonC = 0;
u32_t lastTimeChange_buttonB = 0;

u32_t lastTimeChange_LED_Y = 0;
u32_t lastTimeChange_LED_W = 0;

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
  pinMode(LED_W, OUTPUT);
  pinMode(LED_Y, OUTPUT);
  pinMode(LDR, INPUT);
  btnBlink.init();
  btnCrash.init();
  Serial.begin(115200);
  Serial.println("setuped\n");
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
      digitalWrite(LED_W, HIGH);
    }
    if (filtered_adc_value > LDR_THRESHOLD_OFF)
    {
      digitalWrite(LED_W, LOW);
    }

    lastTimeChange = millis();
  }
}

void blink()
{
  if (millis() - lastTimeChange_LED_Y > 700)
  {
    lastTimeChange_LED_Y = millis();
    ledState_Y = (ledState_Y == HIGH) ? LOW : HIGH;
    Serial.printf("LED state: %d\n", ledState_Y);
    digitalWrite(LED_Y, ledState_Y);
  }
}

void crashed()
{
  if (millis() - lastTimeChange_LED_Y > 200)
  {
    lastTimeChange_LED_Y = millis();
    ledState_Y = (ledState_Y == HIGH) ? LOW : HIGH;
    Serial.printf("LED Y state: %d\n", ledState_Y);
    digitalWrite(LED_Y, ledState_Y);
  }

  if (millis() - lastTimeChange_LED_W > 300)
  {
    lastTimeChange_LED_W = millis();
    ledState_W = (ledState_W == HIGH) ? LOW : HIGH;
    Serial.printf("LED W state: %d\n", ledState_W);
    digitalWrite(LED_W, ledState_W);
  }
}

void loop()
{ // нескінченний цикл — серце програми

  btnBlink.poll();
  btnCrash.poll();

  if (btnBlink.wasPressed())
  {
    mode = (mode != Mode::BLINK) ? Mode::BLINK : Mode::NORMAL;
    ledState_Y = (mode == Mode::NORMAL) ? LOW : HIGH;
    digitalWrite(LED_Y, ledState_Y);
  }

  if (btnCrash.wasPressed())
  {
    mode = (mode != Mode::CRASHED) ? Mode::CRASHED : Mode::NORMAL;
    ledState_Y = (mode == Mode::NORMAL) ? LOW : HIGH;
    ledState_W = (mode == Mode::NORMAL) ? LOW : HIGH;
    digitalWrite(LED_Y, ledState_Y);
    digitalWrite(LED_W, ledState_W);
  }

  switch (mode)
  {
  case Mode::NORMAL:
    ldr_blink();
    break;

  case Mode::BLINK:
    blink();
    break;

  case Mode::CRASHED:
    crashed();
    break;
  }
}