#include "FAF/FAF_Manager.h"
#include "FAF/FAF_Provider.h"
#include "FAF/FAF_Dispatch.h"
#include "FAF_Provider_Itn.h"

#define INIT 0
#define DISPOSE 1

static inline int FAF_Driver_VTable_AssertMemory(const FAF_Driver_VTable* vptr) {
    if (!vptr) return 0;

    const uintptr_t vt = (uintptr_t) vptr;
    return (vt >= (uintptr_t) &_faf_vtable_ptr_start && vt < (uintptr_t) &_faf_vtable_ptr_end);
}

static inline int FAF_Driver_Func_AssertMemory(void (*const v_func)(FAF_Driver* self)) {
    if (!v_func) return 0;

    const uintptr_t func = (uintptr_t) v_func;
    return (func >= (uintptr_t) &_faf_vtable_func_start && func < (uintptr_t) &_faf_vtable_func_end);
}

static void FAF_Driver_Lifecycle_Execute(FAF_Driver* driver, int isDispose) {
    if (!driver) return;

    const FAF_Driver_VTable* vtable = driver->vptr;
    void (*const func)(FAF_Driver* self) = (isDispose) ? vtable->v_dispose : vtable->v_init;

    if (
        FAF_Driver_VTable_AssertMemory(vtable) &&
        FAF_Driver_Func_AssertMemory(func) &&
        (driver->signature == vtable->signature)
    ) func(driver);
}

void FAF_Manager_DriverInit(FAF_Driver* driver) { FAF_Driver_Lifecycle_Execute(driver, INIT); }

void FAF_Manager_DriverInit_Index(size_t i) {
    FAF_Driver* driver = FAF_Provider_GetDevice_Internal(i);    
    FAF_Driver_Lifecycle_Execute(driver, INIT);
}

void FAF_Manager_DriverInit_All() {
    for (size_t i = 0; i < FAF_Provider_Size(); i++) {
        FAF_Driver* driver = FAF_Provider_GetDevice_Internal(i);
        FAF_Driver_Lifecycle_Execute(driver, INIT);
    }
}

void FAF_Manager_DriverDispose(FAF_Driver* driver) { FAF_Driver_Lifecycle_Execute(driver, DISPOSE); }

void FAF_Manager_DriverDispose_Index(size_t i) {
    FAF_Driver* driver = FAF_Provider_GetDevice_Internal(i);
    FAF_Driver_Lifecycle_Execute(driver, DISPOSE);
}

void FAF_Manager_DriverDispose_All() {
    for (size_t i = 0; i < FAF_Provider_Size(); i++) {
        FAF_Driver* driver = FAF_Provider_GetDevice_Internal(i);
        FAF_Driver_Lifecycle_Execute(driver, DISPOSE);
    }
}

void FAF_Manager_DriverIterator(size_t first, size_t count, void (*callback)(FAF_Driver* driver), uint32_t signature) {
    if (!callback) return;

    size_t end = first + count;
    if (end > FAF_Provider_Size()) end = FAF_Provider_Size();

    for (size_t i = first; i < end; i++) {
        FAF_Driver* driver = (signature == ANY_SIGNATURE) ?
            FAF_Provider_GetDevice_Internal(i) :
            FAF_Provider_GetDevice(i, signature);
        
        if (!driver) continue;
        callback(driver);
    }
}