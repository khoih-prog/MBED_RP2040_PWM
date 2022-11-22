/****************************************************************************************************************************
  multiFileProject.ino

  For RP2040 boards
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/MBED_RP2040_PWM
  Licensed under MIT license
*****************************************************************************************************************************/

// To demo how to include files in multi-file Projects

#if !( defined(ARDUINO_NANO_RP2040_CONNECT) || defined(ARDUINO_RASPBERRY_PI_PICO) || defined(ARDUINO_ADAFRUIT_FEATHER_RP2040) || \
      defined(ARDUINO_GENERIC_RP2040) ) && defined(ARDUINO_ARCH_MBED)
#error This code is intended to run on the MBED RP2040 platform! Please check your Tools->Board setting.
#endif

#define MBED_RP2040_PWM_VERSION_MIN_TARGET      "MBED_RP2040_PWM v1.0.0"
#define MBED_RP2040_PWM_VERSION_MIN             1000000

#include "multiFileProject.h"

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "MBED_RP2040_PWM.h"

void setup()
{
  Serial.begin(115200);

  while (!Serial);

  Serial.println("\nStart multiFileProject");
  Serial.println(MBED_RP2040_PWM_VERSION);

#if defined(MBED_RP2040_PWM_VERSION_MIN)

  if (MBED_RP2040_PWM_VERSION_INT < MBED_RP2040_PWM_VERSION_MIN)
  {
    Serial.print("Warning. Must use this example on Version equal or later than : ");
    Serial.println(MBED_RP2040_PWM_VERSION_MIN_TARGET);
  }

#endif
}

void loop()
{
  // put your main code here, to run repeatedly:
}
