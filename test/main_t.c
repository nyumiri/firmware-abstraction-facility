#include <stdio.h>
#include <unity.h>

#include "units/provider_u/Provider_t.h"
#include "units/manager_u/Manager_t.h"

void setUp(void) {
    // This is run before EACH TEST
}

void tearDown(void) {
    // This is run after EACH TEST
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_provider_null);
    RUN_TEST(test_provider_valid);

    RUN_TEST(test_manager_noData);
    RUN_TEST(teste_manager_dummy);
    UNITY_END();
    return 0;
}