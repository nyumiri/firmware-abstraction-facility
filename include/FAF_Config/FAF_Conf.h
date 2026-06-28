#ifndef FAF_CONFIG_H
#define FAF_CONFIG_H

#include "FAF/types/FAF_Repository.h"
#include "FAF/utils/FAF_Def.h"

#define S_DECLARE_REPOSITORY(ID) \
    extern const FAF_Repository r_##ID;

#define S_DEVICE_TREE_INIT(ID) \
    struct _dev_tree_##ID {

#define S_DEVICE_DECLARE(T, VAR) \
    T d_##T##_##VAR;

#define S_DEVICE_TREE_END \
    };

#define S_DEVICE_LIST_INIT(ID) \
    static struct _dev_tree_##ID _dev_list_##ID = {

#define S_DEVICE_DEFINE(T, VAR, CONF, ...) \
    .d_##T##_##VAR = { \
        .c_parent = {\
            .m_ops = (FAF_Device_Ops*) FAF_DEVICE_OPS_GET(T),\
            .m_imut = (!(CONF) ? NULL : (FAF_Device_Imut*) (CONF)),\
            .m_ID = FAF_DEVICE_TYPE(T)\
        },\
        __VA_ARGS__\
    }

#define S_DEVICE_LIST_END };

#define S_REPOSITORY_PUBLISH(ID)\
    static FAF_Device* r_##ID##_list[] = {

#define S_REPOSITORY_PUSH(ID, T, VAR) \
    (FAF_Device*) &(_dev_list_##ID.d_##T##_##VAR)

#define S_REPOSITORY_SEAL(ID) }; \
    const FAF_Repository r_##ID = {\
        .devices = r_##ID##_list,\
        .size = sizeof(r_##ID##_list) / sizeof(r_##ID##_list[0])\
    };

#define FAF_REPOSITORY_GET(ID) &(r_##ID)

#endif // FAF_CONFIG_H