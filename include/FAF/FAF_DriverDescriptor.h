#ifndef FAF_DRIVER_DESCRIPTOR_H
#define FAF_DRIVER_DESCRIPTOR_H

/*
 * Firmware Abstraction Facility
 * Copyright (C) 2026 Alice aka Nyumi.
 *
 * Released under the MIT License.
 * See LICENSE file or <https://opensource.org/licenses/MIT> for details.
 */

#include "FAF/FAF_Driver.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct FAF_driver_desc_t {
    FAF_Driver* driver;
    const char* name;
    void (*constructor)(FAF_Driver* self);
} FAF_DriverDescriptor;

#ifdef __cplusplus
}
#endif

#endif // FAF_DRIVER_DESCRIPTOR_H