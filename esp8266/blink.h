
#ifndef __BLINK_H__
#define __BLINK_H__

#include <Arduino.h> 

#define LED_PIN 2

class LED 
{
  public:
    static void begin() { pinMode(LED_PIN, OUTPUT); }
    static void blink(uint32_t count=1, int ms=1000) {
      for(uint32_t n=0; n<count; n++){
        digitalWrite(LED_PIN, LOW); 
        delay(ms/2);
        digitalWrite(LED_PIN, HIGH); 
        delay(ms/2);
      }
    }
};

#endif
