#ifndef FAF_REGISTRY_H
#define FAF_REGISTRY_H

#ifdef __cplusplus
#   include <cstddef>
#else
#   include <stddef.h>
#endif

#include "FAF/types/FAF_Device.h"

#ifdef __cplusplus
extern "C" {
#endif

void FAF_Registry_Init_Device(FAF_Device* dev);
void FAF_Registry_Init_Device_Pos(size_t index);
void FAF_Registry_Init_All();

void FAF_Registry_Dispose_Device(FAF_Device* dev);
void FAF_Registry_Dispose_Device_Pos(size_t index);
void FAF_Registry_Dispose_All();

FAF_Device_Status FAF_Registry_Device_Status_Get(const FAF_Device* dev);
void FAF_Registry_Device_Status_Set(FAF_Device* const dev, FAF_Device_Status status);

#ifdef __cplusplus
}
#endif

#endif // FAF_REGISTRY_H