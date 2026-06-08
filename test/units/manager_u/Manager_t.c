#include "Manager_t.h"

#include <unity.h>

#include <FAF/FAF.h>

#include "Manager_t.h"

#include "../../mock/config/CBoard_Stress.h"
#include "../../mock/drivers/DummyDriver.h"
#include "../../mock/drivers/DummySignature.h"

#include <stdio.h>

int count = 0;

static void mock_iterator_noData(FAF_Driver* driver) {
    printf("Error, Driver?? Address: %p\n", (void*) driver);
}

static void mock_iterator_dummy(FAF_Driver* driver) {
    count++;
    printf("Driver Count: %d\n", count);
    printf("Driver Address: %p\n", (void*) driver);

    FAF_Driver* dmy = FAF_Provider_GetDevice(0, DRIVER_SIGNATURE(DummyDriver));
    TEST_ASSERT_NOT_NULL(dmy);
    int sixsevenIdiot = FAF_DRIVER_CALL(DummyDriver, dummy, dmy);
    
    printf("Driver Speak: %d\n\n", sixsevenIdiot);
    TEST_ASSERT(sixsevenIdiot == 67);
}

void test_manager_noData(void) {
    FAF_Provider_Provide(NULL);
    FAF_Provider_Init();
    FAF_Manager_DriverInit_All();
    FAF_Manager_DriverDispose_All();

    FAF_Manager_DriverIterator(0, 99, mock_iterator_noData, ANY_SIGNATURE);

    TEST_ASSERT_TRUE(1);
}

void teste_manager_dummy(void) {
    FAF_Provider_Provide(GET_PROVIDER_SUPPLY(stress));
    FAF_Provider_Init();
    FAF_Manager_DriverInit_All();
    FAF_Manager_DriverDispose_All();

    FAF_Manager_DriverIterator(0, 99, mock_iterator_dummy, ANY_SIGNATURE);
    count = 0;
    FAF_Manager_DriverIterator(0, 99, mock_iterator_dummy, DRIVER_SIGNATURE(DummyDriver));

    TEST_ASSERT_TRUE(1);
}