#include <stdio.h>
#include <unity.h>

#include "units/provider_u/Provider_t.h"
#include "units/manager_u/Manager_t.h"
#include "units/memory_u/Memory_t.h"

#include "FAF/FAF_Deffs.h"

void setUp(void) {
    // This is run before EACH TEST
}

void tearDown(void) {
    // This is run after EACH TEST
}

int main() {

    uintptr_t addr = (uintptr_t) &_faf_vtable_func_end;
    printf("%ld\n", addr);

    UNITY_BEGIN();
    RUN_TEST(test_provider_null);
    RUN_TEST(test_provider_valid);

    RUN_TEST(test_manager_noData);
    RUN_TEST(teste_manager_dummy);

    RUN_TEST(test_memory_corrupt);
    RUN_TEST(test_memory_malicious_assigned);
    UNITY_END();
    return 0;
}