#ifndef FAF_DRIVER_H
#define FAF_DRIVER_H

/*
 * Firmware Abstraction Facility
 * Copyright (C) 2026 Alice aka Nyumi.
 *
 * Released under the MIT License.
 * See LICENSE file or <https://opensource.org/licenses/MIT> for details.
 */

#include "FAF/FAF_Deffs.h"

#define ANY_SIGNATURE 0xFFFFFFFF
#define DRIVER_SIGNATURE(className) className##_Class_SIGNATURE

#ifdef __cplusplus
#   include <cstdint>
extern "C" {
#else
#   include <stdint.h>
#endif

#define __ASSERT_MEMORY_RANGE(ptr, start, end) \
    ((ptr) >= (start) && (ptr) < (end))

#define __ASSERT_VTABLE(T, ptr, method) ({                                                                                      \
    const T##_VTable* __vtptr = ptr;                                                                                            \
    const uintptr_t __meth = (uintptr_t) __vtptr->v_##method;                                                                   \
    (                                                                                                                           \
        __ASSERT_MEMORY_RANGE((uintptr_t) __vtptr, (uintptr_t) &_faf_vtable_ptr_start, (uintptr_t) &_faf_vtable_ptr_end) &&     \
        __ASSERT_MEMORY_RANGE(__meth, (uintptr_t) &_faf_vtable_func_start, (uintptr_t) &_faf_vtable_func_end) &&                \
        (__vtptr->v_parent.signature == DRIVER_SIGNATURE(T))                                                                    \
    );                                                                                                                          \
})

#define __DRIVER_CALL(T, method, ptr, ...)  \
    const T##_VTable* vt = (T##_VTable*) (ptr)->vptr; \
    if (__ASSERT_VTABLE(T,vt, method)) vt->v_##method((ptr),##__VA_ARGS__);

typedef struct faf_driver_t FAF_Driver;
typedef struct faf_driver_instance_t FAF_Driver_Instance;

typedef struct faf_driver_vtable_t {
    uint32_t signature;

    void (*v_init)(FAF_Driver* self);
    void (*v_dispose)(FAF_Driver* self);
} FAF_Driver_VTable;

struct faf_driver_t {
    uint32_t signature;
    FAF_Driver_Instance* context;

    const FAF_Driver_VTable* vptr;
};

#ifdef __cplusplus
}
#endif

#endif // FAF_DRIVER_H