#ifndef FAF_ESP32_ARDUINO_LED_API_H
#define FAF_ESP32_ARDUINO_LED_API_H

/*
 * Firmware Abstraction Facility
 * Copyright (C) 2026 Alice aka Nyumi.
 *
 * Released under the MIT License.
 * See LICENSE file or <https://opensource.org/licenses/MIT> for details.
 */

#include "FAF/FAF_Driver.h"

#define ArduinoLED_Class_SIGNATURE 0xA1B2C3D4

#ifdef __cplusplus
extern "C" {
#endif

void ArduinoLED_Constructor(FAF_Driver* self);

void ArduinoLED_Class_Turn_ON(FAF_Driver* self);
void ArduinoLED_Class_Turn_OFF(FAF_Driver* self);

#ifdef __cplusplus
}
#endif

#endif // FAF_ESP32_ARDUINO_LED_API_H