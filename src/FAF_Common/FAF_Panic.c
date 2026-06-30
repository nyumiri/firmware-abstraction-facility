#include "FAF/utils/FAF_Panic.h"
#include "stddef.h"

void FAF_User_Panic(const FAF_Panic_Props* ctx) {
    (void)ctx;
}

#ifdef __STDC_NO_ATOMICS__
    static volatile FAF_PanicHandler p_callback = FAF_User_Panic;
#else
    #include <stdatomic.h>
    static _Atomic FAF_PanicHandler p_callback = FAF_User_Panic;
#endif

void FAF_Panic_Switch(FAF_PanicHandler handler) { 
    #ifdef __STDC_NO_ATOMICS__
        p_callback = (handler == NULL) ? FAF_User_Panic : handler; 
    #else
        atomic_store(&p_callback, ((handler == NULL) ? FAF_User_Panic : handler));
    #endif
}

void __attribute__((noreturn)) FAF_Panic(const FAF_Panic_Props* ctx) { 
    #ifdef __STDC_NO_ATOMICS__
        FAF_PanicHandler const panic = p_callback;
    #else
        FAF_PanicHandler const panic = atomic_load(&p_callback);
    #endif
    
    panic(ctx);
    __builtin_trap();
}