#include <unity.h>

#include <FAF/FAF.h>

#include "Provider_t.h"
#include "../../mock/drivers/DummySignature.h"

#define MOCK_DRIVER 0

void test_provider_null(void) {
    FAF_ProviderInit(NULL);
    TEST_ASSERT_TRUE(FAF_ProviderSize() == 0);
    TEST_ASSERT_NULL(FAF_ProviderGetDevice(MOCK_DRIVER, DUMMY_DRIVER_SIGNATURE));
    TEST_ASSERT_NULL(FAF_ProviderGetDevice(0, DUMMY_DRIVER_SIGNATURE));
}

void test_provider_valid(void) {
    FAF_ProviderInit(&providerData);
    TEST_ASSERT_TRUE(FAF_ProviderSize() == 1);
    TEST_ASSERT_NOT_NULL(FAF_ProviderGetDevice(MOCK_DRIVER, DUMMY_DRIVER_SIGNATURE));
    TEST_ASSERT_NULL(FAF_ProviderGetDevice(99, DUMMY_DRIVER_SIGNATURE));
    TEST_ASSERT_NULL(FAF_ProviderGetDevice(MOCK_DRIVER, 0x66554433));
}