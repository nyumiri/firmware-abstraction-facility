SECTIONS {
    .faf.vtable_ptr : {
        _faf_vtable_ptr_start = .;
        KEEP(*(.faf.vtable_ptr))
        KEEP(*(.faf.vtable_ptr.*))
        _faf_vtable_ptr_end = .;
    }
}
INSERT AFTER .flash.rodata;

SECTIONS {
    .faf.vtable_func : {
        _faf_vtable_func_start = .;
        KEEP(*(.faf.vtable_func.literal))
        KEEP(*(.faf.vtable_func.literal.*))

        KEEP(*(.literal.faf.vtable_func))
        KEEP(*(.literal.faf.vtable_func.*))

        KEEP(*(.faf.vtable_func))
        KEEP(*(.faf.vtable_func.*))
        _faf_vtable_func_end = .;
    }
}
INSERT AFTER .flash.text;