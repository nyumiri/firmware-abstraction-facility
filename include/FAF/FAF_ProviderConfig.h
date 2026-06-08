#ifndef FAF_PROVIDER_CONFIG_H
#define FAF_PROVIDER_CONFIG_H

/*
 * Firmware Abstraction Facility
 * Copyright (C) 2026 Alice aka Nyumi.
 *
 * Released under the MIT License.
 * See LICENSE file or <https://opensource.org/licenses/MIT> for details.
 */

#include "FAF/FAF_DriverDescriptor.h"

#ifdef __cplusplus
#   include <cstddef>
#else
#   include <stddef.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct FAF_ProviderConfig_t {
    size_t count;
    FAF_DriverDescriptor* devices;
} FAF_ProviderConfig;

#ifdef __cplusplus
}
#endif

#endif // FAF_PROVIDER_CONFIG_H