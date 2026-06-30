#ifndef FAF_MOCK_DEVICE_CLASS
#define FAF_MOCK_DEVICE_CLASS

#include "FAF_MockDevice_API.h"
#include "FAF/utils/FAF_Def.h"

#ifdef __cplusplus
extern "C" {
#endif

FAF_DEVICE_VTABLE_DECLARE(FAF_MockDevice);

struct faf_mockdevice_t {
    FAF_Device c_parent;
    int m_number;
};

#ifdef __cplusplus
}
#endif

#endif // FAF_MOCK_DEVICE_CLASS