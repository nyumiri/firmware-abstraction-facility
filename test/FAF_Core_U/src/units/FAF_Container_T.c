#include <units/FAF_Container_T.h>

#include <Mock_Conf.h>
#include <devices/mock/FAF_MockDevice_API.h>
#include <devices/mock/FAF_MockDevice_Class.h>

#include <FAF_Core/FAF_Container.h>

#include <unity.h>
#include <unistd.h>
#include <sys/wait.h>

FAF_Device* device;

FAF_Device corrupted_vtable = {
    .m_ID = FAF_DEVICE_TYPE(FAF_MockDevice)
};

FAF_Device corrupted_type = {
    .m_ID = NULL,
    .m_ops = (const FAF_Device_Ops*) FAF_DEVICE_OPS_GET(FAF_MockDevice)
};

const FAF_Device_Imut imut = {
    .m_ID = NULL
};

FAF_Device corrupted_imut = {
    .m_ID = FAF_DEVICE_TYPE(FAF_MockDevice),
    .m_ops = (const FAF_Device_Ops*) FAF_DEVICE_OPS_GET(FAF_MockDevice),
    .m_imut = &imut
};

FAF_Device* list[] = {&corrupted_vtable, &corrupted_type, &corrupted_imut};

const FAF_Repository repo_c = {
    .devices = list,
    .size = 3
};

const FAF_Repository repo_ln = {
    .devices = NULL,
    .size = 50
};

const FAF_Repository repo_szn = {
    .devices = list,
    .size = 0
};

FAF_Iterator itMock;

static void it_callback(FAF_Device* dev) {
    printf("DEV %p -> OPS -%p- IMUT -%p- ID -%p-\n", (void*) dev,(void*) dev->m_ops, (void*) dev->m_imut, (void*) dev->m_ID);
}

void FAF_Container_Empty_T(void) {
    TEST_MESSAGE("First Step: NULL Repository Access");
    FAF_Container_Set(NULL);
    TEST_ASSERT(FAF_Container_Get(0, FAF_DEVICE_TYPE(FAF_MockDevice), NULL) == FAF_REPOSITORY_INVALID);

    pid_t panic = fork();
    if (panic < 0) TEST_FAIL_MESSAGE("Error on fork");

    if (panic == 0) {
        FAF_Container_Get(0, FAF_DEVICE_TYPE(FAF_MockDevice), &device);
        _exit(0);
    } else {
        int status;
        waitpid(panic, &status, 0);
        if (!WIFSIGNALED(status)) TEST_FAIL_MESSAGE("Program Exit (Success)");

        TEST_MESSAGE("Trigged FAF_Panic()");
    }
}

void FAF_Container_Valid_T(void) {
    TEST_MESSAGE("First Step: Repository Valid");
    FAF_Container_Set(FAF_REPOSITORY_GET(mock));
    
    TEST_ASSERT(FAF_Container_Get(0, FAF_DEVICE_TYPE(FAF_MockDevice), &device) == FAF_REPOSITORY_SUCCESS);
    TEST_ASSERT_NOT_NULL(device);

    TEST_ASSERT(FAF_Container_Get(99, FAF_DEVICE_TYPE(FAF_MockDevice), &device) == FAF_REPOSITORY_NO_FOUND);
    TEST_ASSERT_NULL(device);

    TEST_ASSERT(FAF_Container_Get(10, FAF_DEVICE_TYPE(FAF_MockDevice), &device) == FAF_REPOSITORY_SUCCESS);
    TEST_ASSERT_NOT_NULL(device);

    TEST_ASSERT(FAF_Container_Get(0, FAF_DEVICE_ANY_TYPE, &device) == FAF_REPOSITORY_NO_FOUND);
    TEST_ASSERT_NULL(device);
}

