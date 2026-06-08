# Capabilities

As capacidades são contratos opcionais que um driver pode implementar para expor comportamentos padronizados. Elas são definidas como structs de ponteiros de função e adicionadas como membros da `Class` do driver.

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

O `IConnectable` é a definição de tipo para a struct interna `iConnectable_t`:

```c
typedef struct iConnectable_t {
    int (*connect)(FAF_Driver* self);
    int (*disconnect)(FAF_Driver* self);
} IConnectable;
```

<br>

O `IConnectable` é uma capacidade para drivers que gerenciam conexões. Ele expõe dois métodos: `connect` para estabelecer a conexão e `disconnect` para encerrá-la. Ambos retornam um `int` que deve ser usado pelo driver para indicar sucesso ou falha.

### Exemplo:

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

O `IReportable` é a definição de tipo para a struct interna `iReportable_t`:

```c
typedef struct iReportable_t {
    int (*status)(FAF_Driver* self);
} IReportable;
```

<br>

O `IReportable` é uma capacidade para drivers que expõem um estado consultável. Ele expõe um método `status` que retorna um `int` representando o estado atual do driver.

### Exemplo:

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

O `IToggleable` é a definição de tipo para a struct interna `iToggleable_t`:

```c
typedef struct iToggleable_t {
    void (*turn_on)(FAF_Driver* self);
    void (*turn_off)(FAF_Driver* self);
} IToggleable;
```

<br>

O `IToggleable` é uma capacidade para drivers que podem ser ligados e desligados. Ele expõe dois métodos: `turn_on` e `turn_off`, ambos sem retorno.

### Exemplo:

```c
typedef struct my_driver_class_t {
    FAF_Driver c_parent;
    IToggleable c_toggleable;
} MyDriver_Class;
```