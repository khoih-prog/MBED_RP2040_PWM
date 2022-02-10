/****************************************************************************************************************************
  PWM_Multi.ino
  For RP2040 boards
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/MBED_RP2040_PWM
  Licensed under MIT license
*****************************************************************************************************************************/

#if !( defined(ARDUINO_NANO_RP2040_CONNECT) || defined(ARDUINO_RASPBERRY_PI_PICO) || defined(ARDUINO_ADAFRUIT_FEATHER_RP2040) || \
      defined(ARDUINO_GENERIC_RP2040) ) && defined(ARDUINO_ARCH_MBED)
  #error This code is intended to run on the MBED RP2040 platform! Please check your Tools->Board setting.
#endif

#define _PWM_LOGLEVEL_       1

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "MBED_RP2040_PWM.h"

#define LED_ON        LOW
#define LED_OFF       HIGH

#ifndef LED_BUILTIN
  #define LED_BUILTIN       25
#endif

#ifndef LED_BLUE
  #define LED_BLUE          10
#endif

#ifndef LED_RED
  #define LED_RED           11
#endif

// Valid pins from 0-29 (GP0-GP29)
uint32_t pins[]       = { 12, 13, 14, 15 };

#define NUM_OF_PINS       ( sizeof(pins) / sizeof(uint32_t) )

float dutyCycle[]      = { 50.0f, 50.0f, 50.0f, 50.0f };

float freq[]           = { 1000.0f, 2500.0f, 4000.0f, 5000.0f };

float curDutyCycle[]   = { 50.0f, 50.0f, 50.0f, 50.0f };

float curFreq[]        = { 1000.0f, 2500.0f, 4000.0f, 5000.0f };

mbed::PwmOut* pwm[]    = { NULL, NULL, NULL, NULL };

void startAllPWM()
{
  digitalWrite(LED_BUILTIN, LED_ON);
  digitalWrite(LED_BLUE, LED_OFF);
  digitalWrite(LED_RED, LED_OFF);
  
  for (uint8_t index = 0; index < NUM_OF_PINS; index++)
  {
    PWM_LOGERROR7("Freq = ", freq[index], ", \tDutyCycle % = ", dutyCycle[index], ", \tDutyCycle = ", dutyCycle[index] / 100, ", \tPin = GP", pins[index]);
    
    // setPWM(mbed::PwmOut* &pwm, pinsize_t pin, float frequency, float dutyCycle)
    setPWM(pwm[index], pins[index], freq[index], dutyCycle[index]);
  }
}

void restoreAllPWM()
{
  digitalWrite(LED_BUILTIN, LED_ON);
  digitalWrite(LED_BLUE, LED_OFF);
  digitalWrite(LED_RED, LED_OFF);
  
  for (uint8_t index = 0; index < NUM_OF_PINS; index++)
  {
    curFreq[index]      = freq[index];
    curDutyCycle[index] = dutyCycle[index];
    
    // setPWM(mbed::PwmOut* &pwm, pinsize_t pin, float frequency, float dutyCycle)
    setPWM(pwm[index], pins[index], freq[index], dutyCycle[index]);
  }
}

void changeAllPWM()
{
  digitalWrite(LED_BUILTIN, LED_OFF);
  digitalWrite(LED_BLUE, LED_ON);
  digitalWrite(LED_RED, LED_OFF);
  
  for (uint8_t index = 0; index < NUM_OF_PINS; index++)
  {
    curFreq[index]      = freq[index] * 2;
    curDutyCycle[index] = dutyCycle[index] / 2;
    
    // setPWM(mbed::PwmOut* &pwm, pinsize_t pin, float frequency, float dutyCycle)
    setPWM(pwm[index], pins[index], curFreq[index], curDutyCycle[index]);
  }
}

void stopAllPWM()
{
  digitalWrite(LED_BUILTIN, LED_OFF);
  digitalWrite(LED_BLUE, LED_OFF);
  digitalWrite(LED_RED, LED_ON);
  
  for (uint8_t index = 0; index < NUM_OF_PINS; index++)
  {
    curFreq[index]      = 1000.0f;
    curDutyCycle[index] = 0.0f;
    
    //stopPWM(mbed::PwmOut* &pwm, pinsize_t pin)
    stopPWM(pwm[index], pins[index]);
  }
}

void printLine()
{
  Serial.println(F("\n========================================================="));
}

void printPulseWidth()
{
  static uint32_t num = 0;

  if (num++ % 50 == 0)
  {
    printLine();
    
    for (uint8_t index = 0; index < NUM_OF_PINS; index++)
    {
      Serial.print(F("PW (us) ")); Serial.print(index); Serial.print(F("\t"));  
    }

    printLine();
  }
 
  if (num > 1)
  {
    for (uint8_t index = 0; index < NUM_OF_PINS; index++)
    {
      if (pwm[index])
      {
        Serial.print(getPulseWidth_uS(pwm[index])); Serial.print(F("\t\t"));
      }
    }

    Serial.println();
  }
}

#define PRINT_INTERVAL      10000L
#define CHANGE_INTERVAL     20000L

void check_status()
{
  static unsigned long checkstatus_timeout  = 0;
  static unsigned long changePWM_timeout    = 0;

  static bool PWM_orig  = true;
  static uint32_t count = 0;

  // Print every PRINT_INTERVAL (10) seconds.
  if ((millis() > checkstatus_timeout) || (checkstatus_timeout == 0))
  {
    printPulseWidth();
    checkstatus_timeout = millis() + PRINT_INTERVAL;
  }

  if ( (millis() > changePWM_timeout) && (millis() > CHANGE_INTERVAL) )
  {
    
    if (PWM_orig)
    {
      if (count++ %2 == 0)
      {
        Serial.println("Stop all PWM");
        stopAllPWM();
      }
      else
      {
        Serial.println("Change all PWM");
        
        changeAllPWM();

        PWM_orig = !PWM_orig;
      }
    }
    else
    {
      Serial.println("Restore all PWM");
      
      restoreAllPWM();

      PWM_orig = !PWM_orig;
    }
      
    changePWM_timeout = millis() + CHANGE_INTERVAL;
  }
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  digitalWrite(LED_BUILTIN, LED_OFF);
  digitalWrite(LED_BLUE, LED_OFF);
  digitalWrite(LED_RED, LED_OFF);

  for (uint8_t index = 0; index < NUM_OF_PINS; index++)
  {
    pinMode(pins[index], OUTPUT);
    digitalWrite(pins[index], LOW);
  }

  Serial.begin(115200);
  while (!Serial);

  delay(100);

  Serial.print(F("\nStarting PWM_Multi on ")); Serial.println(BOARD_NAME);
  Serial.println(MBED_RP2040_PWM_VERSION);

  // Automatically retrieve TIM instance and channel associated to pin
  // This is used to be compatible with all STM32 series automatically.

  startAllPWM();
}

void loop()
{
  check_status();
}
