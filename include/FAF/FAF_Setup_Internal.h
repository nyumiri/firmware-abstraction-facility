#ifndef FAF_SETUP_ITN_H
#define FAF_SETUP_INT_H

#include "FAF/FAF_Driver.h"

#define ASSERT_SIGNATURE_EXISTS(TYPE)                                                                           \
    _Static_assert((sizeof(TYPE##_SIGNATURE) > 0), "Driver [" #TYPE "] precisa de assinatura definida");        \
    _Static_assert((TYPE##_SIGNATURE != 0), "Assinatura de driver [" #TYPE "] precisa ser diferente de zero");  \

#define DRIVER_LIST_INIT(list_name, ...)                \
    struct list_name##_ty {                             \
        __VA_ARGS__                                     \
    }; struct list_name##_ty devices_##list_name = {

#define DRIVER_DECLARE_MEMBER(className, var)   \
    ASSERT_SIGNATURE_EXISTS(className##_Class)  \
    className##_Class c_##className##_##var;    \
    className##_Instance i_##className##_##var;

#define DRIVER_LIST_END };

#define DRIVER_LIST_APPEND(list_name, className, var, cfg)                                  \
    .c_##className##_##var = {                                                              \
        .base = {                                                                           \
            .context = (FAF_Driver_Instance*) &(devices_##list_name.i_##className##_##var)  \
        }                                                                                   \
    },                                                                                      \
    .i_##className##_##var = {                                                              \
        .instance = {                                                                       \
            .signature = className##_Class_SIGNATURE,                                       \
            .config = ((cfg) == NULL) ? NULL : (cfg)                                        \
        }                                                                                   \
    }

#define PROVIDER_SUPPLY_CREATE(list_name, ...)                                                  \
    static FAF_DriverDescriptor a_##list_name##_descriptors[] = {                               \
        __VA_ARGS__                                                                             \
    };                                                                                          \
    FAF_ProviderConfig provider_##list_name##_data = {                                          \
        .count = sizeof(a_##list_name##_descriptors) / sizeof(a_##list_name##_descriptors[0]),  \
        .devices = (a_##list_name##_descriptors)                                                \
    };

#define PROVIDER_SUPPLY_APPEND(list_name, className, var, nameStr)              \
    {                                                                           \
        .driver = (FAF_Driver*) &(devices_##list_name.c_##className##_##var),   \
        .name = nameStr,                                                        \
        .constructor = className##_Constructor                                  \
    }

#endif // FAF_SETUP_INT_H