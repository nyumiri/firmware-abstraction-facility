#ifndef FAF_MOCK_DEVICE_API
#define FAF_MOCK_DEVICE_API

#include "FAF/types/FAF_Device.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct faf_mockdevice_t FAF_MockDevice;

FAF_DEVICE_DECLARE(FAF_MockDevice)

typedef struct faf_mockdevice_ops_t {
    FAF_Device_Ops v_parent;
    void (*v_speak_num)(FAF_Device* self, int* out);
} FAF_MockDevice_Ops;

#ifdef __cplusplus
}
#endif

#endif // FAF_MOCK_DEVICE_API