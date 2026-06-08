#ifndef FAF_ESP32_ARDUINO_LED_CLASS_H
#define FAF_ESP32_ARDUINO_LED_CLASS_H

/*
 * Firmware Abstraction Facility
 * Copyright (C) 2026 Alice aka Nyumi.
 *
 * Released under the MIT License.
 * See LICENSE file or <https://opensource.org/licenses/MIT> for details.
 */

#include "FAF/FAF_Driver_Internal.h"
#include "FAF/contracts/FAF_Toggleable.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct arduino_led_instance_t {
    FAF_Driver_Instance i_parent;
} ArduinoLED_Instance;

typedef struct arduino_led_class_t {
    FAF_Driver c_parent;
    IToggleable c_toggleable;
} ArduinoLED_Class;

#ifdef __cplusplus
}
#endif

#endif // FAF_ESP32_ARDUINO_LED_CLASS_H