#ifndef FAF_MQTT_PACKET_H
#define FAF_MQTT_PACKET_H

/*
 * Firmware Abstraction Facility
 * Copyright (C) 2026 Alice aka Nyumi.
 *
 * Released under the MIT License.
 * See LICENSE file or <https://opensource.org/licenses/MIT> for details.
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct FAF_Mqtt_Packet_t {
    const char* topic;
    char payload[512];
} FAF_MQTT_Packet;

#ifdef __cplusplus
}
#endif

#endif // FAF_MQTT_PACKET_H