#ifndef FAF_DEVICE_H
#define FAF_DEVICE_H

#ifdef __cplusplus
#   include <cstdint>
#else
#   include <stdint.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct faf_device_ops_t FAF_Device_Ops;
typedef struct faf_device_imut_t FAF_Device_Imut;
typedef struct faf_device_base_t FAF_Device;

typedef const char* FAF_ID;
typedef uintptr_t FAF_SIGNATURE;

typedef enum faf_device_status {
    FAF_DEVICE_ACTIVED = 0,
    FAF_DEVICE_DISABLED = -1,
    FAF_DEVICE_ERROR = -2
} FAF_Device_Status;

#define FAF_DEVICE_DECLARE(T) \
    extern const char T##_ID;

#define FAF_DEVICE_DEFINE(T) \
    const char T##_ID = 'D';

#define FAF_DEVICE_ANY_TYPE 0x0
#define FAF_DEVICE_TYPE(T) &(T##_ID)

#define FAF_DEVICE_VTABLE_DECLARE(T) \
    extern const T##_Ops __attribute__((section(".faf.vtable_ptr"))) T##_vptr

#define FAF_DEVICE_VTABLE_DEFINE(T, ...)                                            \
    const T##_Ops __attribute__((section(".faf.vtable_ptr"), used)) T##_vptr = {    \
        __VA_ARGS__                                                                 \
    }

#define FAF_DEVICE_OPS_GET(T) &(T##_vptr)

#define FAF_METHOD __attribute__((section(".faf.vtable_func"), used))

struct faf_device_ops_t {
    const FAF_ID m_ID;
    const char* m_fancy_name;

    void (*const v_constructor)(FAF_Device* self);
    void (*const v_destroy)(FAF_Device* self);
};

struct faf_device_imut_t {
    const FAF_ID m_ID;
};

struct faf_device_base_t {
    const FAF_Device_Ops* const m_ops;
    const FAF_Device_Imut* const m_imut;
    
    FAF_ID m_ID;
    FAF_SIGNATURE m_signature;
    FAF_Device_Status m_status;
};

#ifdef __cplusplus
}
#endif

#endif // FAF_DEVICE_H