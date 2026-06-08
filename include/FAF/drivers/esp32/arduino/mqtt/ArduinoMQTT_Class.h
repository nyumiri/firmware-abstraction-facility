#ifndef FAF_ESP32_ARDUINO_MQTT_CLASS_H
#define FAF_ESP32_ARDUINO_MQTT_CLASS_H

/*
 * Firmware Abstraction Facility
 * Copyright (C) 2026 Alice aka Nyumi.
 *
 * Released under the MIT License.
 * See LICENSE file or <https://opensource.org/licenses/MIT> for details.
 */

#include "FAF/FAF_Driver_Internal.h"
#include "FAF/contracts/FAF_Connectable.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct arduino_mqtt_internal_t ArduinoMQTT_Internal;

typedef struct arduino_mqtt_instance {
    FAF_Driver_Instance i_parent;
    ArduinoMQTT_Internal* itn_props;

    const char* m_clientID;
    int m_messageBusy;
    void* m_messagePacket;
} ArduinoMQTT_Instance;

typedef struct arduino_mqtt_class_t {
    FAF_Driver c_parent;

    IConnectable c_connectable;
    int (*publish)(FAF_Driver* self, const char* topic, const char* payload);
    int (*subscribe)(FAF_Driver* self, const char* topic);
    void (*listen)(FAF_Driver* self);

} ArduinoMQTT_Class;

#ifdef __cplusplus
}
#endif

#endif // FAF_ESP32_ARDUINO_MQTT_CLASS_H