# Driver Guide

This guide describes how to structure a driver for the FAF, covering the definition of the `Class`, `Instance`, `SIGNATURE`, `Constructor`, and public methods.

## General Structure

A driver in FAF is composed of two concrete types that extend `FAF_Driver` and `FAF_Driver_Instance`:

```c
typedef struct my_driver_instance_t {
    FAF_Driver_Instance i_parent;
} MyDriver_Instance;

typedef struct my_driver_class_t {
    FAF_Driver c_parent;
} MyDriver_Class;
```

The prefix `i_parent` on the `Instance` and `c_parent` on the `Class` is the FAF convention to identify the base members of each type.

## Defining the SIGNATURE

Each driver must define a unique `uint32_t` constant in the format `className_Class_SIGNATURE`:

```c
#define MyDriver_Class_SIGNATURE 0x12345678
```

This constant is used by FAF to identify the driver type at runtime and is validated at compile time by `DRIVER_DECLARE_MEMBER`.

## Adding Capabilities

Capabilities are optional contracts that the driver can implement. They are added as members of the `Class`:

```c
typedef struct my_driver_class_t {
    FAF_Driver c_parent;
    IToggleable c_toggleable;
} MyDriver_Class;
```

## Defining the Constructor

The `Constructor` is responsible for configuring the base fields of the `Class` before initialization. It must define the `signature` and the `init` pointer:

```c
void MyDriver_Constructor(FAF_Driver* self) {
    if (!self) return;

    self->signature = DRIVER_SIGNATURE(MyDriver);
    self->init = iMyDriver_init;
}
```

## Defining the init

The `init` function is called by the Manager during initialization. This is where capabilities are bound and the hardware is configured:

```c
static void iMyDriver_init(FAF_Driver* self) {
    if (!self) return;

    MyDriver_Class* cls = (MyDriver_Class*) self;
    IToggleable* toggleable = &cls->c_toggleable;

    toggleable->turn_on  = iMyDriver_turn_on;
    toggleable->turn_off = iMyDriver_turn_off;
}
```

## Defining Public Methods

The driver's public methods follow the format `className_Class_method` and serve as the interface exposed to the rest of the system, called via `FAF_DRIVER_CALL`:

```c
void MyDriver_Class_Turn_ON(FAF_Driver* self) {
    if (!self || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(MyDriver))) return;

    MyDriver_Class* cls = (MyDriver_Class*) self;
    IToggleable* toggleable = &cls->c_toggleable;
    if (!toggleable->turn_on) return;

    toggleable->turn_on(self);
}
```

```c
FAF_DRIVER_CALL(MyDriver, Turn_ON, driver);
```