#ifndef FAF_BOARDDEFINITION_H
#define FAF_BOARDDEFINITION_H

#include "FAF/FAF_ProviderConfig.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct FAF_Board_Definition_t FAF_BoardDefinition;

extern FAF_DriverDescriptor driverDescriptors[];
extern FAF_ProviderConfig providerData;

#ifdef __cplusplus
}
#endif

#endif // FAF_BOARDDEFINITION_H