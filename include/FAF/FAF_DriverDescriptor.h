#ifndef FAF_DRIVERCONFIG_H
#define FAF_DRIVERCONFIG_H

#include "FAF/FAF_Driver.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct FAF_driver_desc_t {
    FAF_Driver* driver;
    const char* name;
    void (*constructor)(FAF_Driver* self);
} FAF_DriverDescriptor;

#ifdef __cplusplus
}
#endif

#endif // FAF_DRIVERCONFIG_H