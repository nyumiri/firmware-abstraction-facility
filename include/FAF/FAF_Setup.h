#ifndef FAF_SETUP_H
#define FAF_SETUP_H

#include "FAF/FAF_ProviderConfig.h"

#define DECLARE_PROVIDER_SUPPLY(list_name)   \
    extern FAF_ProviderConfig provider_##list_name##_data;

#define GET_PROVIDER_SUPPLY(list_name) &(provider_##list_name##_data)

#endif