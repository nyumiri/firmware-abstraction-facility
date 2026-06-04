#ifndef FAF_DRIVER_ITN_H
#define FAF_DRIVER_ITN_H

#include "FAF/FAF_Driver.h"

#define VALIDATE_DRIVER_SIGNATURE(ctx, sig) ((ctx)->signature == (sig))

#ifdef __cplusplus
#   include <cstdint>
#else
#   include <stdint.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct faf_driver_instance_t {
    uint32_t signature;
    const void* config;
};

struct faf_driver_t {
    uint32_t signature;
    FAF_Driver_Instance* context;
    
    void (*init)(FAF_Driver* self);
    void (*dispose)(FAF_Driver* self);
};

#ifdef __cplusplus
}
#endif

#endif // FAF_DRIVER_ITN_H