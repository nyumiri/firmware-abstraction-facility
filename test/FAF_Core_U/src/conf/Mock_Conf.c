#include <Mock_Conf.h>

#include <devices/mock/FAF_MockDevice_API.h>
#include <devices/mock/FAF_MockDevice_Class.h>

S_DEVICE_TREE_INIT(mock)
    S_DEVICE_DECLARE(FAF_MockDevice, mockA)
    S_DEVICE_DECLARE(FAF_MockDevice, mockB)
    S_DEVICE_DECLARE(FAF_MockDevice, mockC)
    S_DEVICE_DECLARE(FAF_MockDevice, mockD)
    S_DEVICE_DECLARE(FAF_MockDevice, mockE)
    S_DEVICE_DECLARE(FAF_MockDevice, mockF)
    S_DEVICE_DECLARE(FAF_MockDevice, mockG)
    S_DEVICE_DECLARE(FAF_MockDevice, mockH)
    S_DEVICE_DECLARE(FAF_MockDevice, mockI)
    S_DEVICE_DECLARE(FAF_MockDevice, mockJ)
    S_DEVICE_DECLARE(FAF_MockDevice, mockK)
S_DEVICE_TREE_END

S_DEVICE_LIST_INIT(mock)
    S_DEVICE_DEFINE(FAF_MockDevice, mockA, NULL, .m_number = 69),
    S_DEVICE_DEFINE(FAF_MockDevice, mockB, NULL),
    S_DEVICE_DEFINE(FAF_MockDevice, mockC, NULL, .m_number = 64),
    S_DEVICE_DEFINE(FAF_MockDevice, mockD, NULL, .m_number = 67),
    S_DEVICE_DEFINE(FAF_MockDevice, mockE, NULL, .m_number = 50),
    S_DEVICE_DEFINE(FAF_MockDevice, mockF, NULL, .m_number = 23),
    S_DEVICE_DEFINE(FAF_MockDevice, mockG, NULL, .m_number = 665),
    S_DEVICE_DEFINE(FAF_MockDevice, mockH, NULL, .m_number = 666),
    S_DEVICE_DEFINE(FAF_MockDevice, mockI, NULL, .m_number = 999),
    S_DEVICE_DEFINE(FAF_MockDevice, mockJ, NULL, .m_number = 623),
    S_DEVICE_DEFINE(FAF_MockDevice, mockK, NULL, .m_number = 14)
S_DEVICE_LIST_END

S_REPOSITORY_PUBLISH(mock)
    S_REPOSITORY_PUSH(mock, FAF_MockDevice, mockA),
    S_REPOSITORY_PUSH(mock, FAF_MockDevice, mockB),
    S_REPOSITORY_PUSH(mock, FAF_MockDevice, mockC),
    S_REPOSITORY_PUSH(mock, FAF_MockDevice, mockD),
    S_REPOSITORY_PUSH(mock, FAF_MockDevice, mockE),
    S_REPOSITORY_PUSH(mock, FAF_MockDevice, mockF),
    S_REPOSITORY_PUSH(mock, FAF_MockDevice, mockG),
    S_REPOSITORY_PUSH(mock, FAF_MockDevice, mockH),
    S_REPOSITORY_PUSH(mock, FAF_MockDevice, mockI),
    S_REPOSITORY_PUSH(mock, FAF_MockDevice, mockJ),
    S_REPOSITORY_PUSH(mock, FAF_MockDevice, mockK)
S_REPOSITORY_SEAL(mock)