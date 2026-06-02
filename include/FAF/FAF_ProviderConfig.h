#ifndef FAF_PROVIDERCONFIG_H
#define FAF_PROVIDERCONFIG_H

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

#endif // FAF_PROVIDERCONFIG_H