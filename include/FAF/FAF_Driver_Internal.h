#ifndef FAF_DRIVER_ITN_H
#define FAF_DRIVER_ITN_H

/*
 * Firmware Abstraction Facility
 * Copyright (C) 2026 Alice aka Nyumi.
 *
 * Released under the MIT License.
 * See LICENSE file or <https://opensource.org/licenses/MIT> for details.
 */

#include "FAF/FAF_Driver.h"

#define VALIDATE_DRIVER_SIGNATURE(ctx, sig) ((ctx)->signature == (sig))

#ifdef __cplusplus
#   include <cstdint>
#else
#   include <stdint.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct faf_driver_instance_t {
    uint32_t signature;
    const void* config;
};

#ifdef __cplusplus
}
#endif

#endif // FAF_DRIVER_ITN_H