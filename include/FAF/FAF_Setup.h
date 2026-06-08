#ifndef FAF_SETUP_H
#define FAF_SETUP_H

/*
 * Firmware Abstraction Facility
 * Copyright (C) 2026 Alice aka Nyumi.
 *
 * Released under the MIT License.
 * See LICENSE file or <https://opensource.org/licenses/MIT> for details.
 */

#include "FAF/FAF_ProviderConfig.h"

#define DECLARE_PROVIDER_SUPPLY(list_name)   \
    extern FAF_ProviderConfig provider_##list_name##_data;

#endif // FAF_SETUP_H