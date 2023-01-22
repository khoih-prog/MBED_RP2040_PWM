# MBED_RP2040_PWM Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/MBED_RP2040_PWM.svg?)](https://www.ardu-badge.com/MBED_RP2040_PWM)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/MBED_RP2040_PWM.svg)](https://github.com/khoih-prog/MBED_RP2040_PWM/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/MBED_RP2040_PWM/blob/main/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/MBED_RP2040_PWM.svg)](http://github.com/khoih-prog/MBED_RP2040_PWM/issues)


<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Donate to my libraries using BuyMeACoffee" style="height: 50px !important;width: 181px !important;" ></a>
<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-donate-orange.svg?logo=buy-me-a-coffee&logoColor=FFDD00" style="height: 20px !important;width: 200px !important;" ></a>


---
---

## Table of Contents

* [Why do we need this MBED_RP2040_PWM library](#why-do-we-need-this-MBED_RP2040_PWM-library)
  * [Features](#features)
  * [Currently supported Boards](#currently-supported-boards)
* [Changelog](changelog.md)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [HOWTO Fix `Multiple Definitions` Linker Error](#howto-fix-multiple-definitions-linker-error) 
* [Usage](#usage)
  * [1. Prepare PWM settings](#1-Prepare-PWM-settings)
  * [2. Set PWM Frequency and dutycycle](#2-Set-PWM-Frequency-and-dutycycle)
  * [3. Read actual PWM Parameters](#3-Read-actual-PWM-Parameters) 
* [Examples](#examples)
  * [ 1. PWM_Multi](examples/PWM_Multi)
  * [ 2. PWM_Single](examples/PWM_Single)
  * [ 3. multiFileProject](examples/multiFileProject)
  * [ 4. PWM_StepperControl](examples/PWM_StepperControl). **New**
* [Example PWM_Multi](#example-PWM_Multi)
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [1. PWM_Single on RaspberryPi Pico](#1-PWM_Single-on-RaspberryPi-Pico)
  * [2. PWM_Multi on RaspberryPi Pico](#2-PWM_Multi-on-RaspberryPi-Pico)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)

---
---


### Why do we need this [MBED_RP2040_PWM library](https://github.com/khoih-prog/MBED_RP2040_PWM)

### Features

This library enables you to use Hardware-based PWM to create and output PWM to pins on **MBED RP2040-based boards such as Nano_RP2040_Connect, RASPBERRY_PI_PICO**, using [**Arduino-mbed mbed_rp2040 or mbed_nano** core](https://github.com/arduino/ArduinoCore-mbed)

This library is using the **same or similar functions** as other FastPWM libraries, as follows, to enable you to **port your PWM code easily between platforms**

 1. [**RP2040_PWM**](https://github.com/khoih-prog/RP2040_PWM)
 2. [**AVR_PWM**](https://github.com/khoih-prog/AVR_PWM)
 3. [**megaAVR_PWM**](https://github.com/khoih-prog/megaAVR_PWM)
 4. [**ESP32_FastPWM**](https://github.com/khoih-prog/ESP32_FastPWM)
 5. [**SAMD_PWM**](https://github.com/khoih-prog/SAMD_PWM)
 6. [**SAMDUE_PWM**](https://github.com/khoih-prog/SAMDUE_PWM)
 7. [**nRF52_PWM**](https://github.com/khoih-prog/nRF52_PWM)
 8. [**Teensy_PWM**](https://github.com/khoih-prog/Teensy_PWM)
 9. [**ATtiny_PWM**](https://github.com/khoih-prog/ATtiny_PWM)
10. [**Dx_PWM**](https://github.com/khoih-prog/Dx_PWM)
11. [**Portenta_H7_PWM**](https://github.com/khoih-prog/Portenta_H7_PWM)
12. [**MBED_RP2040_PWM**](https://github.com/khoih-prog/MBED_RP2040_PWM)
13. [**nRF52_MBED_PWM**](https://github.com/khoih-prog/nRF52_MBED_PWM)
14. [**STM32_PWM**](https://github.com/khoih-prog/STM32_PWM)


---

The most important feature is they're purely `hardware-based PWM` channels. Therefore, the frequency can be higher than `hybrid or software-based PWM`, and their executions are **not blocked by bad-behaving functions / tasks**. This important feature is absolutely necessary for mission-critical tasks.

The [**PWM_Multi**](examples/PWM_Multi) will demonstrate the usage of multichannel PWM using multiple Hardware Timers. The 4 independent Hardware Timers are used **to control 4 different PWM outputs**, with totally independent frequencies and dutycycles. You can **start, stop, change and restore the settings of any PWM channel on-the-fly**.

Being hardware-based PWM, their executions are not blocked by bad-behaving functions / tasks, such as connecting to WiFi, Internet or Blynk services.

This non-being-blocked important feature is absolutely necessary for mission-critical tasks.


---

### Currently supported Boards

1. RP2040-based boards such as **Nano_RP2040_Connect, RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, etc. using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed)

---
---

## Prerequisites

 1. [`Arduino IDE 1.8.19+` for Arduino](https://github.com/arduino/Arduino). [![GitHub release](https://img.shields.io/github/release/arduino/Arduino.svg)](https://github.com/arduino/Arduino/releases/latest)
 2. [`Arduino mbed_rp2040 core 3.5.4+`](https://github.com/arduino/ArduinoCore-mbed) for Arduino (Use Arduino Board Manager) RP2040-based boards, such as **Arduino Nano RP2040 Connect, RASPBERRY_PI_PICO, etc.**. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-mbed.svg)](https://github.com/arduino/ArduinoCore-mbed/releases/latest)
---
---

## Installation

### Use Arduino Library Manager

The best and easiest way is to use `Arduino Library Manager`. Search for [**MBED_RP2040_PWM**](https://github.com/khoih-prog/MBED_RP2040_PWM), then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/MBED_RP2040_PWM.svg?)](https://www.ardu-badge.com/MBED_RP2040_PWM) for more detailed instructions.

### Manual Install

Another way to install is to:

1. Navigate to [**MBED_RP2040_PWM**](https://github.com/khoih-prog/MBED_RP2040_PWM) page.
2. Download the latest release `MBED_RP2040_PWM-main.zip`.
3. Extract the zip file to `MBED_RP2040_PWM-main` directory 
4. Copy whole `MBED_RP2040_PWM-main` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**MBED_RP2040_PWM** library](https://registry.platformio.org/libraries/khoih-prog/MBED_RP2040_PWM) by using [Library Manager](https://registry.platformio.org/libraries/khoih-prog/MBED_RP2040_PWM/installation). Search for **MBED_RP2040_PWM** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)


---
---

### HOWTO Fix `Multiple Definitions` Linker Error

The current library implementation, using `xyz-Impl.h` instead of standard `xyz.cpp`, possibly creates certain `Multiple Definitions` Linker error in certain use cases.

You can include this `.hpp` file

```cpp
// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include "MBED_RP2040_PWM.hpp"    //https://github.com/khoih-prog/MBED_RP2040_PWM
```

in many files. But be sure to use the following `.h` file **in just 1 `.h`, `.cpp` or `.ino` file**, which must **not be included in any other file**, to avoid `Multiple Definitions` Linker Error

```cpp
// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "MBED_RP2040_PWM.h"      //https://github.com/khoih-prog/MBED_RP2040_PWM
```

Check the new [**multiFileProject** example](examples/multiFileProject) for a `HOWTO` demo.

---
---

## Usage

Before using any Timer for a PWM channel, you have to make sure the Timer has not been used by any other purpose.

### 1. Prepare PWM settings

```cpp
// Valid pins from 0-29 (GP0-GP29)
uint32_t myPin  = 15;    // GP15

float dutyCycle = 50.0f;

float freq      = 5000.0f;

mbed::PwmOut* pwm   = NULL;
```

#### 2. Set PWM Frequency and dutycycle

```cpp
void setup()
{
  ....
  
  setPWM(pwm, myPin, freq, dutyCycle);
}  
```

#### 3. Read actual PWM Parameters

Use these functions

```cpp
float getFreq(mbed::PwmOut* &pwm);

float getDutyCycle(mbed::PwmOut* &pwm);

float getPulseWidth_uS(mbed::PwmOut* &pwm);

float getPeriod_uS(mbed::PwmOut* &pwm);
```

For example

```cpp
// Valid pins from 0-29 (GP0-GP29)
uint32_t myPin  = 15;    // GP15

float dutyCycle = 50.0f;

float freq      = 5000.0f;

mbed::PwmOut* pwm   = NULL;

setPWM(pwm, myPin, freq, dutyCycle);

if (pwm)
{
  Serial.print(getPulseWidth_uS(pwm)); Serial.print(F("\t\t"));
  Serial.print(getDutyCycle(pwm)); Serial.print(F("\t\t"));
  Serial.print(getPeriod_uS(pwm));
}
```

---
---

### Examples: 

 1. [PWM_Multi](examples/PWM_Multi)
 2. [PWM_Single](examples/PWM_Single)
 3. [**multiFileProject**](examples/multiFileProject)
 4. [**PWM_StepperControl**](examples/PWM_StepperControl) **New**

 
---
---

### Example [PWM_Multi](examples/PWM_Multi)

https://github.com/khoih-prog/MBED_RP2040_PWM/blob/97018ae974e1f1dab9e77b4967ee7726b60b74c1/examples/PWM_Multi/PWM_Multi.ino#L10-L237


---
---

### Debug Terminal Output Samples

### 1. PWM_Single on RaspberryPi Pico

The following is the sample terminal output when running example [PWM_Single](examples/PWM_Single) on **RaspberryPi Pico** to demonstrate how to start a single PWM channel, then stop, change, restore the PWM settings on-the-fly.


```cpp
Starting PWM_Single on RaspberryPi Pico
MBED_RP2040_PWM v1.0.1
[PWM] Freq = 5000.00, DutyCycle % = 50.00, DutyCycle = 0.50, Pin = 15

============================================
PW (us)		DutyCycle	Period (uS)
============================================
100.00		50.00		200.00
Stop PWM
0.00		0.00		1000.00
0.00		0.00		1000.00
Change PWM
25.00		25.00		100.00
25.00		25.00		100.00
Restore PWM
100.00		50.00		200.00
100.00		50.00		200.00
Stop PWM
0.00		0.00		1000.00
0.00		0.00		1000.00
Change PWM
25.00		25.00		100.00
25.00		25.00		100.00
```

---

### 2. PWM_Multi on RaspberryPi Pico

The following is the sample terminal output when running example [**PWM_Multi**](examples/PWM_Multi) on **RaspberryPi Pico** to demonstrate how to start multiple PWM channels, then stop, change, restore the PWM settings on-the-fly.

```cpp
Starting PWM_Multi on RaspberryPi Pico
MBED_RP2040_PWM v1.0.1
[PWM] Freq = 1000.00, 	DutyCycle % = 50.00, 	DutyCycle = 0.50, 	Pin = GP12
[PWM] Freq = 2500.00, 	DutyCycle % = 50.00, 	DutyCycle = 0.50, 	Pin = GP13
[PWM] Freq = 4000.00, 	DutyCycle % = 50.00, 	DutyCycle = 0.50, 	Pin = GP14
[PWM] Freq = 5000.00, 	DutyCycle % = 50.00, 	DutyCycle = 0.50, 	Pin = GP15

=========================================================
PW (us) 0	PW (us) 1	PW (us) 2	PW (us) 3	
=========================================================
500.00		200.00		125.00		100.00		
Stop all PWM
0.00		0.00		0.00		0.00		
0.00		0.00		0.00		0.00		
Change all PWM
125.00		50.00		31.25		25.00		
125.00		50.00		31.25		25.00		
Restore all PWM
500.00		200.00		125.00		100.00		
500.00		200.00		125.00		100.00		
Stop all PWM
0.00		0.00		0.00		0.00		
0.00		0.00		0.00		0.00		
Change all PWM
125.00		50.00		31.25		25.00		
125.00		50.00		31.25		25.00		
Restore all PWM
500.00		200.00		125.00		100.00		
500.00		200.00		125.00		100.00		
```


---
---

### Debug

Debug is enabled by default on Serial.

You can also change the debugging level `_PWM_LOGLEVEL_` from 0 to 4

```cpp
// Don't define _PWM_LOGLEVEL_ > 0. Only for special ISR debugging only. Can hang the system.
#define _PWM_LOGLEVEL_     0
```

---

### Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the core for Arduino boards.

Sometimes, the library will only work if you update the board core to the latest version because I am using newly added functions.


---
---

### Issues

Submit issues to: [MBED_RP2040_PWM issues](https://github.com/khoih-prog/MBED_RP2040_PWM/issues)

---
---

## TO DO

1. Search for bug and improvement.
2. Similar features for remaining Arduino boards

---

## DONE

1. Basic hardware multi-channel PWM for **Nano_RP2040_Connect and RASPBERRY_PI_PICO**, etc. using [**Arduino-mbed** core](https://github.com/arduino/ArduinoCore-mbed)
2. Add Table of Contents
3. Permit to start, stop, modify, restore PWM settings on-the-fly
4. Optimize library code by using `reference-passing` instead of `value-passing`
5. Use `h-only` style
6. Add functions to read PWM parameters
7. Use `allman astyle` and add `utils`
8. Add example [PWM_StepperControl](https://github.com/khoih-prog/Portenta_H7_PWM/examples/PWM_StepperControl) to demo how to control Stepper Motor using PWM

---
---

### Contributions and Thanks

Many thanks for everyone for bug reporting, new feature suggesting, testing and contributing to the development of this library.

1. Thanks to [Paul van Dinther](https://github.com/dinther) for proposing new way to use PWM to drive Stepper-Motor in [Using PWM to step a stepper driver #16](https://github.com/khoih-prog/RP2040_PWM/issues/16), leading to v1.0.1

<table>
  <tr>
    <td align="center"><a href="https://github.com/dinther"><img src="https://github.com/dinther.png" width="100px;" alt="dinther"/><br /><sub><b>Paul van Dinther</b></sub></a><br /></td>
  </tr>
</table>

---

## Contributing

If you want to contribute to this project:

- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- The library is licensed under [MIT](https://github.com/khoih-prog/MBED_RP2040_PWM/blob/main/LICENSE)

---

## Copyright

Copyright (c) 2022- Khoi Hoang


