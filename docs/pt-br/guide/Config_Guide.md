# Setup Guide

Este guia descreve como criar e registrar uma configuração de drivers no FAF, cobrindo a criação do header de configuração, a definição da lista de drivers e o registro no Provider.

## Convenção de includes de um driver

Cada driver do FAF segue uma convenção de três headers:

- `MyDriver_API.h` — assinatura (`MyDriver_Class_SIGNATURE`), `Constructor` e declarações dos métodos públicos
- `MyDriver_Class.h` — definição da `Class` e da `Instance`
- `MyDriver_Config.h` — struct de configuração (opcional, apenas se o driver precisar de configuração externa)

No arquivo de configuração, inclua apenas os headers necessários para cada driver:

```c
#include "drivers/MyDriver_API.h"
#include "drivers/MyDriver_Class.h"
#include "drivers/MyDriver_Config.h" // opcional
```

## Criando o header de configuração

O header de configuração declara externamente a lista de drivers para que o Provider consiga enxergá-la. Ele deve incluir `FAF_Setup.h` e usar `DECLARE_PROVIDER_SUPPLY` com o ID da lista:

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

## Criando a lista de drivers

No arquivo `.c` de configuração, inclua `FAF_Setup_Internal.h` e o header criado acima. Em seguida, declare a lista de drivers com `DRIVER_LIST_INIT`, registrando cada driver com `DRIVER_DECLARE_MEMBER`:

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

> **NOTE:** O `DRIVER_LIST_APPEND` de cada driver deve ser declarado entre o fechamento do `DRIVER_LIST_INIT` e o `DRIVER_LIST_END`. Cada driver declarado em `DRIVER_DECLARE_MEMBER` deve ter um `DRIVER_LIST_APPEND` correspondente.

## Passando uma configuração para o driver

Caso o driver necessite de uma configuração externa, inclua o `MyDriver_Config.h`, declare-a como variável estática e passe sua referência no `DRIVER_LIST_APPEND`:

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

## Registrando os drivers no Provider

Após a lista, use `PROVIDER_SUPPLY_CREATE` para gerar a variável de configuração que será consumida pelo Provider. Cada driver deve ser registrado com `PROVIDER_SUPPLY_APPEND`:

```c
PROVIDER_SUPPLY_CREATE(config,
    PROVIDER_SUPPLY_APPEND(config, MyDriver, device, "My Device")
)
```

## Inicializando o Provider

Com a configuração pronta, passe-a ao Provider usando `GET_PROVIDER_SUPPLY` e inicialize com `FAF_Provider_Init`:

```c
FAF_Provider_Provide(GET_PROVIDER_SUPPLY(config));
FAF_Provider_Init();
```

## Exemplo completo com múltiplos drivers

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