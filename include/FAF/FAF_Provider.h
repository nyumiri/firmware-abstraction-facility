#ifndef FAF_PROVIDER_H
#define FAF_PROVIDER_H

/*
 * Firmware Abstraction Facility
 * Copyright (C) 2026 Alice aka Nyumi.
 *
 * Released under the MIT License.
 * See LICENSE file or <https://opensource.org/licenses/MIT> for details.
 */

#include "FAF/FAF_ProviderConfig.h"

#define GET_PROVIDER_SUPPLY(list_name) &(provider_##list_name##_data)

#ifdef __cplusplus
#   include <cstddef>
#   include <cstdint>
#else
#   include <stddef.h>
#   include <stdint.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct FAF_Provider_t FAF_Provider;
void FAF_Provider_Provide(FAF_ProviderConfig* config);
void FAF_Provider_Init();
size_t FAF_Provider_Size();
FAF_Driver* FAF_Provider_GetDevice(size_t index, uint32_t type_signature);

#ifdef __cplusplus
}
#endif

#endif // FAF_PROVIDER_H