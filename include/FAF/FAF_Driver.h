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

#define FAF_DRIVER_CALL(class_name, method, ptr, ...) \
    class_name##_Class_##method(ptr, ##__VA_ARGS__)

#ifdef __cplusplus
extern "C" {
#endif

typedef struct faf_driver_instance_t FAF_Driver_Instance;
typedef struct faf_driver_t FAF_Driver;

#ifdef __cplusplus
}
#endif

#endif // FAF_DRIVER_H