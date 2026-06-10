#include <unity.h>

#include <FAF/FAF.h>

#include "Provider_t.h"

#include "../../mock/config/CBoard_Valid.h"
#include "../../mock/drivers/DummyDriver_API.h"

#define MOCK_DRIVER 0

void test_provider_null(void) {
    FAF_Provider_Provide(NULL);
    FAF_Provider_Init();
    TEST_ASSERT_TRUE(FAF_Provider_Size() == 0);
    TEST_ASSERT_NULL(FAF_Provider_GetDevice(MOCK_DRIVER, DRIVER_SIGNATURE(DummyDriver)));
    TEST_ASSERT_NULL(FAF_Provider_GetDevice(0, DRIVER_SIGNATURE(DummyDriver)));
}

void test_provider_valid(void) {
    FAF_Provider_Provide(GET_PROVIDER_SUPPLY(valid));
    FAF_Provider_Init();
    TEST_ASSERT_TRUE(FAF_Provider_Size() == 1);
    TEST_ASSERT_NOT_NULL(FAF_Provider_GetDevice(MOCK_DRIVER, DRIVER_SIGNATURE(DummyDriver)));
    TEST_ASSERT_NULL(FAF_Provider_GetDevice(99, DRIVER_SIGNATURE(DummyDriver)));
    TEST_ASSERT_NULL(FAF_Provider_GetDevice(-1, DRIVER_SIGNATURE(DummyDriver)));
    TEST_ASSERT_NULL(FAF_Provider_GetDevice(MOCK_DRIVER, 0x66554433));
}