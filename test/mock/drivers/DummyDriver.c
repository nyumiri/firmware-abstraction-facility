#include "DummyDriver.h"

/* Internal Methods */

void idummy_init(FAF_Driver* self) {
    if (!self || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(DummyDriver))) return;

    FAF_Driver_Instance* instance = (self->context);
    if (!instance || !VALIDATE_DRIVER_SIGNATURE(instance, DRIVER_SIGNATURE(DummyDriver))) return;

    DummyDriver_Instance* context = (DummyDriver_Instance*) instance;
    context->m_dummy = 67;
}

/* Public Methods */

void DummyDriver_Constructor(FAF_Driver* self) {
    if (!self) return;

    self->signature = DRIVER_SIGNATURE(DummyDriver);
    self->init = idummy_init;
}

int DummyDriver_dummy(FAF_Driver* self) {
    if (!self || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(DummyDriver))) return -1;
    
    FAF_Driver_Instance* instance = (self->context);
    if (!instance || !VALIDATE_DRIVER_SIGNATURE(instance, DRIVER_SIGNATURE(DummyDriver))) return -1;

    DummyDriver_Instance* context = (DummyDriver_Instance*) instance;
    return context->m_dummy;
}