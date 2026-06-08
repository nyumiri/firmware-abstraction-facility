#ifndef FAF_ESP32_ARDUINO_WIFI_CONF_H
#define FAF_ESP32_ARDUINO_WIFI_CONF_H

/*
 * Firmware Abstraction Facility
 * Copyright (C) 2026 Alice aka Nyumi.
 *
 * Released under the MIT License.
 * See LICENSE file or <https://opensource.org/licenses/MIT> for details.
 */

typedef struct arduino_wifi_cfg_t {
    const char* ssid;
    const char* password;
} ArduinoWifi_Config;

#endif // FAF_ESP32_ARDUINO_WIFI_CONF_H