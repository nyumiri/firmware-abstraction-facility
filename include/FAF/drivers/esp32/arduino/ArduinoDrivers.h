#ifndef FAF_ESP32_ARDUINO_DRIVERS_H
#define FAF_ESP32_ARDUINO_DRIVERS_H

/*
 * Firmware Abstraction Facility
 * Copyright (C) 2026 Alice aka Nyumi.
 *
 * Released under the MIT License.
 * See LICENSE file or <https://opensource.org/licenses/MIT> for details.
 */

#ifdef ARDUINO_ARCH_ESP32
#   include "FAF/drivers/esp32/arduino/led/ArduinoLED_API.h"
#   include "FAF/drivers/esp32/arduino/wifi/ArduinoWifi_API.h"
#   ifdef FAF_ARDUINO_MQTT_ENABLE
#       include "FAF/drivers/esp32/arduino/mqtt/ArduinoMQTT_API.h"
#   endif
#else
#   warning "ESP32 Arduino Drivers only works on ESP32 Arduino Platform! Check build flags."
#endif

#endif // FAF_ESP32_ARDUINO_DRIVERS_H