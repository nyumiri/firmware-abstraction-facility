#include "FAF/FAF_Provider.h"

#include "FAF/FAF_Driver_Internal.h"
#include "FAF_Provider_Itn.h"

struct FAF_Provider_t {
    FAF_ProviderConfig* config;
};

static FAF_Provider provider = {0};

/*  
*   I Removed the count "fix" because im getting very trouble 
*   and the responsability is for the user if ther violate the contract ;)
*/

void FAF_ProviderInit(FAF_ProviderConfig* config) {
    if (!config) return;

    FAF_Provider* self = &provider;
    self->config = config;

    FAF_ProviderConfig* props = self->config;
    if (!props->count || !props->devices) return;

    for (size_t i = 0; i < props->count; i++) {
        FAF_DriverDescriptor* driverProps = &props->devices[i];
        if (!driverProps->constructor || !driverProps->driver) continue;

        driverProps->constructor(driverProps->driver);
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