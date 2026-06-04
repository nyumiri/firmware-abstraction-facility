#ifndef FAF_DUMMYDRIVER_H
#define FAF_DUMMYDRIVER_H

#include <FAF/FAF_Driver_Internal.h>
#include "DummySignature.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct dummy_context_t {
    FAF_Driver_Instance instance;
    int m_dummy;
} DummyDriver_Instance;

typedef struct dummy_driver_t {
    FAF_Driver base;

    void (*dummy)(FAF_Driver* self);
} DummyDriver_Class;

void DummyDriver_Constructor(FAF_Driver* self);

int DummyDriver_dummy(FAF_Driver* self);

#ifdef __cplusplus
}
#endif

#endif // FAF_DUMMYDRIVER_H