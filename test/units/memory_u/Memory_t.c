#include "Memory_t.h"

#include <unity.h>
#include <FAF/FAF.h>
#include <stdio.h>

#include "../../mock/config/CBoard_Valid.h"
#include "../../mock/drivers/DummyDriver_API.h"

#include <FAF/FAF_Deffs.h>

FAF_Driver* dummyDriver;

/* Unassigned Malicious Driver */

static void vDummyDriver_Malicious_Func(FAF_Driver* self, int* out) {
    printf("Error: Access Malicious Address\n");
    (*out) = 128;
}

static const DummyDriver_VTable malicious = {
    .v_parent = { .signature = DRIVER_SIGNATURE(DummyDriver) },
    .v_dummy = vDummyDriver_Malicious_Func
};

/* Assigned Malicious Driver */

static DECLARE_METHOD void vaDummyDriver_Malicious_Func(FAF_Driver* self, int* out) {
    printf("Error: Access Malicious Assigned Address\n");
    (*out) = 256;
}

static DECLARE_VTABLE const DummyDriver_VTable a_malicious = {
    .v_parent = { .signature = DRIVER_SIGNATURE(DummyDriver) },
    .v_dummy = vaDummyDriver_Malicious_Func
};

void test_memory_corrupt(void) {
    FAF_Provider_Provide(GET_PROVIDER_SUPPLY(valid));
    FAF_Provider_Init();

    FAF_Manager_DriverInit_Index(0);

    dummyDriver = FAF_Provider_GetDevice(0, DRIVER_SIGNATURE(DummyDriver));
    int var = FAF_CALL_RETURN(DummyDriver, int, dummy, dummyDriver);

    TEST_ASSERT(var == 69);

    dummyDriver->vptr = (FAF_Driver_VTable*) &malicious;
    var = FAF_CALL_RETURN(DummyDriver, int, dummy, dummyDriver);

    TEST_ASSERT_FALSE(var == 128);
}

void test_memory_malicious_assigned(void) {
    FAF_Provider_Provide(GET_PROVIDER_SUPPLY(valid));
    FAF_Provider_Init();

    FAF_Manager_DriverInit_Index(0);

    dummyDriver = FAF_Provider_GetDevice(0, DRIVER_SIGNATURE(DummyDriver));
    
    dummyDriver->vptr = (FAF_Driver_VTable*) &a_malicious;
    int var = FAF_CALL_RETURN(DummyDriver, int, dummy, dummyDriver);

    TEST_ASSERT(var == 256);
}