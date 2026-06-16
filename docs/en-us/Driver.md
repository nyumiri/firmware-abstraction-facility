# Driver

The Driver is the fundamental unit of FAF. Every piece of hardware or service abstracted by FAF is represented by a driver, which is composed of a `VTable`, a `Class`, and an `Instance` bound at compile time.

The `VTable` declares the public dispatch contract of the driver, carrying the type signature and the function pointers protected by the linker. The `Class` carries the pointer to the `VTable`, the pointer to the `Instance`, and the driver capabilities. The `Instance` carries the type signature, the optional configuration, and any internal driver state.

## Driver API:

### Types:

- *typedef struct* faf_driver_instance_t [FAF_Driver_Instance](#FAF_Driver_Instance)
- *typedef struct* faf_driver_vtable_t [FAF_Driver_VTable](#FAF_Driver_VTable)
- *typedef struct* faf_driver_t [FAF_Driver](#FAF_Driver)

### Macros:

- [ANY_SIGNATURE](#ANY_SIGNATURE)
- [DRIVER_SIGNATURE](#DRIVER_SIGNATURE)(className)
- [VALIDATE_DRIVER_SIGNATURE](#VALIDATE_DRIVER_SIGNATURE)(ctx, sig)
- [FAF_CALL_VOID](#FAF_CALL_VOID)(T, method, ptr, ...)
- [FAF_CALL_RETURN](#FAF_CALL_RETURN)(T, R, method, ptr, ...)
- [DECLARE_METHOD](#DECLARE_METHOD)
- [DECLARE_VTABLE](#DECLARE_VTABLE)

<br>

## Types:

## FAF_Driver_Instance

```c
typedef struct faf_driver_instance_t FAF_Driver_Instance
```

<br>

`FAF_Driver_Instance` is the type definition for the internal struct `faf_driver_instance_t`:

```c
struct faf_driver_instance_t {
    uint32_t signature;
    const void* config;
};
```

<br>

The `Instance` represents the runtime state of the driver. It carries the `signature` that identifies the driver type and an optional `config` pointer to an external configuration struct.

## FAF_Driver_VTable

```c
typedef struct faf_driver_vtable_t FAF_Driver_VTable
```

<br>

`FAF_Driver_VTable` is the type definition for the internal struct `faf_driver_vtable_t`:

```c
struct faf_driver_vtable_t {
    uint32_t signature;

    void (*v_init)(FAF_Driver* self);
    void (*v_dispose)(FAF_Driver* self);
};
```

<br>

The `VTable` is the public dispatch contract of the driver. It carries the type `signature` and the lifecycle function pointers `v_init` and `v_dispose`. Concrete drivers extend `FAF_Driver_VTable` as their first member (`v_parent`) and add their own methods. The `VTable` instance must be declared with `DECLARE_VTABLE` to be allocated in the linker-protected memory section.

## FAF_Driver

```c
typedef struct faf_driver_t FAF_Driver
```

<br>

`FAF_Driver` is the type definition for the internal struct `faf_driver_t`:

```c
struct faf_driver_t {
    uint32_t signature;
    FAF_Driver_Instance* context;

    const FAF_Driver_VTable* vptr;
};
```

<br>

The `Class` represents the base interface of the driver. It carries the type `signature`, the `context` pointer to its corresponding `Instance`, and the `vptr` pointer to the driver's `VTable`. The `vptr` is verified by the dispatcher at runtime before any method call.

## Macros:

## ANY_SIGNATURE

```c
#define ANY_SIGNATURE 0xFFFFFFFF
```

- Returns: Undefined
- Input: Undefined

<br>

`ANY_SIGNATURE` is a reserved constant that represents the absence of a type filter. It is used in functions that accept a `signature` parameter to indicate that any driver should be considered, regardless of its type.

> **NOTE:** Never use `ANY_SIGNATURE` as the signature of a concrete driver.

### Example:

```c
FAF_Manager_DriverIterator(0, 10, onDriverCallback, ANY_SIGNATURE);
```

## DRIVER_SIGNATURE

```c
DRIVER_SIGNATURE(className)
```

- Returns: `uint32_t` with the class signature value
- Input: Driver class name as `TEXT`

<br>

`DRIVER_SIGNATURE` expands to the signature constant of the given class, in the format `className_Class_SIGNATURE`. It is used to obtain a driver's signature in a safe and readable way.

### Example:

```c
FAF_Driver* driver = FAF_Provider_GetDevice(0, DRIVER_SIGNATURE(ArduinoLED));
```

## VALIDATE_DRIVER_SIGNATURE

```c
VALIDATE_DRIVER_SIGNATURE(ctx, sig)
```

- Returns: `int` — `1` if the signature matches, `0` otherwise
- Input: Pointer to `FAF_Driver` or `FAF_Driver_Instance` in `ctx`, expected `uint32_t` signature in `sig`

<br>

`VALIDATE_DRIVER_SIGNATURE` checks whether the `signature` of the given context matches the expected value. It is used internally by vtable methods to validate the driver type before accessing concrete fields of the `Class` or `Instance`.

### Example:

```c
if (!VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(ArduinoLED))) return;
```

## DECLARE_METHOD

```c
DECLARE_METHOD
```

- Returns: Undefined
- Input: Undefined

<br>

`DECLARE_METHOD` is an attribute applied to functions that implement vtable methods. It instructs the compiler to allocate the function in the `.faf.vtable_func` memory section, which is protected by the linker. The dispatcher verifies at runtime that the function pointer is within that section before executing it.

### Example:

```c
static DECLARE_METHOD void vMyDriver_init(FAF_Driver* self) { ... }
```

## DECLARE_VTABLE

```c
DECLARE_VTABLE
```

- Returns: Undefined
- Input: Undefined

<br>

`DECLARE_VTABLE` is an attribute applied to the static instance of a driver's `VTable`. It instructs the compiler to allocate the struct in the `.faf.vtable_ptr` memory section, which is protected by the linker. The dispatcher verifies at runtime that the `vptr` is within that section before accessing any field of the `VTable`.

### Example:

```c
static DECLARE_VTABLE const MyDriver_VTable my_vtable = { ... };
```

## FAF_CALL_VOID

```c
FAF_CALL_VOID(T, method, ptr, ...)
```

- Returns: None
- Input: Class name as `TEXT`, method name as `TEXT`, driver reference as `FAF_Driver*`, and optional arguments via `...`

<br>

`FAF_CALL_VOID` invokes a vtable method with no logical return value. Before the call, the dispatcher verifies that the `vptr` is within the `.faf.vtable_ptr` section, that the function pointer is within the `.faf.vtable_func` section, and that the `VTable` `signature` matches the type `T`. If any check fails, the call is silently ignored.

### Example:

```c
FAF_Driver* driver = FAF_Provider_GetDevice(0, DRIVER_SIGNATURE(ArduinoLED));
FAF_CALL_VOID(ArduinoLED, Turn_ON, driver);
```

## FAF_CALL_RETURN

```c
FAF_CALL_RETURN(T, R, method, ptr, ...)
```

- Returns: Value of type `R` returned by the method, or `{0}` if any check fails
- Input: Class name as `TEXT`, return type `R`, method name as `TEXT`, driver reference as `FAF_Driver*`, and optional arguments via `...`

<br>

`FAF_CALL_RETURN` invokes a vtable method with a logical return value. The type `R` is verified at compile time against the method signature via output parameter — if the given type is incompatible with what the method expects, the compiler emits an error. The same memory and signature checks from `FAF_CALL_VOID` are applied.

### Example:

```c
FAF_Driver* driver = FAF_Provider_GetDevice(0, DRIVER_SIGNATURE(ArduinoWifi));
int status = FAF_CALL_RETURN(ArduinoWifi, int, Status, driver);
```