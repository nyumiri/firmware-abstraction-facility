#ifndef FAF_DEFFS_H
#define FAF_DEFFS_H

/*
 * Firmware Abstraction Facility
 * Copyright (C) 2026 Alice aka Nyumi.
 *
 * Released under the MIT License.
 * See LICENSE file or <https://opensource.org/licenses/MIT> for details.
 */

#define DECLARE_VTABLE __attribute__((section(".faf.vtable_ptr"), used))
#define DECLARE_METHOD __attribute__((section(".faf.vtable_func"), used))

#ifdef __cplusplus
#   include <cstdint>
extern "C" {
#else
#   include <stdint.h>
#endif

extern const uint8_t _faf_vtable_ptr_start, _faf_vtable_ptr_end;
extern const uint8_t _faf_vtable_func_start, _faf_vtable_func_end;

#ifdef __cplusplus
}
#endif

#endif // FAF_DEFFS_H