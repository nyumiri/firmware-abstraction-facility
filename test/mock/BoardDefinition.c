#include <FAF/FAF_BoardDefinition.h>
#include "drivers/DummyDriver.h"

#define MAX_DEVICES 9

struct FAF_Board_Definition_t{
    DummyDriverDevice dummyDevice;
    DummyDriverInstance dummyDeviceInstance;
};

FAF_BoardDefinition devices = {
    .dummyDevice = {
        .base = {
            .context = (FAF_Driver_Instance*) &(devices.dummyDeviceInstance)
        }
    },
    .dummyDeviceInstance = {
        .instance = {
            .signature = DUMMY_DRIVER_SIGNATURE
        },
    }
};

FAF_DriverDescriptor driverDescriptors[1] = {
    {
        .driver = (FAF_Driver*) &(devices.dummyDevice),
        .name = "Dummy Example Driver",
        .constructor = DummyDriver
    }
};

FAF_ProviderConfig providerData = {
    .count = MAX_DEVICES,
    .devices = driverDescriptors
};
