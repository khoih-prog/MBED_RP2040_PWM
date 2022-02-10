/****************************************************************************************************************************
  MBED_RP2040_PWM_Impl.h
  For RP2040 boards
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/MBED_RP2040_PWM
  Licensed under MIT license

  Version: 1.0.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K.Hoang      09/02/2022 Initial coding for RP2040 using ArduinoCore-mbed mbed_rp2040 core
*****************************************************************************************************************************/

#ifndef MBED_RP2040_PWM_IMPL_H
#define MBED_RP2040_PWM_IMPL_H

#ifndef _PWM_LOGLEVEL_
  #define _PWM_LOGLEVEL_       1
#endif

#include "Arduino.h"
#include "MBED_RP2040_PWM.h"

#include "PWM_Generic_Debug.h"


bool isValidPWMPin(const pin_size_t& pin)
{
  if ( (pin < NUM_DIGITAL_PINS) )
  {
    return true;
  }
  
  PWM_LOGERROR1("Not PWM pin = ", pin);
  
  return false;
}

bool isValidPWMDutyCycle(const pin_size_t& pin, const float& dutyCycle)
{
  if ( (dutyCycle < 0.0f) || (dutyCycle > 100.0f) )
  {
    PWM_LOGERROR3("Bad dutyCycle = ", dutyCycle, ", pin = ", pin);
    
    return false;
  }

  return true;
}

// Check if freq > 0
bool isValidPWMFreq(const pin_size_t& pin, const float& frequency)
{
  if ( frequency <= 0.0f )
  {
    PWM_LOGERROR3("Bad Freq = ", frequency, ", pin = ", pin);

    return false;
  }
  
  return true;
}

bool isValidPWMSettings(const pin_size_t& pin, const float& frequency, const float& dutyCycle)
{
  if ( !isValidPWMPin(pin) || !isValidPWMFreq(pin, frequency) || !isValidPWMDutyCycle(pin, dutyCycle) )
  { 
    return false;
  } 
  
  return true;
}

// dutyCycle from 0.0f to 100.0f
mbed::PwmOut* setPWM(mbed::PwmOut* &pwm, const pin_size_t& pin, const float& frequency, const float& dutyCycle)
{
  PWM_LOGDEBUG7("Freq = ", frequency, ", \tDutyCycle = ", dutyCycle, ", \tDutyCycle % = ", dutyCycle / 100, ", \tPin = ", pin);
    
  if ( !isValidPWMSettings(pin, frequency, dutyCycle) )
  {   
    return NULL;
  }

  float percent = dutyCycle / 100.0f;
  
  if (digitalPinToPwm(pin) == NULL)
  {
    PWM_LOGDEBUG("New pwm");
    
    pwm = new mbed::PwmOut(digitalPinToPinName(pin));
    
    digitalPinToPwm(pin) = pwm;

    pwm->period_us( 1000000.0f/frequency );  

    pwm->write(percent);
  }
  else if (pwm && (digitalPinToPwm(pin) == pwm) )
  {
    PWM_LOGDEBUG("Use existing pwm");
    
    pwm->period_us( 1000000.0f/frequency );  

    pwm->write(percent);
  }
  
  return pwm;
}

mbed::PwmOut* stopPWM(mbed::PwmOut* &pwm, const pin_size_t& pin)
{
  return setPWM(pwm, pin, 1000.0f, 0.0f);
}

// Return Freq in float Hz
float getFreq(mbed::PwmOut* &pwm)
{
  return (float) 1000000.0f / pwm->read_period_us();
}

// Return DutyCycle in float (from 0.0f - 100.0f)
float getDutyCycle(mbed::PwmOut* &pwm)
{
  return (pwm->read() * 100.0f);
}

// Return PulseWidth in uint64_t uS
float getPulseWidth_uS(mbed::PwmOut* &pwm)
{
  return ( pwm->read() * pwm->read_period_us() );
}

// Return PulseWidth in uint64_t uS
float getPeriod_uS(mbed::PwmOut* &pwm)
{
  return (float) pwm->read_period_us();
}


#endif    // MBED_RP2040_PWM_IMPL_H


