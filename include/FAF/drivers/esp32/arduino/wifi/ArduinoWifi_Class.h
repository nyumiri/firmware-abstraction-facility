#ifndef FAF_ESP32_ARDUINO_WIFI_CLASS_H
#define FAF_ESP32_ARDUINO_WIFI_CLASS_H

/*
 * Firmware Abstraction Facility
 * Copyright (C) 2026 Alice aka Nyumi.
 *
 * Released under the MIT License.
 * See LICENSE file or <https://opensource.org/licenses/MIT> for details.
 */

#include "FAF/FAF_Driver_Internal.h"

#include "FAF/contracts/FAF_Connectable.h"
#include "FAF/contracts/FAF_Reportable.h"

#ifdef __cplusplus
#   include <cstdint>
extern "C" {
#else
#   include <stdint.h>
#endif

typedef struct arduino_wifi_instance_t {
    FAF_Driver_Instance i_parent;
} ArduinoWifi_Instance;

typedef struct arduino_wifi_class_t {
    FAF_Driver c_parent;
    
    IConnectable c_connectable;
    IReportable c_reportable;
    void (*macAddress)(FAF_Driver* self, char* out, uint32_t max_len);
} ArduinoWifi_Class;

#ifdef __cplusplus
}
#endif

#endif // FAF_ESP32_ARDUINO_WIFI_CLASS_H