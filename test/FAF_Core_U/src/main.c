#include <unity.h>
#include <stdio.h>

#include <FAF/utils/FAF_Panic.h>

#include <units/FAF_Container_T.h>
#include <units/FAF_Registry_T.h>
#include <units/FAF_Dispatcher_T.h>

void FAF_Panic_T(const FAF_Panic_Props* ctx) {
    printf("\n[FAF] Error %d, File %s, line %d, Info %s\n\n", 
        ctx->error_code, ctx->file, ctx->line, ctx->info
    );
    fflush(NULL);
}

void setUp(void) {}

void tearDown(void) {}

int main(void) {
    FAF_Panic_Switch(FAF_Panic_T);
    UNITY_BEGIN();

    RUN_TEST(FAF_Container_Empty_T);
    RUN_TEST(FAF_Container_Valid_T);

    RUN_TEST(FAF_Container_Devices_T);
    RUN_TEST(FAF_Container_Corrupt_T);

    RUN_TEST(FAF_Container_Iterator_NULL_T);
    RUN_TEST(FAF_Container_Iterator_Corrupt_T);
    RUN_TEST(FAF_Container_Iterator_Corrupted_Repo_T);

    RUN_TEST(FAF_Container_Foreach_Valid_T);
    RUN_TEST(FAF_Container_Foreach_Corrupt_T);

    RUN_TEST(FAF_Registry_Init_Valid_T);
    RUN_TEST(FAF_Registry_Init_Out_Bounds_T);
    RUN_TEST(FAF_Registry_Init_Poison_T);
    RUN_TEST(FAF_Registry_Init_Type_Mismatch_T);

    RUN_TEST(FAF_Registry_Dispose_Valid_T);
    RUN_TEST(FAF_Registry_Dispose_Out_Bounds_T);
    RUN_TEST(FAF_Registry_Dispose_Poison_T);
    RUN_TEST(FAF_Registry_Dispose_Type_Mismatch_T);

    RUN_TEST(FAF_Dispatcher_Valid_T);
    RUN_TEST(FAF_Dispatcher_NULL_T);
    RUN_TEST(FAF_Dispatcher_Poisoned_T);

    return UNITY_END();
}