void FAF_Container_Devices_T(void) {
    TEST_MESSAGE("Second Step: Repository Corrupted Devices");
    FAF_Container_Set(&repo_c);

    pid_t panic = fork();
    if (panic < 0) TEST_FAIL_MESSAGE("Error on fork");

    if (panic == 0) {
        FAF_Container_Get(0, FAF_DEVICE_TYPE(FAF_MockDevice), &device);
        _exit(0);
    } else {
        int status;
        waitpid(panic, &status, 0);
        if (!WIFSIGNALED(status)) TEST_FAIL_MESSAGE("Program Exit (Success)");
    }

    TEST_MESSAGE("Trigged FAF_Panic() -> Typed but Vtable Invalid");

    panic = fork();
    if (panic < 0) TEST_FAIL_MESSAGE("Error on fork");

    if (panic == 0) {
        FAF_Container_Get(1, FAF_DEVICE_TYPE(FAF_MockDevice), &device);
        _exit(0);
    } else {
        int status;
        waitpid(panic, &status, 0);
        if (!WIFSIGNALED(status)) TEST_FAIL_MESSAGE("Program Exit (Success)");
    }

    TEST_MESSAGE("Trigged FAF_Panic() -> Vtable Okay but Type Info Corrupted");

    panic = fork();
    if (panic < 0) TEST_FAIL_MESSAGE("Error on fork");

    if (panic == 0) {
        FAF_Container_Get(2, FAF_DEVICE_TYPE(FAF_MockDevice), &device);
        _exit(0);
    } else {
        int status;
        waitpid(panic, &status, 0);
        if (!WIFSIGNALED(status)) TEST_FAIL_MESSAGE("Program Exit (Success)");
    }

    TEST_MESSAGE("Trigged FAF_Panic() -> Device Is 'OKAY' but Config is Corrupted");
}

void FAF_Container_Corrupt_T(void) {
    TEST_MESSAGE("Third Step: Repository Corrupted Struct");
    FAF_Container_Set(&repo_ln);

    pid_t panic = fork();
    if (panic < 0) TEST_FAIL_MESSAGE("Error on fork");

    if (panic == 0) {
        FAF_Container_Get(2, FAF_DEVICE_TYPE(FAF_MockDevice), &device);
        _exit(0);
    } else {
        int status;
        waitpid(panic, &status, 0);
        if (!WIFSIGNALED(status)) TEST_FAIL_MESSAGE("Program Exit (Success)");
    }

    TEST_MESSAGE("Trigged FAF_Panic() -> Repository Data NULL");

    FAF_Container_Set(&repo_szn);

    panic = fork();
    if (panic < 0) TEST_FAIL_MESSAGE("Error on fork");

    if (panic == 0) {
        FAF_Container_Get(2, FAF_DEVICE_TYPE(FAF_MockDevice), &device);
        _exit(0);
    } else {
        int status;
        waitpid(panic, &status, 0);
        if (!WIFSIGNALED(status)) TEST_FAIL_MESSAGE("Program Exit (Success)");
    }

    TEST_MESSAGE("Trigged FAF_Panic() -> Repository Data Size is 0");
}

void FAF_Container_Iterator_NULL_T(void) {
    TEST_MESSAGE("First Step: Iterator Factory (INVALID)");

    FAF_Container_Set(NULL);
    TEST_ASSERT(FAF_Container_Iterator_Create(NULL) == FAF_REPOSITORY_INVALID);

    pid_t panic = fork();

    if (panic < 0) TEST_FAIL_MESSAGE("Error on fork");

    if (panic == 0) {
        FAF_Container_Iterator_Create(&itMock);
        _exit(0);
    } else {
        int status;
        waitpid(panic, &status, 0);
        if (!WIFSIGNALED(status)) TEST_FAIL_MESSAGE("Program Exit (Success)");
    }

    TEST_MESSAGE("Trigged FAF_Panic() -> Attempt on Creating a Iterator of NULL");
}

void FAF_Container_Iterator_Corrupt_T(void) {
    TEST_MESSAGE("Second Step: Iterator Factory (Corrupted)");

    FAF_Container_Set(&repo_c);

    pid_t panic = fork();

    if (panic < 0) TEST_FAIL_MESSAGE("Error on fork");

    if (panic == 0) {
        FAF_Container_Iterator_Create(&itMock);
        _exit(0);
    } else {
        int status;
        waitpid(panic, &status, 0);
        if (!WIFSIGNALED(status)) TEST_FAIL_MESSAGE("Program Exit (Success)");
    }

    TEST_MESSAGE("Trigged FAF_Panic() -> Attempt on Creating a Iterator of Repository with Corrupted Devices");
}

