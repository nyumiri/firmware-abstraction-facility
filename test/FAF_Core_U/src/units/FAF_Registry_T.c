#include <units/FAF_Registry_T.h>
#include <unity.h>
#include <stdio.h>

#include <FAF_Core/FAF_Registry.h>
#include <FAF_Core/FAF_Container.h>
#include <FAF_Core/FAF_Dispatch.h>

#include <Mock_Conf.h>
#include <devices/mock/FAF_MockDevice_Class.h>

#include <unistd.h>
#include <sys/wait.h>

FAF_Device* mockDev;
int destroyCalled = 0;

static void poison_constructor(FAF_Device* self) { (void)self; }
static void poison_destroy(FAF_Device* self) { (void)self; }

static void FAF_METHOD mock_destroy(FAF_Device* self) {
    (void)self; 
    destroyCalled = 1;
}

static FAF_MockDevice_Ops  __attribute__((section(".faf.vtable_ptr"), used)) poisonOps = {
    .v_parent = {
        .m_ID = FAF_DEVICE_TYPE(FAF_MockDevice),
        .v_constructor = poison_constructor,
        .v_destroy = poison_destroy
    }
};

void FAF_Registry_Init_Valid_T(void) {
    TEST_MESSAGE("First Step: Constructor Pos #2 (VALID)");
    FAF_Container_Set(FAF_REPOSITORY_GET(mock));

    FAF_Registry_Init_Device_Pos(1);
    FAF_Container_Get(1, FAF_DEVICE_TYPE(FAF_MockDevice), &mockDev);

    int number = FAF_CALL_RETURN(FAF_MockDevice, int, speak_num, mockDev);
    printf("\nDevice -%p- Speak: %d\n", (void*) mockDev, number);
    TEST_ASSERT(number == 2);

    TEST_MESSAGE("Second Step: Constructor Iterator (VALID)");
    FAF_Registry_Init_All();

    FAF_Container_Get(7, FAF_DEVICE_TYPE(FAF_MockDevice), &mockDev);
    number = FAF_CALL_RETURN(FAF_MockDevice, int, speak_num, mockDev);

    printf("\nDevice -%p- Speak: %d\n", (void*) mockDev, number);
    TEST_ASSERT(number == 666);
}

void FAF_Registry_Init_Out_Bounds_T(void) {
    TEST_MESSAGE("First Step: Call Constructor out of bounds");

    pid_t panic = fork();
    if (panic < 0) TEST_FAIL_MESSAGE("Error on fork");

    if (panic == 0) {
        FAF_Registry_Init_Device_Pos(20);
        _exit(0);
    } else {
        int status;
        waitpid(panic, &status, 0);
        if (!WIFSIGNALED(status)) TEST_FAIL_MESSAGE("Program Exit (Success)");

        TEST_MESSAGE("Trigged FAF_Panic() -> Init Device Out Of Bounds");
    }
}

void FAF_Registry_Init_Poison_T(void) {
    TEST_MESSAGE("First Step: Call Constructor Poisoned");

    FAF_Container_Set(FAF_REPOSITORY_GET(mock));
    FAF_Container_Get(4, FAF_DEVICE_TYPE(FAF_MockDevice), &mockDev);

    FAF_Device_Ops** bypass = (FAF_Device_Ops**) &mockDev->m_ops;
    *bypass = (FAF_Device_Ops*) &poisonOps;

    pid_t panic = fork();
    if (panic < 0) TEST_FAIL_MESSAGE("Error on fork");

    if (panic == 0) {
        FAF_Registry_Init_All();
        _exit(0);
    } else {
        int status;
        waitpid(panic, &status, 0);
        if (!WIFSIGNALED(status)) TEST_FAIL_MESSAGE("Program Exit (Success)");

        TEST_MESSAGE("Trigged FAF_Panic() -> Atempt on Init Device Poisoned");
    }
}

