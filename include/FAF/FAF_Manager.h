#ifndef FAF_MANAGER_H
#define FAF_MANAGER_H

#include "FAF/FAF_Driver.h"

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

void FAF_Manager_DriverInit(FAF_Driver* driver);
void FAF_Manager_DriverInit_Index(size_t i);
void FAF_Manager_DriverInit_All();

void FAF_Manager_DriverDispose(FAF_Driver* driver);
void FAF_Manager_DriverDispose_Index(size_t i);
void FAF_Manager_DriverDispose_All();

void FAF_Manager_DriverIterator(size_t first, size_t count, void (*callback)(FAF_Driver* driver), uint32_t signature);

#ifdef __cplusplus
}
#endif

#endif // FAF_MANAGER_H