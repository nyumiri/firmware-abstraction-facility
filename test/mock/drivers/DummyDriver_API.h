#ifndef FAF_DUMMY_DRIVER_API_H
#define FAF_DUMMY_DRIVER_API_H

/*
 * Firmware Abstraction Facility
 * Copyright (C) 2026 Alice aka Nyumi.
 *
 * Released under the MIT License.
 * See LICENSE file or <https://opensource.org/licenses/MIT> for details.
 */

#include "FAF/FAF_Driver.h"

#define DummyDriver_Class_SIGNATURE 0x64756D6D

#ifdef __cplusplus
extern "C" {
#endif

typedef struct dummy_driver_vtable_t {
    FAF_Driver_VTable v_parent;

    void (*v_dummy)(FAF_Driver* self, int* out);
} DummyDriver_VTable;

void DummyDriver_Constructor(FAF_Driver* self);

#ifdef __cplusplus
}
#endif

#endif // FAF_DUMMY_DRIVER_API_H