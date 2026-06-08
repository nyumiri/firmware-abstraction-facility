# Driver

The Driver is the fundamental unit of FAF. Every hardware or service abstracted by FAF is represented by a driver, which is composed of a `Class` and an `Instance` bound at compile time.

The `Class` carries the pointer to the `Instance`, the lifecycle functions `init` and `dispose`, and the driver's capabilities. The `Instance` carries the type signature, optional configuration, and any internal state of the driver.

## Driver API:

### Types:

- *typedef struct* faf_driver_instance_t [FAF_Driver_Instance](#FAF_Driver_Instance)
- *typedef struct* faf_driver_t [FAF_Driver](#FAF_Driver)
- *typedef struct* FAF_driver_desc_t [FAF_DriverDescriptor](#FAF_DriverDescriptor)

### Macros:

- [ANY_SIGNATURE](#ANY_SIGNATURE)
- [DRIVER_SIGNATURE](#DRIVER_SIGNATURE)(className)
- [FAF_DRIVER_CALL](#FAF_DRIVER_CALL)(class_name, method, ptr, ...)

<br>

## Types:

## FAF_Driver_Instance

```c
typedef struct faf_driver_instance_t FAF_Driver_Instance
```

<br>

The `FAF_Driver_Instance` is the type definition for the internal struct `faf_driver_instance_t`:

```c
struct faf_driver_instance_t {
    uint32_t signature;
    const void* config;
};
```

<br>

The `Instance` represents the driver's state at runtime. It carries the `signature` that identifies the driver type and an optional `config` pointer to an external configuration struct.

## FAF_Driver

```c
typedef struct faf_driver_t FAF_Driver
```

<br>

The `FAF_Driver` is the type definition for the internal struct `faf_driver_t`:

```c
struct faf_driver_t {
    uint32_t signature;
    FAF_Driver_Instance* context;

    void (*init)(FAF_Driver* self);
    void (*dispose)(FAF_Driver* self);
};
```

<br>

The `Class` represents the driver's public interface. It carries the type `signature`, the `context` pointer to its corresponding `Instance`, and the function pointers `init` and `dispose` that make up the driver's lifecycle.

## FAF_DriverDescriptor

```c
typedef struct FAF_driver_desc_t FAF_DriverDescriptor
```

<br>

The `FAF_DriverDescriptor` is the type definition for the internal struct `FAF_driver_desc_t`:

```c
typedef struct FAF_driver_desc_t {
    FAF_Driver* driver;
    const char* name;
    void (*constructor)(FAF_Driver* self);
} FAF_DriverDescriptor;
```

<br>

The `FAF_DriverDescriptor` is the registration of a driver in the Provider. It groups the pointer to the driver's `Class`, its descriptive name, and its `constructor`, which is responsible for configuring the `Class` before initialization.

## Macros:

## ANY_SIGNATURE

```c
#define ANY_SIGNATURE 0xFFFFFFFF
```

- Return: Undefined
- Input: Undefined

<br>

The `ANY_SIGNATURE` is a reserved constant that represents the absence of a type filter. It is used in functions that accept a `signature` as a parameter to indicate that any driver should be considered, regardless of its type.

> **NOTE:** Never use `ANY_SIGNATURE` as a concrete driver's signature. `DRIVER_DECLARE_MEMBER` validates at compile time that no driver has this signature.

### Example:

```c
FAF_Manager_DriverIterator(0, 10, onDriverCallback, ANY_SIGNATURE);
```

## DRIVER_SIGNATURE

```c
DRIVER_SIGNATURE(className)
```

- Return: `uint32_t` containing the value of the class signature
- Input: Name of the driver class in the form of `TEXT`

<br>

The `DRIVER_SIGNATURE` expands to the signature constant of the specified class, in the format `className_Class_SIGNATURE`. It is used to obtain a driver's signature in a safe and readable manner.

### Example:

```c
FAF_Driver* driver = FAF_Provider_GetDevice(0, DRIVER_SIGNATURE(ArduinoLED));
```

## FAF_DRIVER_CALL

```c
FAF_DRIVER_CALL(class_name, method, ptr, ...)
```

- Return: Depends on the invoked method
- Input: Class name in the form of `TEXT`, method name in the form of `TEXT`, driver reference in `FAF_Driver*`, and optional arguments via `...`

<br>

The `FAF_DRIVER_CALL` invokes a public method of a driver's `Class` safely and without the need for a manual cast. It expands to the direct call of the corresponding function in the format `className_Class_method(ptr, ...)`.

### Example:

```c
FAF_Driver* driver = FAF_Provider_GetDevice(0, DRIVER_SIGNATURE(ArduinoLED));
FAF_DRIVER_CALL(ArduinoLED, Turn_ON, driver);
```