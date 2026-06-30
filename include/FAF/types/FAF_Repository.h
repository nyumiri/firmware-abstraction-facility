#ifndef FAF_REPOSITORY_H
#define FAF_REPOSITORY_H

#include "FAF_Device.h"

#ifdef __cplusplus
#   include <cstddef>
#else
#   include <stddef.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct faf_repo_t FAF_Repository;

typedef enum faf_repo_status_t {
    FAF_REPOSITORY_SUCCESS = 0,
    FAF_REPOSITORY_NO_FOUND = -1,
    FAF_REPOSITORY_INVALID = -2
} FAF_Repository_Status;

struct faf_repo_t {
    FAF_Device** const devices;
    const size_t size;
};

#ifdef __cplusplus
}
#endif

#endif // FAF_REPOSITORY_H