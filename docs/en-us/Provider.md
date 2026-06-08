# Provider
The Provider is the module responsible for managing the repository where the drivers that were added to the project configuration will be registered.

Basically, it is a **Service Locator** which is the central point where the drivers are stored.

## Provider API:

### Types:

- *typedef struct* FAF_Provider_t [FAF_Provider](#FAF_Provider)

### Variables:

- *static FAF_Provider* [provider](#provider)

### Macros:

- [GET_PROVIDER_SUPPLY](#GET_PROVIDER_SUPPLY)(list_name)

### Functions:

- *void* [FAF_Provider_Provide](#FAF_Provider_Provide)(FAF_ProviderConfig* config)
- *void* [FAF_Provider_Init](#FAF_Provider_Init)()
- *FAF_Driver* *[FAF_Provider_GetDevice](#FAF_Provider_GetDevice)(size_t index, uint32_t type_signature)
- *size_t* [FAF_Provider_Size](#FAF_Provider_Size)()

<br>

## Types:

## FAF_Provider

```c
typedef struct FAF_Provider_t FAF_Provider
```

<br>

The `FAF_Provider` is a type definition for the internal **struct** `FAF_Provider_t`:

```c
struct FAF_Provider_t {
    FAF_ProviderConfig* config;
}
```

<br>

Basically, this struct has a member that is a reference to a global configuration variable that will be consumed by the Provider internally.

## Variables:

## provider

```c
static FAF_Provider provider
```

<br>

The `provider` variable is the internal representation of the Provider in memory. It is a global scope variable that can only be manipulated using the Provider API functions.


## Macros:

## GET_PROVIDER_SUPPLY

```C
GET_PROVIDER_SUPPLY(list_name)
```

- Return: Undefined
- Input: ID of a config in the form of `TEXT`.

<br>

The `GET_PROVIDER_SUPPLY` is a helper macro that basically transforms an ID in the form of `TEXT` into a valid configuration variable at the pre-processing stage.

```c
GET_PROVIDER_SUPPLY(example) --> &(provider_example_data)
```

### Example:

```c
GET_PROVIDER_SUPPLY(example)
```


## Functions:

## FAF_Provider_Provide

```c
void FAF_Provider_Provide(FAF_ProviderConfig* config)
```

- Return: void
- Input: Reference of a variable of type `FAF_ProviderConfig`

<br>

The `FAF_Provider_Provide` is a function that expects a `FAF_ProviderConfig*` containing the registration of all configured drivers and injects it into the Provider so that we can have access to the drivers in the future.

> **NOTE:** To clear the current registration, simply pass a new reference or pass `NULL` if you want to leave the Provider empty.

### Example:

```c
FAF_Provider_Provide(GET_PROVIDER_SUPPLY(example));
```

## FAF_Provider_Init

```c
void FAF_Provider_Init()
```

- Return: void
- Input: Undefined

<br>

The `FAF_Provider_Init` is the function responsible for the internal initialization of the **constructors** of the registered drivers. Do not confuse this with the actual initialization, it is just an initial setup for internal *vtables* and `SIGNATURE` configuration, which is the means by which the driver identifies itself.

>**NOTE:** `FAF_Provider_Init` must be called right after the `FAF_Provider_Provide` function, thus ensuring that the Provider initialization is properly completed.

### Example:

```c
FAF_Provider_Provide(GET_PROVIDER_SUPPLY(example));
FAF_Provider_Init();
```

## FAF_Provider_GetDevice

```c
FAF_Driver* FAF_Provider_GetDevice(size_t index, uint32_t type_signature)
```

- Return: Driver reference in `FAF_Driver*`
- Input: index via `Number`, and the driver type ID via `DRIVER SIGNATURE`.

<br>

The `FAF_Provider_GetDevice` is the function responsible for retrieving a valid `FAF_Driver` reference so that the returned driver can be used later.

It requires you to provide the registration position where the driver is located and its `SIGNATURE`. If it finds it and the type matches what was requested, it returns the reference of the requested driver.

### Example:

```c
FAF_Driver* driver = FAF_Provider_GetDevice(index, DRIVER_SIGNATURE(driverClass));
```

## FAF_Provider_Size

```c
size_t FAF_Provider_Size()
```

- Return: Total amount of drivers in *size_t*
- Input: Undefined

<br>

The `FAF_Provider_Size` is the function responsible for returning the value of how many drivers are registered in the Provider.

### Example:

```c
size_t quantityDrivers = FAF_Provider_Size();
```