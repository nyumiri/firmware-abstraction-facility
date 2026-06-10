#include "FAF/FAF_Provider.h"
#include "FAF_Provider_Itn.h"

struct FAF_Provider_t {
    FAF_ProviderConfig* config;
};

static FAF_Provider provider = {0};

void FAF_Provider_Provide(FAF_ProviderConfig* config) {
    FAF_Provider* self = &provider;
    self->config = config;
}

void FAF_Provider_Init() {
    FAF_Provider* self = &provider;
    if (!self->config) return;

    FAF_ProviderConfig* props = self->config;
    if (!props->count || !props->devices) return;

    for (size_t i = 0; i < props->count; i++) {
        FAF_DriverDescriptor* driverProps = &props->devices[i];
        if (!driverProps->constructor || !driverProps->driver) continue;

        driverProps->constructor(driverProps->driver);
    }
}

size_t FAF_Provider_Size() {
    FAF_Provider* self = &provider;

    FAF_ProviderConfig* config = self->config;
    if (!config) return 0;

    return config->count;
}

FAF_Driver* FAF_Provider_GetDevice(size_t index, uint32_t type_signature) {
    FAF_Provider* self = &provider;

    FAF_ProviderConfig* config = self->config;
    if (!config) return NULL;

    FAF_DriverDescriptor* devices = config->devices;
    if (!devices) return NULL;

    if (index >= FAF_Provider_Size()) return NULL;
    
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

    if (index >= FAF_Provider_Size()) return NULL;
    
    FAF_Driver* device = devices[index].driver;
    if (!device) return NULL;
    
    return device;
}