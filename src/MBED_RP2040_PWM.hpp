/****************************************************************************************************************************
  MBED_RP2040_PWM.hpp
  For RP2040 boards
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/MBED_RP2040_PWM
  Licensed under MIT license

  Version: 1.0.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K.Hoang      09/02/2022 Initial coding for RP2040 using ArduinoCore-mbed mbed_rp2040 core
*****************************************************************************************************************************/

#pragma once

#ifndef MBED_RP2040_PWM_HPP
#define MBED_RP2040_PWM_HPP

#if !( defined(ARDUINO_NANO_RP2040_CONNECT) || defined(ARDUINO_RASPBERRY_PI_PICO) || defined(ARDUINO_ADAFRUIT_FEATHER_RP2040) || \
      defined(ARDUINO_GENERIC_RP2040) ) && defined(ARDUINO_ARCH_MBED)
  #error This code is intended to run on the MBED RP2040 platform! Please check your Tools->Board setting.
#endif

#ifndef MBED_RP2040_PWM_VERSION
  #define MBED_RP2040_PWM_VERSION             "MBED_RP2040_PWM v1.0.0"
  
  #define MBED_RP2040_PWM_VERSION_MAJOR       1
  #define MBED_RP2040_PWM_VERSION_MINOR       0
  #define MBED_RP2040_PWM_VERSION_PATCH       0

  #define MBED_RP2040_PWM_VERSION_INT         1000000
#endif


///////////////////////////////////////////

#include "Arduino.h"
#include "pinDefinitions.h"
#include "PwmOut.h"

///////////////////////////////////////////
  

///////////////////////////////////////////

#ifndef _PWM_LOGLEVEL_
  #define _PWM_LOGLEVEL_       1
#endif

#include "PWM_Generic_Debug.h"

///////////////////////////////////////////

bool isValidPWMPin(const pin_size_t& pin);

bool isValidPWMFreq(const pin_size_t& pin, const float& frequency);

bool isValidPWMDutyCycle(const pin_size_t& pin, const float& dutyCycle);

bool isValidPWMSettings(const pin_size_t& pin, const float& frequency, const float& dutyCycle);

mbed::PwmOut* setPWM(mbed::PwmOut* &pwm, const pin_size_t& pin, const float& frequency, const float& dutyCycle);

mbed::PwmOut* stopPWM(mbed::PwmOut* &pwm, const pin_size_t& pin);

float getFreq(mbed::PwmOut* &pwm);

float getDutyCycle(mbed::PwmOut* &pwm);

float getPulseWidth_uS(mbed::PwmOut* &pwm);

float getPeriod_uS(mbed::PwmOut* &pwm);

#endif    // MBED_RP2040_PWM_HPP

