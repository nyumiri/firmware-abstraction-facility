# Manager

The Manager is the module responsible for managing the lifecycle of the drivers registered in the Provider, exposing functions for initialization, dispose, and iteration.

## Manager API:

### Functions:

- *void* [FAF_Manager_DriverInit](#FAF_Manager_DriverInit)(FAF_Driver* driver)
- *void* [FAF_Manager_DriverInit_Index](#FAF_Manager_DriverInit_Index)(size_t i)
- *void* [FAF_Manager_DriverInit_All](#FAF_Manager_DriverInit_All)()
- *void* [FAF_Manager_DriverDispose](#FAF_Manager_DriverDispose)(FAF_Manager_DriverDispose)(FAF_Driver* driver)
- *void* [FAF_Manager_DriverDispose_Index](#FAF_Manager_DriverDispose_Index)(size_t i)
- *void* [FAF_Manager_DriverDispose_All](#FAF_Manager_DriverDispose_All)()
- *void* [FAF_Manager_DriverIterator](#FAF_Manager_DriverIterator)(size_t first, size_t count, void (*callback)(FAF_Driver* driver), uint32_t signature)

<br>

## Functions:

## FAF_Manager_DriverInit

```c
void FAF_Manager_DriverInit(FAF_Driver* driver)
```

- Return: void
- Input: Reference of a driver in `FAF_Driver*`

<br>

The `FAF_Manager_DriverInit` initializes a driver directly from its reference, calling its internal `init` function.

### Example:

```c
FAF_Driver* driver = FAF_Provider_GetDevice(0, DRIVER_SIGNATURE(driverClass));
FAF_Manager_DriverInit(driver);
```

## FAF_Manager_DriverInit_Index

```c
void FAF_Manager_DriverInit_Index(size_t i)
```

- Return: void
- Input: Driver index via `Number`

<br>

The `FAF_Manager_DriverInit_Index` initializes a driver from its index in the Provider, calling its internal `init` function.

### Example:

```c
FAF_Manager_DriverInit_Index(0);
```

## FAF_Manager_DriverInit_All

```c
void FAF_Manager_DriverInit_All()
```

- Return: void
- Input: Undefined

<br>

The `FAF_Manager_DriverInit_All` initializes all drivers registered in the Provider in sequence, calling the `init` function of each one.

### Example:

```c
FAF_Manager_DriverInit_All();
```

## FAF_Manager_DriverDispose

```c
void FAF_Manager_DriverDispose(FAF_Driver* driver)
```

- Return: void
- Input: Reference of a driver in `FAF_Driver*`

<br>

The `FAF_Manager_DriverDispose` releases a driver directly from its reference, calling its internal `dispose` function.

### Example:

```c
FAF_Driver* driver = FAF_Provider_GetDevice(0, DRIVER_SIGNATURE(driverClass));
FAF_Manager_DriverDispose(driver);
```

## FAF_Manager_DriverDispose_Index

```c
void FAF_Manager_DriverDispose_Index(size_t i)
```

- Return: void
- Input: Driver index via `Number`

<br>

The `FAF_Manager_DriverDispose_Index` releases a driver from its index in the Provider, calling its internal `dispose` function.

### Example:

```c
FAF_Manager_DriverDispose_Index(0);
```

## FAF_Manager_DriverDispose_All

```c
void FAF_Manager_DriverDispose_All()
```

- Return: void
- Input: Undefined

<br>

The `FAF_Manager_DriverDispose_All` releases all drivers registered in the Provider in sequence, calling the `dispose` function of each one.

### Example:

```c
FAF_Manager_DriverDispose_All();
```

## FAF_Manager_DriverIterator

```c
void FAF_Manager_DriverIterator(size_t first, size_t count, void (*callback)(FAF_Driver* driver), uint32_t signature)
```

- Return: void
- Input: Starting index via `Number`, quantity of drivers via `Number`, callback function via `Function pointer`, and type signature via `DRIVER SIGNATURE`

<br>

The `FAF_Manager_DriverIterator` iterates over a range of drivers registered in the Provider from `first` to `first + count`, calling the `callback` for each driver found. If `count` exceeds the total number of registered drivers, the iteration is automatically limited to the Provider size.

Pass `ANY_SIGNATURE` in `signature` to iterate over all drivers within the range without filtering by type. Otherwise, only drivers whose signature matches the provided value will be passed to the `callback`.

### Example:

```c
FAF_Manager_DriverIterator(0, 10, onDriverCallback, ANY_SIGNATURE);
FAF_Manager_DriverIterator(0, 10, onDriverCallback, DRIVER_SIGNATURE(driverClass));
```