void FAF_Registry_Init_Type_Mismatch_T(void) {
    TEST_MESSAGE("First Step: Call Constructor on Wrong Device");

    FAF_Container_Set(FAF_REPOSITORY_GET(mock));
    FAF_Container_Get(6, FAF_DEVICE_TYPE(FAF_MockDevice), &mockDev);

    mockDev->m_ID = 0x0;

    pid_t panic = fork();
    if (panic < 0) TEST_FAIL_MESSAGE("Error on fork");

    if (panic == 0) {
        FAF_Registry_Init_Device(mockDev);
        _exit(0);
    } else {
        int status;
        waitpid(panic, &status, 0);
        if (!WIFSIGNALED(status)) TEST_FAIL_MESSAGE("Program Exit (Success)");

        TEST_MESSAGE("Trigged FAF_Panic() -> Atempt on Init Wrong Device Instance");
    }
}

void FAF_Registry_Dispose_Valid_T(void) {
    TEST_MESSAGE("First Step: Destructor Pos #2 (NULL)");
    FAF_Container_Set(FAF_REPOSITORY_GET(mock));

    FAF_Registry_Init_Device_Pos(1);
    FAF_Container_Get(1, FAF_DEVICE_TYPE(FAF_MockDevice), &mockDev);

    FAF_Registry_Dispose_Device_Pos(1);

    TEST_MESSAGE("Second Step: Destructor Pos #2 (VALID)");
    destroyCalled = 0;

    FAF_Device_Ops** bypass = (FAF_Device_Ops**) &mockDev->m_ops;
    void(**func)(FAF_Device*) = (void(**)(FAF_Device*)) &((*bypass)->v_destroy);
    (*func) = mock_destroy;

    FAF_Registry_Dispose_Device_Pos(1);
    TEST_ASSERT(destroyCalled);
}

void FAF_Registry_Dispose_Out_Bounds_T(void) {
    TEST_MESSAGE("First Step: Call Destructor out of bounds");

    pid_t panic = fork();
    if (panic < 0) TEST_FAIL_MESSAGE("Error on fork");

    if (panic == 0) {
        FAF_Registry_Dispose_Device_Pos(20);
        _exit(0);
    } else {
        int status;
        waitpid(panic, &status, 0);
        if (!WIFSIGNALED(status)) TEST_FAIL_MESSAGE("Program Exit (Success)");

        TEST_MESSAGE("Trigged FAF_Panic() -> Dispose Device Out Of Bounds");
    }
}

void FAF_Registry_Dispose_Poison_T(void) {
    TEST_MESSAGE("First Step: Call Destructor Poisoned");

    FAF_Container_Set(FAF_REPOSITORY_GET(mock));
    FAF_Container_Get(4, FAF_DEVICE_TYPE(FAF_MockDevice), &mockDev);

    FAF_Device_Ops** bypass = (FAF_Device_Ops**) &mockDev->m_ops;
    *bypass = (FAF_Device_Ops*) &poisonOps;

    pid_t panic = fork();
    if (panic < 0) TEST_FAIL_MESSAGE("Error on fork");

    if (panic == 0) {
        FAF_Registry_Dispose_All();
        _exit(0);
    } else {
        int status;
        waitpid(panic, &status, 0);
        if (!WIFSIGNALED(status)) TEST_FAIL_MESSAGE("Program Exit (Success)");

        TEST_MESSAGE("Trigged FAF_Panic() -> Atempt on Dispose Device Poisoned");
    }
}

void FAF_Registry_Dispose_Type_Mismatch_T(void) {
    TEST_MESSAGE("First Step: Call Destructor on Wrong Device");

    FAF_Container_Set(FAF_REPOSITORY_GET(mock));
    FAF_Container_Get(9, FAF_DEVICE_TYPE(FAF_MockDevice), &mockDev);

    mockDev->m_ID = 0x0;

    FAF_Device_Ops** bypass = (FAF_Device_Ops**) &mockDev->m_ops;
    void(**func)(FAF_Device*) = (void(**)(FAF_Device*)) &((*bypass)->v_destroy);
    (*func) = mock_destroy;

    pid_t panic = fork();
    if (panic < 0) TEST_FAIL_MESSAGE("Error on fork");

    if (panic == 0) {
        FAF_Registry_Dispose_Device(mockDev);
        _exit(0);
    } else {
        int status;
        waitpid(panic, &status, 0);
        if (!WIFSIGNALED(status)) TEST_FAIL_MESSAGE("Program Exit (Success)");

        TEST_MESSAGE("Trigged FAF_Panic() -> Atempt on Dispose Wrong Device Instance");
    }
}