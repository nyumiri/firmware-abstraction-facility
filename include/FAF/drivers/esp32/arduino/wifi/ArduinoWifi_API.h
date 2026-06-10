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

typedef struct arduino_wifi_vtable_t {
    FAF_Driver_VTable v_parent;

    void (*v_Connect)(FAF_Driver* self, int* out);
    void (*v_Disconnect)(FAF_Driver* self, int* out);

    void (*v_Status)(FAF_Driver* self, int* out);

    void (*v_MacAddress)(FAF_Driver* self, char* buf, uint32_t max_len);
} ArduinoWifi_VTable;

void ArduinoWifi_Constructor(FAF_Driver* self);

#ifdef __cplusplus
}
#endif

#endif // FAF_ESP32_ARDUINO_WIFI_API_H