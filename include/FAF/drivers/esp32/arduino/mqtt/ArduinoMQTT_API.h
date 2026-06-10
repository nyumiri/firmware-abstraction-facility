#ifndef FAF_ESP32_ARDUINO_MQTT_API_H
#define FAF_ESP32_ARDUINO_MQTT_API_H

/*
 * Firmware Abstraction Facility
 * Copyright (C) 2026 Alice aka Nyumi.
 *
 * Released under the MIT License.
 * See LICENSE file or <https://opensource.org/licenses/MIT> for details.
 */

#include "FAF/FAF_Driver.h"
#include "FAF/utils/FAF_Mqtt_Packet.h"

#define ArduinoMQTT_Class_SIGNATURE 0x41574D51

#ifdef __cplusplus
extern "C" {
#endif

typedef struct arduino_mqtt_vtable_t {
    FAF_Driver_VTable v_parent;

    void (*v_Connect)(FAF_Driver* self, int* out);
    void (*v_Disconnect)(FAF_Driver* self, int* out);

    void (*v_Publish)(FAF_Driver* self, int* out, const char* topic, const char* payload);
    void (*v_Subscribe)(FAF_Driver* self, int* out, const char* topic);
    void (*v_Listen)(FAF_Driver* self);

    void (*v_Message_IsReady)(FAF_Driver* self, int* out);
    void (*v_Message_Read)(FAF_Driver* self, FAF_MQTT_Packet* buf);
    void (*v_Message_Flush)(FAF_Driver* self);
} ArduinoMQTT_VTable;

void ArduinoMQTT_Constructor(FAF_Driver* self);

#ifdef __cplusplus
}
#endif

#endif // FAF_ESP32_ARDUINO_MQTT_API_H