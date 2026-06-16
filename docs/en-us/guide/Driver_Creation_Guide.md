# Driver Guide

This guide describes how to structure a driver for FAF, covering the definition of the `VTable`, `Class`, `Instance`, `SIGNATURE`, `Constructor`, and vtable methods.

## General structure

A driver in FAF is composed of three concrete types: the `VTable` (public dispatch contract), the `Class` (concrete state and behavior), and the `Instance` (instance data):

```c
typedef struct my_driver_instance_t {
    FAF_Driver_Instance i_parent;
} MyDriver_Instance;

typedef struct my_driver_class_t {
    FAF_Driver c_parent;
} MyDriver_Class;
```

The prefix `i_parent` in the `Instance` and `c_parent` in the `Class` is the FAF convention for identifying the base members of each type.

## Defining the SIGNATURE

Each driver must define a unique `uint32_t` constant in the format `className_Class_SIGNATURE`:

```c
#define MyDriver_Class_SIGNATURE 0x12345678
```

This constant is used by FAF to identify the driver type at runtime. By convention, the value is derived from the ASCII characters of the driver name.

## Defining the VTable

The `VTable` is the public dispatch contract of the driver. It must be declared in a public `_API.h` header, extending `FAF_Driver_VTable` as its first member:

```c
typedef struct my_driver_vtable_t {
    FAF_Driver_VTable v_parent;

    void (*v_turn_on)(FAF_Driver* self);
    void (*v_turn_off)(FAF_Driver* self);
} MyDriver_VTable;
```

The `v_` prefix identifies vtable methods. Methods with a logical return value use an output parameter as the second argument:

```c
void (*v_get_state)(FAF_Driver* self, int* out);
```

## Adding capabilities

Capabilities are optional contracts that a driver can implement. They are added as members of the `Class`:

```c
typedef struct my_driver_class_t {
    FAF_Driver c_parent;
    IToggleable c_toggleable;
} MyDriver_Class;
```

## Defining the Constructor

The `Constructor` is responsible for configuring the base fields of the `Class` before initialization. It must set the `signature` and the `vptr` pointer:

```c
void MyDriver_Constructor(FAF_Driver* self) {
    if (!self) return;

    self->vptr = (const FAF_Driver_VTable*) &my_vtable;
    self->signature = DRIVER_SIGNATURE(MyDriver);
}
```

## Defining vtable methods

Vtable methods are internal functions marked with `DECLARE_METHOD`, placed in the linker-protected memory section. Lifecycle methods (`v_init`, `v_dispose`) must include an extra signature validation:

```c
static DECLARE_METHOD void vMyDriver_init(FAF_Driver* self) {
    if (!self || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(MyDriver))) return;

    MyDriver_Class* cls = (MyDriver_Class*) self;
    IToggleable* toggleable = &cls->c_toggleable;

    toggleable->turn_on  = iMyDriver_turn_on;
    toggleable->turn_off = iMyDriver_turn_off;
}
```

Operation methods delegate to the internal state of the `Class`:

```c
static DECLARE_METHOD void vMyDriver_turn_on(FAF_Driver* self) {
    if (!self) return;

    MyDriver_Class* cls = (MyDriver_Class*) self;
    if (!cls->c_toggleable.turn_on) return;

    cls->c_toggleable.turn_on(self);
}
```

## Defining the VTable instance

The vtable instance is declared `static const` with `DECLARE_VTABLE`, making it part of the linker-protected memory section:

```c
static DECLARE_VTABLE const MyDriver_VTable my_vtable = {
    .v_parent = {
        .signature = DRIVER_SIGNATURE(MyDriver),
        .v_init    = vMyDriver_init,
        .v_dispose = vMyDriver_dispose
    },
    .v_turn_on  = vMyDriver_turn_on,
    .v_turn_off = vMyDriver_turn_off
};
```

## Calling methods

Methods without a return value are called via `FAF_CALL_VOID`. Methods with a logical return value are called via `FAF_CALL_RETURN`, which enforces compile-time type checking of the return value:

```c
FAF_CALL_VOID(MyDriver, Turn_ON, driver);

int state = FAF_CALL_RETURN(MyDriver, int, get_state, driver);
```

The dispatcher automatically verifies that the `vptr` is within the protected memory range and that the signature matches the expected type before executing the method.