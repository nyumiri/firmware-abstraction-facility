#ifndef FAF_TOGGLEABLE_H
#define FAF_TOGGLEABLE_H

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

typedef struct iToggleable_t {
    void (*turn_on)(FAF_Driver* self);
    void (*turn_off)(FAF_Driver* self);
} IToggleable;

#ifdef __cplusplus
}
#endif

#endif // FAF_TOGGLEABLE_H