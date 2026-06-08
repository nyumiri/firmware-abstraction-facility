# Setup Guide

This guide describes how to create and register a driver configuration in FAF, covering the creation of the configuration header, the definition of the driver list, and registration with the Provider.

## Driver Include Convention

Each FAF driver follows a three-header convention:

- `MyDriver_API.h` — signature (`MyDriver_Class_SIGNATURE`), `Constructor`, and public method declarations
- `MyDriver_Class.h` — definition of the `Class` and `Instance`
- `MyDriver_Config.h` — configuration struct (optional, only if the driver requires external configuration)

In the configuration file, include only the necessary headers for each driver:

```c
#include "drivers/MyDriver_API.h"
#include "drivers/MyDriver_Class.h"
#include "drivers/MyDriver_Config.h" // optional
```

## Creating the Configuration Header

The configuration header externally declares the driver list so that the Provider can see it. It must include `FAF_Setup.h` and use `DECLARE_PROVIDER_SUPPLY` with the list ID:

```c
// CBoard_Config.h
#ifndef CBOARD_CONFIG_H
#define CBOARD_CONFIG_H

#include <FAF/FAF_Setup.h>

#ifdef __cplusplus
extern "C" {
#endif

DECLARE_PROVIDER_SUPPLY(config)

#ifdef __cplusplus
}
#endif

#endif // CBOARD_CONFIG_H
```

## Creating the Driver List

In the configuration `.c` file, include `FAF_Setup_Internal.h` and the header created above. Next, declare the driver list with `DRIVER_LIST_INIT`, registering each driver with `DRIVER_DECLARE_MEMBER`:

```c
// CBoard_Config.c
#include <FAF/FAF_Setup_Internal.h>
#include "CBoard_Config.h"

#include "drivers/MyDriver_API.h"
#include "drivers/MyDriver_Class.h"

DRIVER_LIST_INIT(config,
    DRIVER_DECLARE_MEMBER(MyDriver, device)
)
DRIVER_LIST_APPEND(config, MyDriver, device, NULL)
DRIVER_LIST_END
```

> **NOTE:** The `DRIVER_LIST_APPEND` for each driver must be declared between the closing of `DRIVER_LIST_INIT` and `DRIVER_LIST_END`. Every driver declared in `DRIVER_DECLARE_MEMBER` must have a corresponding `DRIVER_LIST_APPEND`.

## Passing a Configuration to the Driver

If the driver requires an external configuration, include `MyDriver_Config.h`, declare it as a static variable, and pass its reference in `DRIVER_LIST_APPEND`:

```c
#include "drivers/MyDriver_API.h"
#include "drivers/MyDriver_Class.h"
#include "drivers/MyDriver_Config.h"

static const MyDriver_Config device_config = {
    .pin = 13
};

DRIVER_LIST_INIT(config,
    DRIVER_DECLARE_MEMBER(MyDriver, device)
)
DRIVER_LIST_APPEND(config, MyDriver, device, &device_config)
DRIVER_LIST_END
```

## Registering Drivers with the Provider

After the list, use `PROVIDER_SUPPLY_CREATE` to generate the configuration variable that will be consumed by the Provider. Each driver must be registered with `PROVIDER_SUPPLY_APPEND`:

```c
PROVIDER_SUPPLY_CREATE(config,
    PROVIDER_SUPPLY_APPEND(config, MyDriver, device, "My Device")
)
```

## Initializing the Provider

Once the configuration is ready, pass it to the Provider using `GET_PROVIDER_SUPPLY` and initialize it with `FAF_Provider_Init`:

```c
FAF_Provider_Provide(GET_PROVIDER_SUPPLY(config));
FAF_Provider_Init();
```

## Complete Example with Multiple Drivers

```c
// CBoard_Config.c
#include <FAF/FAF_Setup_Internal.h>
#include "CBoard_Config.h"

#include "drivers/DriverA_API.h"
#include "drivers/DriverA_Class.h"
#include "drivers/DriverA_Config.h"
#include "drivers/DriverB_API.h"
#include "drivers/DriverB_Class.h"

static const DriverA_Config sensor_config = { .pin = 4 };

DRIVER_LIST_INIT(config,
    DRIVER_DECLARE_MEMBER(DriverA, sensor)
    DRIVER_DECLARE_MEMBER(DriverB, display)
)
DRIVER_LIST_APPEND(config, DriverA, sensor, &sensor_config),
DRIVER_LIST_APPEND(config, DriverB, display, NULL)
DRIVER_LIST_END

PROVIDER_SUPPLY_CREATE(config,
    PROVIDER_SUPPLY_APPEND(config, DriverA, sensor,  "Sensor Temperatura"),
    PROVIDER_SUPPLY_APPEND(config, DriverB, display, "Display OLED")
)
```