void FAF_Container_Iterator_Corrupted_Repo_T(void) {
    TEST_MESSAGE("Third Step: Iterator Factory (Data NULL)");

    FAF_Container_Set(&repo_ln);

    pid_t panic = fork();

    if (panic < 0) TEST_FAIL_MESSAGE("Error on fork");

    if (panic == 0) {
        FAF_Container_Iterator_Create(&itMock);
        _exit(0);
    } else {
        int status;
        waitpid(panic, &status, 0);
        if (!WIFSIGNALED(status)) TEST_FAIL_MESSAGE("Program Exit (Success)");
    }

    TEST_MESSAGE("Trigged FAF_Panic() -> Attempt on Creating a Iterator of Repository with NULL Array");

    FAF_Container_Set(&repo_szn);

    panic = fork();

    if (panic < 0) TEST_FAIL_MESSAGE("Error on fork");

    if (panic == 0) {
        FAF_Container_Iterator_Create(&itMock);
        _exit(0);
    } else {
        int status;
        waitpid(panic, &status, 0);
        if (!WIFSIGNALED(status)) TEST_FAIL_MESSAGE("Program Exit (Success)");
    }

    TEST_MESSAGE("Trigged FAF_Panic() -> Attempt on Creating a Iterator of Repository with Size 0");
}

void FAF_Container_Foreach_Valid_T(void) {
    TEST_MESSAGE("First Step: Foreach (VALID)");

    FAF_Container_Set(FAF_REPOSITORY_GET(mock));
    
    TEST_ASSERT(FAF_Container_Iterator_Create(&itMock) == FAF_REPOSITORY_SUCCESS);
    TEST_ASSERT(FAF_Container_Iterator_Status(&itMock));

    FAF_Container_Foreach(&itMock, FAF_DEVICE_ANY_TYPE, it_callback);

    TEST_PASS_MESSAGE("Iterator Valided");
}

void FAF_Container_Foreach_Corrupt_T(void) {
    TEST_MESSAGE("Second Step: Foreach (NULL DATA)");

    FAF_Container_Set(FAF_REPOSITORY_GET(mock));
    FAF_Container_Iterator_Create(&itMock);

    itMock.m_data = NULL;

    pid_t panic = fork();

    if (panic < 0) TEST_FAIL_MESSAGE("Error on fork");

    if (panic == 0) {
        FAF_Container_Foreach(&itMock, FAF_DEVICE_ANY_TYPE, it_callback);
        _exit(0);
    } else {
        int status;
        waitpid(panic, &status, 0);
        if (!WIFSIGNALED(status)) TEST_FAIL_MESSAGE("Program Exit (Success)");
    }

    TEST_MESSAGE("Trigged FAF_Panic() -> Iterator Array is NULL");

    TEST_MESSAGE("Second Step: Foreach (NULL SIZE)");
    FAF_Container_Iterator_Create(&itMock);

    itMock.m_size = 0;

    panic = fork();

    if (panic < 0) TEST_FAIL_MESSAGE("Error on fork");

    if (panic == 0) {
        FAF_Container_Foreach(&itMock, FAF_DEVICE_ANY_TYPE, it_callback);
        _exit(0);
    } else {
        int status;
        waitpid(panic, &status, 0);
        if (!WIFSIGNALED(status)) TEST_FAIL_MESSAGE("Program Exit (Success)");
    }

    TEST_MESSAGE("Trigged FAF_Panic() -> Iterator Array Size is 0");

    TEST_MESSAGE("Third Step: Foreach (Signature Invalid)");
    FAF_Container_Iterator_Create(&itMock);

    itMock.m_Magic = 0xFFFFFF;

    panic = fork();

    if (panic < 0) TEST_FAIL_MESSAGE("Error on fork");

    if (panic == 0) {
        FAF_Container_Foreach(&itMock, FAF_DEVICE_ANY_TYPE, it_callback);
        _exit(0);
    } else {
        int status;
        waitpid(panic, &status, 0);
        if (!WIFSIGNALED(status)) TEST_FAIL_MESSAGE("Program Exit (Success)");
    }

    TEST_MESSAGE("Trigged FAF_Panic() -> Signature Invalid");
}