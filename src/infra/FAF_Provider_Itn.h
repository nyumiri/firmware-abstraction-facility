#ifndef FAF_PROVIDER_ITN_H
#define FAF_PROVIDER_ITN_H

#include "FAF/FAF_Driver.h"

#ifdef __cplusplus
#   include <cstddef>
#else
#   include <stddef.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

FAF_Driver* FAF_Provider_GetDevice_Internal(size_t index);

#ifdef __cplusplus
}
#endif

#endif // FAF_PROVIDER_ITN_H