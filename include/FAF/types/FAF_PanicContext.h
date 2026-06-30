#ifndef FAF_PANIC_CTX_H
#define FAF_PANIC_CTX_H

#include <setjmp.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum faf_error_t {
    FAF_INTEGRITY_ERR = -1,
    FAF_EMPTY_CONFIG = -2,
    FAF_OUT_BOUNDS = -3
} FAF_Error;

typedef struct faf_panic_ctx_t {
    FAF_Error error_code;
    const char* file;
    int line;
    const char* info;
} FAF_Panic_Props;

#ifdef __cplusplus
}
#endif

#endif