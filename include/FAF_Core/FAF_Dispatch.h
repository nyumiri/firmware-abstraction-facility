#ifndef FAF_DISPATCH_H
#define FAF_DISPATCH_H

#include "FAF/types/FAF_Device.h"
#include "FAF/utils/FAF_Def.h"
#include "FAF/utils/FAF_Panic.h"

#define __ASSERT_OP_VOID(self)                                                      \
    if (!(self)) {                                                                  \
        FAF_Panic_Props err = { .error_code = FAF_OUT_BOUNDS,                       \
            .file = __FILE__,                                                       \
            .line = __LINE__,                                                       \
            .info = "Operator Contract Violated! Expects -> FAF_Device* valid" };   \
        FAF_Panic(&err);                                                            \
    }

#define __ASSERT_OP_RETURN(self, out)                                                           \
    if (!(self) || ((uintptr_t)(out) == 0)) {                                                   \
        FAF_Panic_Props err = { .error_code = FAF_OUT_BOUNDS,                                   \
            .file = __FILE__,                                                                   \
            .line = __LINE__,                                                                   \
            .info = "Operator Contract Violated! Expects -> FAF_Device* valid & R* valid" };    \
        FAF_Panic(&err);                                                                        \
    }

#define __ASSERT_METHOD(METHOD)                                                                                                         \
    uintptr_t __ptr = (uintptr_t) (METHOD);                                                                                             \
    if(!(__ptr >= (uintptr_t) &_faf_vtable_func_start && __ptr < (uintptr_t) &_faf_vtable_func_end)) {                                  \
        FAF_Panic_Props err = { .error_code = FAF_INTEGRITY_ERR, .file = __FILE__, .line = __LINE__, .info = "Device OP corrupted" };   \
        FAF_Panic(&err);                                                                                                                \
    }

#define __ASSERT_SIGNATURE(T, self)                                         \
    const FAF_SIGNATURE signature = (uintptr_t) (FAF_DEVICE_OPS_GET(T))     \
        ^ (uintptr_t) (self)->m_ID;                                         \
    if ((self)->m_signature != signature) {                                 \
        FAF_Panic_Props err = { .error_code = FAF_INTEGRITY_ERR,            \
            .file = __FILE__,                                               \
            .line = __LINE__,                                               \
            .info = "Wrong Device Type! Expects -> " #T "*" };              \
        FAF_Panic(&err);                                                    \
    }

#define __FAF_CALL(T, METHOD, DEV, ...)                 \
    const T##_Ops* vt = (const T##_Ops*) (DEV)->m_ops;  \
    __ASSERT_METHOD(vt->v_##METHOD)                     \
    vt->v_##METHOD((DEV),##__VA_ARGS__);

#define FAF_CALL_VOID(T, METHOD, DEV, ...) ({       \
    __ASSERT_OP_VOID(DEV)                           \
    __ASSERT_SIGNATURE(T, DEV)                      \
    __FAF_CALL(T, METHOD, DEV,##__VA_ARGS__)        \
})

#define FAF_CALL_RETURN(T, R, METHOD, DEV, ...) ({      \
    R out = {0};                                        \
    __ASSERT_OP_RETURN(DEV, &(out))                     \
    __ASSERT_SIGNATURE(T, DEV)                          \
    __FAF_CALL(T, METHOD, DEV, &(out),##__VA_ARGS__)    \
    out;                                                \
})

#define FAF_UNSAFE_CALL_VOID(T, METHOD, DEV, ...) ({    \
    __ASSERT_OP_VOID(DEV)                               \
    __FAF_CALL(T, METHOD, DEV,##__VA_ARGS__)            \
})

#define FAF_UNSAFE_CALL_RETURN(T, R, METHOD, DEV, ...) ({   \
    R out = {0};                                            \
    __ASSERT_OP_RETURN(DEV, &(out))                         \
    __FAF_CALL(T, METHOD, DEV, &(out),##__VA_ARGS__)        \
    out;                                                    \
})

#endif // FAF_DISPATCH_H