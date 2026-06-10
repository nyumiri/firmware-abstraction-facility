#ifndef FAF_DRIVER_H
#define FAF_DRIVER_H

/*
 * Firmware Abstraction Facility
 * Copyright (C) 2026 Alice aka Nyumi.
 *
 * Released under the MIT License.
 * See LICENSE file or <https://opensource.org/licenses/MIT> for details.
 */

#define ANY_SIGNATURE 0xFFFFFFFF
#define DRIVER_SIGNATURE(className) className##_Class_SIGNATURE

#define __DRIVER_CALL(T, method, ptr, ...)  \
    const T##_VTable* vt = (T##_VTable*) (ptr)->vptr; \
    vt->v_##method((ptr),##__VA_ARGS__);

#ifdef __cplusplus
#   include <cstdint>
extern "C" {
#else
#   include <stdint.h>
#endif

typedef struct faf_driver_vtable_t {
    uint32_t signature;
} FAF_Driver_VTable;

typedef struct faf_driver_instance_t FAF_Driver_Instance;

typedef struct faf_driver_t FAF_Driver;

struct faf_driver_t {
    uint32_t signature;
    const FAF_Driver_VTable* vptr;
    FAF_Driver_Instance* context;
    
    void (*init)(FAF_Driver* self);
    void (*dispose)(FAF_Driver* self);
};

#ifdef __cplusplus
}
#endif

#endif // FAF_DRIVER_H