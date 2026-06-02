#include "FAF/FAF_Provider.h"

#include "FAF/FAF_Driver_Internal.h"
#include "FAF_Provider_Itn.h"

struct FAF_Provider_t {
    FAF_ProviderConfig* config;
};

static FAF_Provider provider = {0};

void FAF_ProviderInit(FAF_ProviderConfig* config) {
    if (!config) return;

    FAF_Provider* self = &provider;
    self->config = config;

    FAF_ProviderConfig* props = self->config;
    FAF_DriverDescriptor* devices = props->devices;
    if (!devices || !props->count) return;

    /* FIX: Calculate the actual number of devices on array, i hate dumb users and im dumb */
    size_t realcount = sizeof(*devices) / sizeof(FAF_DriverDescriptor);
    if (props->count > realcount) props->count = realcount;

    for (size_t i = 0; i < config->count; i++) {
        /* FIX: Im a bullshit, i forget to check if the device is valid and if constructor is valid too */
        if (!devices[i].constructor || !devices[i].driver) continue;

        devices[i].constructor(devices[i].driver);
    }
}

size_t FAF_ProviderSize() {
    FAF_Provider* self = &provider;

    FAF_ProviderConfig* config = self->config;
    if (!config) return 0;

    return config->count;
}

FAF_Driver* FAF_ProviderGetDevice(size_t index, uint32_t type_signature) {
    FAF_Provider* self = &provider;

    FAF_ProviderConfig* config = self->config;
    if (!config) return NULL;

    FAF_DriverDescriptor* devices = config->devices;
    if (!devices) return NULL;

    if (index >= FAF_ProviderSize()) return NULL;
    
    FAF_Driver* device = devices[index].driver;
    if (!device || (device->signature != type_signature)) return NULL;
    
    return device;
}

FAF_Driver* FAF_Provider_GetDevice_Internal(size_t index) {
    FAF_Provider* self = &provider;

    FAF_ProviderConfig* config = self->config;
    if (!config) return NULL;

    FAF_DriverDescriptor* devices = config->devices;
    if (!devices) return NULL;

    if (index >= FAF_ProviderSize()) return NULL;
    
    FAF_Driver* device = devices[index].driver;
    if (!device) return NULL;
    
    return device;
}