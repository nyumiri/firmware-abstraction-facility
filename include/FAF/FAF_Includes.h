#ifndef FAF_INCLUDES_H
#define FAF_INCLUDES_H

/*
 * Firmware Abstraction Facility
 * Copyright (C) 2026 Alice aka Nyumi.
 *
 * Released under the MIT License.
 * See LICENSE file or <https://opensource.org/licenses/MIT> for details.
 */

#if defined(__has_include)
#   ifndef FAF_ARDUINO_MQTT_ENABLE
#       if __has_include(<PubSubClient.h>) && defined(ARDUINO_ARCH_ESP32)
#           define FAF_ARDUINO_MQTT_ENABLE 1
#       elif defined(ARDUINO_ARCH_ESP32)
#           warning "FAF: Library >PubSubClient< Not Founded! Arduino MQTT Driver Disabled."
#       endif
#   endif
#endif

#endif // FAF_INCLUDES_H