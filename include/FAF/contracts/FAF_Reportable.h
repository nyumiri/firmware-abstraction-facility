#ifndef FAF_REPORTABLE_H
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

typedef struct iReportable_t {
    int (*status)(FAF_Driver* self);
} IReportable;

#ifdef __cplusplus
}
#endif

#endif // FAF_REPORTABLE_H