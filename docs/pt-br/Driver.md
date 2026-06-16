# Driver

O Driver é a unidade fundamental do FAF. Todo hardware ou serviço abstraído pelo FAF é representado por um driver, que é composto por uma `VTable`, uma `Class` e uma `Instance` vinculadas em tempo de compilação.

A `VTable` declara o contrato público de dispatch do driver, carregando a assinatura de tipo e os ponteiros de função protegidos pelo linker. A `Class` carrega o ponteiro para a `VTable`, o ponteiro para a `Instance` e as capacidades do driver. A `Instance` carrega a assinatura de tipo, a configuração opcional e qualquer estado interno do driver.

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

O `FAF_Driver_Instance` é a definição de tipo para a struct interna `faf_driver_instance_t`:

```c
struct faf_driver_instance_t {
    uint32_t signature;
    const void* config;
};
```

<br>

A `Instance` representa o estado do driver em tempo de execução. Ela carrega a `signature` que identifica o tipo do driver e um ponteiro `config` opcional para uma struct de configuração externa.

## FAF_Driver_VTable

```c
typedef struct faf_driver_vtable_t FAF_Driver_VTable
```

<br>

O `FAF_Driver_VTable` é a definição de tipo para a struct interna `faf_driver_vtable_t`:

```c
struct faf_driver_vtable_t {
    uint32_t signature;

    void (*v_init)(FAF_Driver* self);
    void (*v_dispose)(FAF_Driver* self);
};
```

<br>

A `VTable` é o contrato público de dispatch do driver. Ela carrega a `signature` de tipo e os ponteiros de função de ciclo de vida `v_init` e `v_dispose`. Drivers concretos estendem `FAF_Driver_VTable` como primeiro membro (`v_parent`) e adicionam seus próprios métodos. A instância da `VTable` deve ser declarada com `DECLARE_VTABLE` para ser alocada na seção de memória protegida pelo linker.

## FAF_Driver

```c
typedef struct faf_driver_t FAF_Driver
```

<br>

O `FAF_Driver` é a definição de tipo para a struct interna `faf_driver_t`:

```c
struct faf_driver_t {
    uint32_t signature;
    FAF_Driver_Instance* context;

    const FAF_Driver_VTable* vptr;
};
```

<br>

A `Class` representa a interface base do driver. Ela carrega a `signature` de tipo, o ponteiro `context` para sua `Instance` correspondente, e o ponteiro `vptr` para a `VTable` do driver. O `vptr` é verificado pelo dispatcher em tempo de execução antes de qualquer chamada de método.

## Macros:

## ANY_SIGNATURE

```c
#define ANY_SIGNATURE 0xFFFFFFFF
```

- Retorno: Indefinido
- Input: Indefinido

<br>

O `ANY_SIGNATURE` é uma constante reservada que representa ausência de filtro de tipo. É utilizado em funções que aceitam uma `signature` como parâmetro para indicar que qualquer driver deve ser considerado, independente do seu tipo.

> **NOTE:** Nunca use `ANY_SIGNATURE` como assinatura de um driver concreto.

### Exemplo:

```c
FAF_Manager_DriverIterator(0, 10, onDriverCallback, ANY_SIGNATURE);
```

## DRIVER_SIGNATURE

```c
DRIVER_SIGNATURE(className)
```

- Retorno: `uint32_t` com o valor da assinatura da classe
- Input: Nome da classe do driver em forma de `TEXT`

<br>

O `DRIVER_SIGNATURE` expande para a constante de assinatura da classe informada, no formato `className_Class_SIGNATURE`. É utilizado para obter a assinatura de um driver de forma segura e legível.

### Exemplo:

```c
FAF_Driver* driver = FAF_Provider_GetDevice(0, DRIVER_SIGNATURE(ArduinoLED));
```

## VALIDATE_DRIVER_SIGNATURE

```c
VALIDATE_DRIVER_SIGNATURE(ctx, sig)
```

- Retorno: `int` — `1` se a assinatura bate, `0` caso contrário
- Input: Ponteiro para `FAF_Driver` ou `FAF_Driver_Instance` em `ctx`, `uint32_t` da assinatura esperada em `sig`

<br>

O `VALIDATE_DRIVER_SIGNATURE` verifica se a `signature` do contexto informado corresponde ao valor esperado. É utilizado internamente pelos métodos de vtable para validar o tipo do driver antes de acessar campos concretos da `Class` ou `Instance`.

### Exemplo:

```c
if (!VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(ArduinoLED))) return;
```

## DECLARE_METHOD

```c
DECLARE_METHOD
```

- Retorno: Indefinido
- Input: Indefinido

<br>

O `DECLARE_METHOD` é um atributo aplicado a funções que implementam métodos de vtable. Ele instrui o compilador a alocar a função na seção de memória `.faf.vtable_func`, que é protegida pelo linker. O dispatcher verifica em tempo de execução que o ponteiro de função está dentro dessa seção antes de executá-lo.

### Exemplo:

```c
static DECLARE_METHOD void vMyDriver_init(FAF_Driver* self) { ... }
```

## DECLARE_VTABLE

```c
DECLARE_VTABLE
```

- Retorno: Indefinido
- Input: Indefinido

<br>

O `DECLARE_VTABLE` é um atributo aplicado à instância estática da `VTable` de um driver. Ele instrui o compilador a alocar a struct na seção de memória `.faf.vtable_ptr`, que é protegida pelo linker. O dispatcher verifica em tempo de execução que o `vptr` está dentro dessa seção antes de acessar qualquer campo da `VTable`.

### Exemplo:

```c
static DECLARE_VTABLE const MyDriver_VTable my_vtable = { ... };
```

## FAF_CALL_VOID

```c
FAF_CALL_VOID(T, method, ptr, ...)
```

- Retorno: Nenhum
- Input: Nome da classe em forma de `TEXT`, nome do método em forma de `TEXT`, referência do driver em `FAF_Driver*` e argumentos opcionais via `...`

<br>

O `FAF_CALL_VOID` invoca um método de vtable sem retorno lógico. Antes da chamada, o dispatcher verifica que o `vptr` está dentro da seção `.faf.vtable_ptr`, que o ponteiro de função está dentro da seção `.faf.vtable_func`, e que a `signature` da `VTable` corresponde ao tipo `T`. Se qualquer verificação falhar, a chamada é silenciosamente ignorada.

### Exemplo:

```c
FAF_Driver* driver = FAF_Provider_GetDevice(0, DRIVER_SIGNATURE(ArduinoLED));
FAF_CALL_VOID(ArduinoLED, Turn_ON, driver);
```

## FAF_CALL_RETURN

```c
FAF_CALL_RETURN(T, R, method, ptr, ...)
```

- Retorno: Valor do tipo `R` retornado pelo método, ou `{0}` se qualquer verificação falhar
- Input: Nome da classe em forma de `TEXT`, tipo de retorno `R`, nome do método em forma de `TEXT`, referência do driver em `FAF_Driver*` e argumentos opcionais via `...`

<br>

O `FAF_CALL_RETURN` invoca um método de vtable com retorno lógico. O tipo `R` é verificado em tempo de compilação contra a assinatura do método via output parameter — se o tipo informado for incompatível com o esperado pelo método, o compilador emite um erro. As mesmas verificações de memória e signature de `FAF_CALL_VOID` são aplicadas.

### Exemplo:

```c
FAF_Driver* driver = FAF_Provider_GetDevice(0, DRIVER_SIGNATURE(ArduinoWifi));
int status = FAF_CALL_RETURN(ArduinoWifi, int, Status, driver);
```