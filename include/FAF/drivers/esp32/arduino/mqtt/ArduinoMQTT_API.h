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

void ArduinoMQTT_Constructor(FAF_Driver* self);

int ArduinoMQTT_Class_Connect(FAF_Driver* self);
int ArduinoMQTT_Class_Disconnect(FAF_Driver* self);
int ArduinoMQTT_Class_Publish(FAF_Driver* self, const char* topic, const char* payload);
int ArduinoMQTT_Class_Subscribe(FAF_Driver* self, const char* topic);
void ArduinoMQTT_Class_Listen(FAF_Driver* self);

int ArduinoMQTT_Class_Message_IsReady(FAF_Driver* self);
void ArduinoMQTT_Class_Message_Read(FAF_Driver* self, FAF_MQTT_Packet* out);
void ArduinoMQTT_Class_Message_Flush(FAF_Driver* self);

#ifdef __cplusplus
}
#endif

#endif // FAF_ESP32_ARDUINO_MQTT_API_H