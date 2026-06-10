#ifndef FAF_DISPATCH_H
#define FAF_DISPATCH_H

/*
 * Firmware Abstraction Facility
 * Copyright (C) 2026 Alice aka Nyumi.
 *
 * Released under the MIT License.
 * See LICENSE file or <https://opensource.org/licenses/MIT> for details.
 */

#include "FAF/FAF_Driver.h"

#define FAF_CALL_RETURN(T, R, method, ptr, ...) ({      \
    R out = 0;                                          \
    __DRIVER_CALL(T, method, ptr, &out,##__VA_ARGS__)   \
    out;                                                \
})

#define FAF_CALL_VOID(T, method, ptr, ...) ({           \
    __DRIVER_CALL(T, method, ptr,##__VA_ARGS__)         \
})


#endif // FAF_DISPATCH_H