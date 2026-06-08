#ifndef FAF_ESP32_ARDUINO_WIFI_API_H
#define FAF_ESP32_ARDUINO_WIFI_API_H

/*
 * Firmware Abstraction Facility
 * Copyright (C) 2026 Alice aka Nyumi.
 *
 * Released under the MIT License.
 * See LICENSE file or <https://opensource.org/licenses/MIT> for details.
 */

#include "FAF/FAF_Driver.h"

#define ArduinoWifi_Class_SIGNATURE 0x41574946

#ifdef __cplusplus
extern "C" {
#   include <cstdint>
#else
#   include <stdint.h>
#endif

typedef enum wifi_status_e {
    W_IDLE,
    W_SSID_INVALID,
    W_SCAN_COMPLETED,
    W_CONNECTED,
    W_FAILED,
    W_LOST,
    W_DISCONNECTED,
    W_EOF
} WifiStatus;

void ArduinoWifi_Constructor(FAF_Driver* self);

int ArduinoWifi_Class_Connect(FAF_Driver* self);
int ArduinoWifi_Class_Disconnect(FAF_Driver* self);
int ArduinoWifi_Class_Status(FAF_Driver* self);
void ArduinoWifi_Class_MacAddress(FAF_Driver* self, char* out, uint32_t max_len);

#ifdef __cplusplus
}
#endif

#endif // FAF_ESP32_ARDUINO_WIFI_API_H