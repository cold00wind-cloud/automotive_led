#include <Arduino.h>
#define LDR 2

void setup()
{
  pinMode(LDR, INPUT);
  Serial.begin(115200);
  Serial.println("setuped\n");
}

void loop()
{ // нескінченний цикл — серце програми

  u16_t adc_value = analogRead(LDR);
  u16_t v_calc = (uint32_t)adc_value * 3100 / 4095;
  u16_t adc_value_mv = analogReadMilliVolts(LDR);
  float relative_error = (fabs(v_calc - adc_value_mv) / adc_value_mv) * 100.0f;
  Serial.printf("adc raw: %u\t|\tcalc: %u mV\t|\tmeasured: %u mV\t|\tdiff: %.2f%%\n",
                adc_value, v_calc, adc_value_mv, relative_error);
  delay(100);
}