# Capabilities

Capabilities are optional contracts that a driver can implement to expose standardized behaviors. They are defined as structs of function pointers and added as members of the driver's `Class`.

## Capabilities API:

### Types:

- *typedef struct* iConnectable_t [IConnectable](#IConnectable)
- *typedef struct* iReportable_t [IReportable](#IReportable)
- *typedef struct* iToggleable_t [IToggleable](#IToggleable)

<br>

## Types:

## IConnectable

```c
typedef struct iConnectable_t IConnectable
```

<br>

The `IConnectable` is the type definition for the internal struct `iConnectable_t`:

```c
typedef struct iConnectable_t {
    int (*connect)(FAF_Driver* self);
    int (*disconnect)(FAF_Driver* self);
} IConnectable;
```

<br>

The `IConnectable` is a capability for drivers that manage connections. It exposes two methods: `connect` to establish the connection and `disconnect` to terminate it. Both return an `int` that should be used by the driver to indicate success or failure.

### Example:

```c
typedef struct my_driver_class_t {
    FAF_Driver c_parent;
    IConnectable c_connectable;
} MyDriver_Class;
```

## IReportable

```c
typedef struct iReportable_t IReportable
```

<br>

The `IReportable` is the type definition for the internal struct `iReportable_t`:

```c
typedef struct iReportable_t {
    int (*status)(FAF_Driver* self);
} IReportable;
```

<br>

The `IReportable` is a capability for drivers that expose a queryable state. It exposes a `status` method that returns an `int` representing the current state of the driver.

### Example:

```c
typedef struct my_driver_class_t {
    FAF_Driver c_parent;
    IReportable c_reportable;
} MyDriver_Class;
```

## IToggleable

```c
typedef struct iToggleable_t IToggleable
```

<br>

The `IToggleable` is the type definition for the internal struct `iToggleable_t`:

```c
typedef struct iToggleable_t {
    void (*turn_on)(FAF_Driver* self);
    void (*turn_off)(FAF_Driver* self);
} IToggleable;
```

<br>

The `IToggleable` is a capability for drivers that can be turned on and off. It exposes two methods: `turn_on` and `turn_off`, both with no return value.

### Example:

```c
typedef struct my_driver_class_t {
    FAF_Driver c_parent;
    IToggleable c_toggleable;
} MyDriver_Class;
```