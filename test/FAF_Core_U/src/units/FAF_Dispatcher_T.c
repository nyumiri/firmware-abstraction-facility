#include <units/FAF_Dispatcher_T.h>

#include <Mock_Conf.h>
#include <devices/mock/FAF_MockDevice_API.h>
#include <devices/mock/FAF_MockDevice_Class.h>

#include <FAF_Core/FAF_Container.h>
#include <FAF_Core/FAF_Registry.h>
#include <FAF_Core/FAF_Dispatch.h>

#include <unity.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

FAF_Device* mockDevice;

void poisoned_method(FAF_Device* self, int* out) { printf("DEV -%p- OUT -%p- POISON!!", (void*) self, (void*) out); }

void FAF_Dispatcher_Valid_T(void) {
    TEST_MESSAGE("First Step: Valid OP");

    FAF_Container_Set(FAF_REPOSITORY_GET(mock));
    FAF_Registry_Init_Device_Pos(3);

    FAF_Container_Get(3, FAF_DEVICE_TYPE(FAF_MockDevice), &mockDevice);
    int number = FAF_CALL_RETURN(FAF_MockDevice, int, speak_num, mockDevice);

    printf("DEV -%p- ID -%p- SIGNATURE -%lx- OPS -%p- RESULT -%d-\n", 
        (void*) mockDevice, 
        (void*) mockDevice->m_ID, 
        mockDevice->m_signature, 
        (void*) mockDevice->m_ops, 
        number
    );

    TEST_ASSERT(number == 67);
}

void FAF_Dispatcher_NULL_T(void) {
    TEST_MESSAGE("First Step: Valid OP -> Device NULL");

    pid_t panic = fork();
    if (panic < 0) TEST_FAIL_MESSAGE("Error on fork");

    if (panic == 0) {
        FAF_CALL_RETURN(FAF_MockDevice, int, speak_num, (FAF_Device*) NULL);
        _exit(0);
    } else {
        int status;
        waitpid(panic, &status, 0);
        if (!WIFSIGNALED(status)) TEST_FAIL_MESSAGE("Program Exit (Success)");

        TEST_MESSAGE("Trigged FAF_Panic() -> Dispatcher Invoked passing NULL Device");
    }
}

void FAF_Dispatcher_Poisoned_T(void) {
    TEST_MESSAGE("First Step: Poisoned OP -> Device Valid");

    FAF_Container_Set(FAF_REPOSITORY_GET(mock));
    FAF_Registry_Init_Device_Pos(3);

    FAF_Container_Get(3, FAF_DEVICE_TYPE(FAF_MockDevice), &mockDevice);

    pid_t panic = fork();
    if (panic < 0) TEST_FAIL_MESSAGE("Error on fork");

    if (panic == 0) {
        FAF_MockDevice_Ops** bypass = (FAF_MockDevice_Ops**) &mockDevice->m_ops;
        void(**func)(FAF_Device*, int*) = (void(**)(FAF_Device*, int*)) &((*bypass)->v_speak_num);
        (*func) = poisoned_method;

        FAF_CALL_RETURN(FAF_MockDevice, int, speak_num, mockDevice);
        _exit(0);
    } else {
        int status;
        waitpid(panic, &status, 0);
        if (!WIFSIGNALED(status)) TEST_FAIL_MESSAGE("Program Exit (Success)");

        TEST_MESSAGE("Trigged FAF_Panic() -> Dispatcher Invoked but OP is Poisoned");
    }

    TEST_MESSAGE("Second Step: Valid OP -> Device Signature Poisoned");

    FAF_Registry_Init_Device_Pos(5);
    FAF_Container_Get(5, FAF_DEVICE_TYPE(FAF_MockDevice), &mockDevice);

    panic = fork();
    if (panic < 0) TEST_FAIL_MESSAGE("Error on fork");

    if (panic == 0) {
        mockDevice->m_signature = 0;
        FAF_CALL_RETURN(FAF_MockDevice, int, speak_num, mockDevice);
        _exit(0);
    } else {
        int status;
        waitpid(panic, &status, 0);
        if (!WIFSIGNALED(status)) TEST_FAIL_MESSAGE("Program Exit (Success)");

        TEST_MESSAGE("Trigged FAF_Panic() -> Dispatcher Invoked but Device Signature is Poisoned");
    }
}