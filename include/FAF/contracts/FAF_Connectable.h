#ifndef FAF_CONNECTABLE_H
#define FAF_CONNECTABLE_H

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

typedef struct iConnectable_t {
    int (*connect)(FAF_Driver* self);
    int (*disconnect)(FAF_Driver* self);
} IConnectable;

#ifdef __cplusplus
}
#endif

#endif // FAF_CONNECTABLE_H