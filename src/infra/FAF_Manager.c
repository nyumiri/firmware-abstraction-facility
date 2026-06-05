#include "FAF/FAF_Manager.h"
#include "FAF/FAF_Driver_Internal.h"
#include "FAF/FAF_Provider.h"
#include "FAF_Provider_Itn.h"

void FAF_Manager_DriverInit(FAF_Driver* driver) {
    if (!driver || !driver->init) return;
    driver->init(driver);
}

void FAF_Manager_DriverInit_Index(size_t i) {
    FAF_Driver* driver = FAF_Provider_GetDevice_Internal(i);
    
    if (!driver || !driver->init) return;
    driver->init(driver);
}

void FAF_Manager_DriverInit_All() {
    for (size_t i = 0; i < FAF_Provider_Size(); i++) {
        FAF_Driver* driver = FAF_Provider_GetDevice_Internal(i);
        
        if (!driver || !driver->init) continue;
        driver->init(driver);
    }
}

void FAF_Manager_DriverDispose(FAF_Driver* driver) {
    if (!driver || !driver->dispose) return;
    driver->dispose(driver);
}

void FAF_Manager_DriverDispose_Index(size_t i) {
    FAF_Driver* driver = FAF_Provider_GetDevice_Internal(i);
    
    if (!driver || !driver->dispose) return;
    driver->dispose(driver);
}

void FAF_Manager_DriverDispose_All() {
    for (size_t i = 0; i < FAF_Provider_Size(); i++) {
        FAF_Driver* driver = FAF_Provider_GetDevice_Internal(i);
        
        if (!driver || !driver->dispose) continue;
        driver->dispose(driver);
    }
}

void FAF_Manager_DriverIterator(size_t first, size_t count, void (*callback)(FAF_Driver* driver), uint32_t signature) {
    if (!callback) return;

    size_t end = first + count;
    if (end > FAF_Provider_Size()) end = FAF_Provider_Size();

    for (size_t i = first; i < end; i++) {
        FAF_Driver* driver = (signature == ANY_SIGNATURE) ?
            FAF_Provider_GetDevice_Internal(i) :
            FAF_Provider_GetDevice(i, signature);
        
        if (!driver) continue;
        callback(driver);
    }
}