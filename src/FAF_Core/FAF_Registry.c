#include "FAF_Core/FAF_Registry.h"
#include "FAF_Container_Internal.h"

#include "FAF/utils/FAF_Def.h"
#include "FAF/utils/FAF_Panic.h"

static inline void FAF_Registry_Assert_Func(void(*op)()) {
    const uintptr_t _ptr = (uintptr_t) op;
    if (!(_ptr >= (uintptr_t) &_faf_vtable_func_start && _ptr < (uintptr_t) &_faf_vtable_func_end)
    ) {
        FAF_Panic_Props err = { .error_code = FAF_INTEGRITY_ERR, .file = __FILE__, .line = __LINE__, .info = "Device Operator corrupted" };
        FAF_Panic(&err);
    }
}

static inline void FAF_Registry_Assert_Type(FAF_Device* const dev, const FAF_Device_Ops* const ops) {
    const uintptr_t typeA = (uintptr_t) dev->m_ID;
    const uintptr_t typeB = (uintptr_t) ops->m_ID;

    if (typeA != typeB) {
        FAF_Panic_Props err = { 
            .error_code = FAF_INTEGRITY_ERR,
            .file = __FILE__,
            .line = __LINE__,
            .info = "Wrong Device Instance Type! Expects a Device Instance Type Equals and Device Class Type as same" 
        };
        FAF_Panic(&err);
    }
}

void FAF_Registry_Init_Device(FAF_Device* dev) {
    void(*const constructor)(FAF_Device*) = dev->m_ops->v_constructor;
    
    FAF_Registry_Assert_Func(constructor);
    FAF_Registry_Assert_Type(dev, dev->m_ops);

    const FAF_SIGNATURE signature = (uintptr_t) (dev->m_ops) ^ (uintptr_t) (dev)->m_ID;
    (dev)->m_signature = signature;
    
    constructor(dev);
}

void FAF_Registry_Init_Device_Pos(size_t index) {
    FAF_Device* dev = NULL;
    FAF_Repository_Status status = FAF_Container_Search(index, &dev);

    if (status != FAF_REPOSITORY_SUCCESS) {
        FAF_Panic_Props err = { .error_code = FAF_OUT_BOUNDS, .file = __FILE__, .line = __LINE__, .info = "Array out of bounds or Invalid device pointer address" };
        FAF_Panic(&err);
    }

    FAF_Registry_Init_Device(dev);
}

void FAF_Registry_Init_All() {
    FAF_Iterator iterator;
    
    if (FAF_Container_Iterator_Create(&iterator) != FAF_REPOSITORY_SUCCESS) {
        FAF_Panic_Props err = { .error_code = FAF_OUT_BOUNDS, .file = __FILE__, .line = __LINE__, .info = "Iterator failed on create |>hardware fault!!<| humanity is over." };
        FAF_Panic(&err);
    }

    FAF_Container_Foreach(&iterator, FAF_DEVICE_ANY_TYPE, FAF_Registry_Init_Device);
}

void FAF_Registry_Dispose_Device(FAF_Device* dev) {
    void(*const destroy)(FAF_Device*) = dev->m_ops->v_destroy;
    if (!destroy) return;

    FAF_Registry_Assert_Func(destroy);
    FAF_Registry_Assert_Type(dev, dev->m_ops);

    destroy(dev);
}

void FAF_Registry_Dispose_Device_Pos(size_t index) {
    FAF_Device* dev = NULL;
    FAF_Repository_Status status = FAF_Container_Search(index, &dev);

    if (status != FAF_REPOSITORY_SUCCESS) {
        FAF_Panic_Props err = { .error_code = FAF_OUT_BOUNDS, .file = __FILE__, .line = __LINE__, .info = "Array out of bounds or Invalid device pointer address" };
        FAF_Panic(&err);
    }

    FAF_Registry_Dispose_Device(dev);
}

void FAF_Registry_Dispose_All() {
    FAF_Iterator iterator;
    
    if (FAF_Container_Iterator_Create(&iterator) != FAF_REPOSITORY_SUCCESS) {
        FAF_Panic_Props err = { .error_code = FAF_OUT_BOUNDS, .file = __FILE__, .line = __LINE__, .info = "Iterator failed on create, dont know why" };
        FAF_Panic(&err);
    }

    FAF_Container_Foreach(&iterator, FAF_DEVICE_ANY_TYPE, FAF_Registry_Dispose_Device);
}

FAF_Device_Status FAF_Registry_Device_Status_Get(const FAF_Device* dev) {
    return dev->m_status;
}

void FAF_Registry_Device_Status_Set(FAF_Device* const dev, FAF_Device_Status status) {
    dev->m_status = status;
}