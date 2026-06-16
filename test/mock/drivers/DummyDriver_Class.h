#ifndef FAF_DUMMY_DRIVER_CLASS_H
#define FAF_DUMMY_DRIVER_CLASS_H

/*
 * Firmware Abstraction Facility
 * Copyright (C) 2026 Alice aka Nyumi.
 *
 * Released under the MIT License.
 * See LICENSE file or <https://opensource.org/licenses/MIT> for details.
 */

#include <FAF/FAF_Driver_Internal.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct dummy_context_t {
    FAF_Driver_Instance i_parent;
    int m_dummy;
} DummyDriver_Instance;

typedef struct dummy_driver_t {
    FAF_Driver c_parent;

    int (*dummy)(FAF_Driver* self);
} DummyDriver_Class;

#ifdef __cplusplus
}
#endif

#endif // FAF_DUMMY_DRIVER_CLASS_H