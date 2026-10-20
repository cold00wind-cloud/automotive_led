#include <Arduino.h>
#include "config.h"
#include "MovingAverage.h"

u16_t MovingAverage::add(u16_t rawData)
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

void MovingAverage::init(u16_t initData)
{
  for (u8_t i = 0; i < N; i++)
  {
    readings[i] = initData;
    sum += initData;
  }
}