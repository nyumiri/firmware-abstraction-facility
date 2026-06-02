#ifndef FAF_PROVIDER_H
#define FAF_PROVIDER_H

#include "FAF/FAF_ProviderConfig.h"

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

void FAF_ProviderInit(FAF_ProviderConfig* config);
size_t FAF_ProviderSize();
FAF_Driver* FAF_ProviderGetDevice(size_t index, uint32_t type_signature);

#ifdef __cplusplus
}
#endif

#endif // FAF_PROVIDER_H