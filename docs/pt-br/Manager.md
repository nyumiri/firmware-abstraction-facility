# Manager

O Manager é o módulo responsável por gerenciar o ciclo de vida dos drivers registrados no Provider, expondo funções para inicialização, dispose e iteração.

## Manager API:

### Functions:

- *void* [FAF_Manager_DriverInit](#FAF_Manager_DriverInit)(FAF_Driver* driver)
- *void* [FAF_Manager_DriverInit_Index](#FAF_Manager_DriverInit_Index)(size_t i)
- *void* [FAF_Manager_DriverInit_All](#FAF_Manager_DriverInit_All)()
- *void* [FAF_Manager_DriverDispose](#FAF_Manager_DriverDispose)(FAF_Driver* driver)
- *void* [FAF_Manager_DriverDispose_Index](#FAF_Manager_DriverDispose_Index)(size_t i)
- *void* [FAF_Manager_DriverDispose_All](#FAF_Manager_DriverDispose_All)()
- *void* [FAF_Manager_DriverIterator](#FAF_Manager_DriverIterator)(size_t first, size_t count, void (*callback)(FAF_Driver* driver), uint32_t signature)

<br>

## Functions:

## FAF_Manager_DriverInit

```c
void FAF_Manager_DriverInit(FAF_Driver* driver)
```

- Retorno: void
- Input: Referência de um driver em `FAF_Driver*`

<br>

O `FAF_Manager_DriverInit` inicializa um driver diretamente a partir de sua referência, chamando sua função `init` interna.

### Exemplo:

```c
FAF_Driver* driver = FAF_Provider_GetDevice(0, DRIVER_SIGNATURE(driverClass));
FAF_Manager_DriverInit(driver);
```

## FAF_Manager_DriverInit_Index

```c
void FAF_Manager_DriverInit_Index(size_t i)
```

- Retorno: void
- Input: Índice do driver via `Número`

<br>

O `FAF_Manager_DriverInit_Index` inicializa um driver a partir de seu índice no Provider, chamando sua função `init` interna.

### Exemplo:

```c
FAF_Manager_DriverInit_Index(0);
```

## FAF_Manager_DriverInit_All

```c
void FAF_Manager_DriverInit_All()
```

- Retorno: void
- Input: Indefinido

<br>

O `FAF_Manager_DriverInit_All` inicializa todos os drivers registrados no Provider em sequência, chamando a função `init` de cada um.

### Exemplo:

```c
FAF_Manager_DriverInit_All();
```

## FAF_Manager_DriverDispose

```c
void FAF_Manager_DriverDispose(FAF_Driver* driver)
```

- Retorno: void
- Input: Referência de um driver em `FAF_Driver*`

<br>

O `FAF_Manager_DriverDispose` libera um driver diretamente a partir de sua referência, chamando sua função `dispose` interna.

### Exemplo:

```c
FAF_Driver* driver = FAF_Provider_GetDevice(0, DRIVER_SIGNATURE(driverClass));
FAF_Manager_DriverDispose(driver);
```

## FAF_Manager_DriverDispose_Index

```c
void FAF_Manager_DriverDispose_Index(size_t i)
```

- Retorno: void
- Input: Índice do driver via `Número`

<br>

O `FAF_Manager_DriverDispose_Index` libera um driver a partir de seu índice no Provider, chamando sua função `dispose` interna.

### Exemplo:

```c
FAF_Manager_DriverDispose_Index(0);
```

## FAF_Manager_DriverDispose_All

```c
void FAF_Manager_DriverDispose_All()
```

- Retorno: void
- Input: Indefinido

<br>

O `FAF_Manager_DriverDispose_All` libera todos os drivers registrados no Provider em sequência, chamando a função `dispose` de cada um.

### Exemplo:

```c
FAF_Manager_DriverDispose_All();
```

## FAF_Manager_DriverIterator

```c
void FAF_Manager_DriverIterator(size_t first, size_t count, void (*callback)(FAF_Driver* driver), uint32_t signature)
```

- Retorno: void
- Input: Índice inicial via `Número`, quantidade de drivers via `Número`, função de callback via `Ponteiro de função` e assinatura de tipo via `DRIVER SIGNATURE`

<br>

O `FAF_Manager_DriverIterator` itera sobre um intervalo de drivers registrados no Provider a partir de `first` até `first + count`, chamando o `callback` para cada driver encontrado. Caso `count` exceda o total de drivers registrados, a iteração é limitada automaticamente ao tamanho do Provider.

Passe `ANY_SIGNATURE` em `signature` para iterar sobre todos os drivers do intervalo sem filtro de tipo. Caso contrário, apenas os drivers cuja assinatura corresponda ao valor informado serão passados ao `callback`.

### Exemplo:

```c
FAF_Manager_DriverIterator(0, 10, onDriverCallback, ANY_SIGNATURE);
FAF_Manager_DriverIterator(0, 10, onDriverCallback, DRIVER_SIGNATURE(driverClass));
```