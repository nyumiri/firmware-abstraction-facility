#include <devices/mock/FAF_MockDevice_API.h>
#include <devices/mock/FAF_MockDevice_Class.h>

#include "FAF/utils/FAF_Panic.h"

FAF_DEVICE_DEFINE(FAF_MockDevice)

/* VTable Methods */

static void FAF_METHOD vMockDevice_Speak_Num(FAF_Device* self, int* out) {
    FAF_MockDevice* device = (FAF_MockDevice*) self;
    (*out) = device->m_number;
}

static void FAF_METHOD vMockDevice_Constructor(FAF_Device* self) {
    FAF_MockDevice* device = (FAF_MockDevice*) self;
    if (!device->m_number) device->m_number = 2;
}

FAF_DEVICE_VTABLE_DEFINE(FAF_MockDevice, 
    .v_parent = { 
        .m_ID = FAF_DEVICE_TYPE(FAF_MockDevice),
        .m_fancy_name = "FAF Mock Device",
        .v_constructor = vMockDevice_Constructor
    },

    .v_speak_num = vMockDevice_Speak_Num
);