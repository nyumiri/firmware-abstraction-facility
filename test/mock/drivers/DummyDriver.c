#include "DummyDriver.h"

/* Internal Methods */

void idummy_init(FAF_Driver* self) {
    if (!self || !VALIDATE_DRIVER_SIGNATURE(self, DUMMY_DRIVER_SIGNATURE)) return;

    FAF_Driver_Instance* instance = (self->context);
    if (!instance || !VALIDATE_DRIVER_SIGNATURE(instance, DUMMY_DRIVER_SIGNATURE)) return;

    DummyDriverInstance* context = (DummyDriverInstance*) instance;
    context->m_dummy = 67;
}

/* Public Methods */

void DummyDriver(FAF_Driver* self) {
    if (!self) return;

    self->signature = DUMMY_DRIVER_SIGNATURE;
    self->init = idummy_init;
}

int DummyDriver_dummy(FAF_Driver* self) {
    if (!self || !VALIDATE_DRIVER_SIGNATURE(self, DUMMY_DRIVER_SIGNATURE)) return -1;
    
    FAF_Driver_Instance* instance = (self->context);
    if (!instance || !VALIDATE_DRIVER_SIGNATURE(instance, DUMMY_DRIVER_SIGNATURE)) return -1;

    DummyDriverInstance* context = (DummyDriverInstance*) instance;
    return context->m_dummy;
}