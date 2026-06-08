# DSL

A DSL do FAF é um conjunto de macros que permite configurar e registrar drivers no Provider de forma declarativa, sem alocação dinâmica e com verificações em tempo de compilação.

A configuração é dividida em dois arquivos: `FAF_Setup.h` que expõe a macro pública de declaração, e `FAF_Setup_Internal.h` que contém as macros de definição usadas no `.c` de configuração do projeto.

## DSL API:

### Macros:

- [DECLARE_PROVIDER_SUPPLY](#DECLARE_PROVIDER_SUPPLY)(list_name)
- [DRIVER_LIST_INIT](#DRIVER_LIST_INIT)(list_name, ...)
- [DRIVER_DECLARE_MEMBER](#DRIVER_DECLARE_MEMBER)(className, var)
- [DRIVER_LIST_APPEND](#DRIVER_LIST_APPEND)(list_name, className, var, cfg, ...)
- [PROVIDER_SUPPLY_CREATE](#PROVIDER_SUPPLY_CREATE)(list_name, ...)
- [PROVIDER_SUPPLY_APPEND](#PROVIDER_SUPPLY_APPEND)(list_name, className, var, nameStr)

<br>

## Macros:

## DECLARE_PROVIDER_SUPPLY

```c
DECLARE_PROVIDER_SUPPLY(list_name)
```

- Retorno: Indefinido
- Input: ID da lista de configuração em forma de `TEXT`

<br>

O `DECLARE_PROVIDER_SUPPLY` declara externamente a variável de configuração `FAF_ProviderConfig` gerada pelo `PROVIDER_SUPPLY_CREATE`. Deve ser usado no header do arquivo de configuração do projeto para que o Provider consiga enxergar a lista de drivers.

### Exemplo:

```c
// CBoard_Config.h
DECLARE_PROVIDER_SUPPLY(config)
```

## DRIVER_LIST_INIT

```c
DRIVER_LIST_INIT(list_name, ...)
// ...
DRIVER_LIST_END
```

- Retorno: Indefinido
- Input: ID da lista em forma de `TEXT`, seguido de chamadas de `DRIVER_DECLARE_MEMBER`

<br>

O `DRIVER_LIST_INIT` abre a definição de uma struct anônima que agrupa todos os pares de `Class` e `Instance` dos drivers registrados. Cada driver é declarado dentro do bloco usando `DRIVER_DECLARE_MEMBER`. O bloco deve ser fechado obrigatoriamente com `DRIVER_LIST_END`.

> **NOTE:** `DRIVER_LIST_INIT`, `DRIVER_DECLARE_MEMBER` e `DRIVER_LIST_END` trabalham juntos como uma unidade — nunca use um sem os outros.

### Exemplo:

```c
DRIVER_LIST_INIT(config,
    DRIVER_DECLARE_MEMBER(driverClass, driver)
)
DRIVER_LIST_APPEND(config, driverClass, driver, NULL)
DRIVER_LIST_END
```

## DRIVER_DECLARE_MEMBER

```c
DRIVER_DECLARE_MEMBER(className, var)
```

- Retorno: Indefinido
- Input: Nome da classe do driver em forma de `TEXT`, e um identificador de variável em forma de `TEXT`

<br>

O `DRIVER_DECLARE_MEMBER` declara dentro do bloco `DRIVER_LIST_INIT` um par de membros: a `Class` e a `Instance` do driver. Além disso, valida em tempo de compilação que o driver possui uma `SIGNATURE` definida, diferente de zero e diferente de `ANY_SIGNATURE`.

> **NOTE:** Deve ser usado exclusivamente dentro de um bloco `DRIVER_LIST_INIT` / `DRIVER_LIST_END`.

### Exemplo:

```c
DRIVER_LIST_INIT(config,
    DRIVER_DECLARE_MEMBER(driverClass, driver)
)
```

## DRIVER_LIST_APPEND

```c
DRIVER_LIST_APPEND(list_name, className, var, cfg, ...)
```

- Retorno: Indefinido
- Input: ID da lista, nome da classe, identificador da variável, ponteiro de configuração e inicializadores opcionais via `...`

<br>

O `DRIVER_LIST_APPEND` inicializa os membros declarados por `DRIVER_DECLARE_MEMBER`, vinculando a `Class` à sua `Instance` correspondente e aplicando a configuração do driver. Deve ser chamado após o bloco `DRIVER_LIST_INIT` / `DRIVER_LIST_END` para cada driver declarado.

Passe `NULL` em `cfg` caso o driver não necessite de configuração externa.

> **NOTE:** O `var` e o `list_name` devem ser idênticos aos usados no `DRIVER_DECLARE_MEMBER` e `DRIVER_LIST_INIT` correspondentes.

### Exemplo:

```c
DRIVER_LIST_APPEND(config, driverClass, driver, NULL)
```

## PROVIDER_SUPPLY_CREATE

```c
PROVIDER_SUPPLY_CREATE(list_name, ...)
```

- Retorno: Indefinido
- Input: ID da lista em forma de `TEXT`, seguido de chamadas de `PROVIDER_SUPPLY_APPEND`

<br>

O `PROVIDER_SUPPLY_CREATE` cria o array de descritores `FAF_DriverDescriptor` e a variável `FAF_ProviderConfig` que será consumida pelo Provider. O campo `count` é calculado automaticamente em tempo de compilação a partir do array gerado.

> **NOTE:** O `list_name` deve ser o mesmo usado em `DRIVER_LIST_INIT` e `DECLARE_PROVIDER_SUPPLY`.

### Exemplo:

```c
PROVIDER_SUPPLY_CREATE(config,
    PROVIDER_SUPPLY_APPEND(config, driverClass, driver, "Driver Example")
)
```

## PROVIDER_SUPPLY_APPEND

```c
PROVIDER_SUPPLY_APPEND(list_name, className, var, nameStr)
```

- Retorno: Indefinido
- Input: ID da lista, nome da classe, identificador da variável e nome descritivo do driver em forma de `STRING`

<br>

O `PROVIDER_SUPPLY_APPEND` gera um inicializador de `FAF_DriverDescriptor` para um driver, vinculando o ponteiro do driver, seu nome descritivo e seu `constructor`. Deve ser usado exclusivamente dentro de `PROVIDER_SUPPLY_CREATE`.

### Exemplo:

```c
PROVIDER_SUPPLY_CREATE(config,
    PROVIDER_SUPPLY_APPEND(config, driverClass, driver, "Driver Example")
)
```