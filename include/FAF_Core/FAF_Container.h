#ifndef FAF_CONTAINER_H
#define FAF_CONTAINER_H

#include "FAF/types/FAF_Device.h"
#include "FAF/types/FAF_Iterator.h"
#include "FAF/types/FAF_Repository.h"

#ifdef __cplusplus
#   include <cstddef>
#else
#   include <stddef.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

void FAF_Container_Set(const FAF_Repository* repository);
int FAF_Container_Get(size_t index, FAF_ID ID, FAF_Device** dev);

int FAF_Container_Iterator_Create(FAF_Iterator* it);
int FAF_Container_Iterator_Status(FAF_Iterator* it);
void FAF_Container_Foreach(FAF_Iterator* it, FAF_ID type, void(*const callback)(FAF_Device* device));

#ifdef __cplusplus
}
#endif

#endif // FAF_CONTAINER_H