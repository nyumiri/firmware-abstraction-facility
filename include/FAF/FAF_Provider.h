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
void FAF_Provider_Provide(FAF_ProviderConfig* config);
void FAF_Provider_Init();
size_t FAF_Provider_Size();
FAF_Driver* FAF_Provider_GetDevice(size_t index, uint32_t type_signature);

#ifdef __cplusplus
}
#endif

#endif // FAF_PROVIDER_H