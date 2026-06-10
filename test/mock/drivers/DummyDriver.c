#include "DummyDriver_API.h"
#include "DummyDriver_Class.h"

/* Internal VTable Methods */

static void vDummyDriver_dummy(FAF_Driver* self, int* out) {
    if (!self || !out || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(DummyDriver))) return;

    const FAF_Driver_VTable* vt = self->vptr;
    if (vt->signature != self->signature) return;

    DummyDriver_Class* cls = (DummyDriver_Class*) self;
    if (!cls->dummy) return;

    (*out) = cls->dummy(self);
}

static const DummyDriver_VTable dummy_vtable = {
    .v_parent = { .signature = DRIVER_SIGNATURE(DummyDriver) },
    .v_dummy = vDummyDriver_dummy
};

/* Internal Methods */

static int iDummyDriver_dummy(FAF_Driver* self) {
    if (!self || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(DummyDriver))) return -1;

    FAF_Driver_Instance* instance = (self->context);
    if (!instance || !VALIDATE_DRIVER_SIGNATURE(instance, DRIVER_SIGNATURE(DummyDriver))) return -1;

    DummyDriver_Instance* context = (DummyDriver_Instance*) instance;
    return context->m_dummy;
}

static void iDummyDriver_init(FAF_Driver* self) {
    if (!self || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(DummyDriver))) return;
    DummyDriver_Class* cls = (DummyDriver_Class*) self;

    FAF_Driver_Instance* instance = (self->context);
    if (!instance || !VALIDATE_DRIVER_SIGNATURE(instance, DRIVER_SIGNATURE(DummyDriver))) return;

    DummyDriver_Instance* context = (DummyDriver_Instance*) instance;
    context->m_dummy = 69;

    cls->dummy = iDummyDriver_dummy;
}

/* Public Methods */

void DummyDriver_Constructor(FAF_Driver* self) {
    if (!self) return;

    self->vptr = (const FAF_Driver_VTable*) &dummy_vtable;

    self->signature = DRIVER_SIGNATURE(DummyDriver);
    self->init = iDummyDriver_init;
}