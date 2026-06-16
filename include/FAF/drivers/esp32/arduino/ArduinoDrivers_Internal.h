#ifndef FAF_ESP32_ARDUINO_DRIVERS_ITN_H
#define FAF_ESP32_ARDUINO_DRIVERS_ITN_H

/*
 * Firmware Abstraction Facility
 * Copyright (C) 2026 Alice aka Nyumi.
 *
 * Released under the MIT License.
 * See LICENSE file or <https://opensource.org/licenses/MIT> for details.
 */

#ifdef ARDUINO_ARCH_ESP32
#   include "FAF/drivers/esp32/arduino/led/ArduinoLED_Class.h"
#   include "FAF/drivers/esp32/arduino/led/ArduinoLED_Conf.h"
#   include "FAF/drivers/esp32/arduino/wifi/ArduinoWifi_Class.h"
#   include "FAF/drivers/esp32/arduino/wifi/ArduinoWifi_Conf.h"
#   ifdef FAF_ARDUINO_MQTT_ENABLE
#       include "FAF/drivers/esp32/arduino/mqtt/ArduinoMQTT_Class.h"
#       include "FAF/drivers/esp32/arduino/mqtt/ArduinoMQTT_Conf.h"
#   endif
#else
#   warning "ESP32 Arduino Drivers only works on ESP32 Arduino Platform! Check build flags."
#endif

#endif // FAF_ESP32_ARDUINO_DRIVERS_ITN_H