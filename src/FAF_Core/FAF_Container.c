#include "FAF_Core/FAF_Container.h"
#include "FAF_Container_Internal.h"

#include "FAF/utils/FAF_Def.h"
#include "FAF/utils/FAF_Panic.h"

static const FAF_Repository* volatile repo_current = NULL;

static inline int FAF_Container_AssertMemory(const void* ptr, const void* start, const void* end) {
    return (ptr >= start && ptr < end);
}

static inline int FAF_Container_Device_AssertIntegrity(FAF_Device* ptr) {
    const FAF_Device_Ops* ops = ptr->m_ops;

    if (!FAF_Container_AssertMemory(
        ops,
        &_faf_vtable_ptr_start,
        &_faf_vtable_ptr_end

    )) {
        return FAF_REPOSITORY_INVALID;
    }

    if(!(ops->m_ID == ptr->m_ID)) {
        return FAF_REPOSITORY_INVALID;
    }

    if ((ptr->m_imut != NULL) && (ptr->m_imut->m_ID != ptr->m_ID)) {
        return FAF_REPOSITORY_INVALID;
    }

    return FAF_REPOSITORY_SUCCESS;
}

void FAF_Container_Set(const FAF_Repository* repository) { repo_current = repository; }

int FAF_Container_Search(size_t index, FAF_Device** dev) {
    const FAF_Repository* const volatile repository = repo_current;

    if (!repository || !repository->devices || !repository->size) {
        FAF_Panic_Props err = { .error_code = FAF_EMPTY_CONFIG, .file = __FILE__, .line = __LINE__, .info = "Getting device on empty container" };
        FAF_Panic(&err);
    }

    if (index >= repository->size) return FAF_REPOSITORY_INVALID;
    if (!dev) return FAF_REPOSITORY_INVALID;

    FAF_Device* device = repository->devices[index];

    if (FAF_Container_Device_AssertIntegrity(device) != FAF_REPOSITORY_SUCCESS) {
        FAF_Panic_Props err = { .error_code = FAF_INTEGRITY_ERR, .file = __FILE__, .line = __LINE__, .info = "Device corrupted" };
        FAF_Panic(&err);
    }

    (*dev) = device;
    return FAF_REPOSITORY_SUCCESS;
}

int FAF_Container_Get(size_t index, FAF_ID ID, FAF_Device** dev) {
    if (!dev) return FAF_REPOSITORY_INVALID;

    FAF_Device* tmp = NULL;
    FAF_Repository_Status status = FAF_Container_Search(index, &tmp);

    if (status != FAF_REPOSITORY_SUCCESS) {
        (*dev) = NULL;
        return FAF_REPOSITORY_NO_FOUND;
    }

    if (tmp->m_ID != ID) {
        (*dev) = NULL;
        return FAF_REPOSITORY_NO_FOUND;
    }

    (*dev) = tmp;
    return FAF_REPOSITORY_SUCCESS;
}

int FAF_Container_Iterator_Create(FAF_Iterator* it) {
    if (!it) return FAF_REPOSITORY_INVALID;

    const FAF_Repository* const volatile repository = repo_current;

    if (!repository || !repository->devices || !repository->size) {
        FAF_Panic_Props err = { .error_code = FAF_EMPTY_CONFIG, .file = __FILE__, .line = __LINE__, .info = "Getting device on empty container" };
        FAF_Panic(&err);
    }

    FAF_Device** devices = repository->devices;
    size_t size = repository->size;

    FAF_Device* device = NULL;

    for (size_t i = 0; i < size; i++) {
        device = devices[i];
        if (FAF_Container_Device_AssertIntegrity(device) != FAF_REPOSITORY_SUCCESS) {
            FAF_Panic_Props err = { .error_code = FAF_INTEGRITY_ERR, .file = __FILE__, .line = __LINE__, .info = "Repository is corrupted" };
            FAF_Panic(&err);
        }
    }

    it->m_data = devices;
    it->m_size = size;

    const uintptr_t n = (size > 1) ? 
        (uintptr_t) devices ^ (uintptr_t) &(devices[size - 1]) : 
        (uintptr_t) devices ^ (uintptr_t) size;
    
    it->m_Magic = n;
    it->m_initialized = 1;
    
    return FAF_REPOSITORY_SUCCESS;
}

int FAF_Container_Iterator_Status(FAF_Iterator* it) {
    if (!it || !(it->m_initialized)) return 0;
    return 1;
}

void FAF_Container_Foreach(FAF_Iterator* it, FAF_ID type, void(*const callback)(FAF_Device* device)) {
    if (!callback || !it || !(it->m_initialized)) return;

    const FAF_Iterator* const iterator = it;
    
    if (!(iterator->m_data) || !(iterator->m_size)) {
        FAF_Panic_Props err = { .error_code = FAF_OUT_BOUNDS, .file = __FILE__, .line = __LINE__, .info = "Iterator not have any data" };
        FAF_Panic(&err);
    }

    FAF_Device** devices = (FAF_Device**) iterator->m_data;
    size_t size = iterator->m_size;

    const uintptr_t expected = (size > 1) ? 
        (uintptr_t) devices ^ (uintptr_t) &(devices[size - 1]) : 
        (uintptr_t) devices ^ (uintptr_t) size;
    
    if (iterator->m_Magic != expected) {
        FAF_Panic_Props err = { .error_code = FAF_INTEGRITY_ERR, .file = __FILE__, .line = __LINE__, .info = "Iterator data corrupted" };
        FAF_Panic(&err);
    }

    FAF_Device* device = NULL;
    
    for (size_t i = 0; i < size; i++) {
        device = devices[i];
        if (type != FAF_DEVICE_ANY_TYPE && (device->m_ID != type)) continue;
        callback(device);
    }
}