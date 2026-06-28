#ifndef FAF_COMMON
#define FAF_COMMON

#include "FAF/types/FAF_PanicContext.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*FAF_PanicHandler)(const FAF_Panic_Props* ctx);

void __attribute__((noreturn)) FAF_Panic(const FAF_Panic_Props* ctx);
void FAF_Panic_Switch(FAF_PanicHandler handler);

#ifdef __cplusplus
}
#endif

#endif // FAF_COMMON