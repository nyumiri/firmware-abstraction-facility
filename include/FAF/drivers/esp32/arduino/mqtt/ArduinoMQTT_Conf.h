#ifndef FAF_ESP32_ARDUINO_MQTT_CONF_H
#define FAF_ESP32_ARDUINO_MQTT_CONF_H

/*
 * Firmware Abstraction Facility
 * Copyright (C) 2026 Alice aka Nyumi.
 *
 * Released under the MIT License.
 * See LICENSE file or <https://opensource.org/licenses/MIT> for details.
 */

#ifdef __cplusplus
#   include <cstdint>
extern "C" {
#else
#   include <stdint.h>
#endif

typedef struct arduino_mqtt_cfg_t {
    const char* addr;
    const uint16_t port;
} ArduinoMQTT_Config;

#ifdef __cplusplus
}
#endif

#endif // FAF_ESP32_ARDUINO_MQTT_CONF_H