# Driver

O Driver é a unidade fundamental do FAF. Todo hardware ou serviço abstraído pelo FAF é representado por um driver, que é composto por uma `Class` e uma `Instance` vinculadas em tempo de compilação.

A `Class` carrega o ponteiro para a `Instance`, as funções de ciclo de vida `init` e `dispose`, e as capacidades do driver. A `Instance` carrega a assinatura de tipo, a configuração opcional e qualquer estado interno do driver.

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

O `FAF_Driver_Instance` é a definição de tipo para a struct interna `faf_driver_instance_t`:

```c
struct faf_driver_instance_t {
    uint32_t signature;
    const void* config;
};
```

<br>

A `Instance` representa o estado do driver em tempo de execução. Ela carrega a `signature` que identifica o tipo do driver e um ponteiro `config` opcional para uma struct de configuração externa.

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

    void (*init)(FAF_Driver* self);
    void (*dispose)(FAF_Driver* self);
};
```

<br>

A `Class` representa a interface pública do driver. Ela carrega a `signature` de tipo, o ponteiro `context` para sua `Instance` correspondente, e os ponteiros de função `init` e `dispose` que compõem o ciclo de vida do driver.

## FAF_DriverDescriptor

```c
typedef struct FAF_driver_desc_t FAF_DriverDescriptor
```

<br>

O `FAF_DriverDescriptor` é a definição de tipo para a struct interna `FAF_driver_desc_t`:

```c
typedef struct FAF_driver_desc_t {
    FAF_Driver* driver;
    const char* name;
    void (*constructor)(FAF_Driver* self);
} FAF_DriverDescriptor;
```

<br>

O `FAF_DriverDescriptor` é o registro de um driver no Provider. Ele agrupa o ponteiro para a `Class` do driver, seu nome descritivo e seu `constructor`, que é responsável por configurar a `Class` antes da inicialização.

## Macros:

## ANY_SIGNATURE

```c
#define ANY_SIGNATURE 0xFFFFFFFF
```

- Retorno: Indefinido
- Input: Indefinido

<br>

O `ANY_SIGNATURE` é uma constante reservada que representa ausência de filtro de tipo. É utilizado em funções que aceitam uma `signature` como parâmetro para indicar que qualquer driver deve ser considerado, independente do seu tipo.

> **NOTE:** Nunca use `ANY_SIGNATURE` como assinatura de um driver concreto. O `DRIVER_DECLARE_MEMBER` valida em tempo de compilação que nenhum driver possui essa assinatura.

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

## FAF_DRIVER_CALL

```c
FAF_DRIVER_CALL(class_name, method, ptr, ...)
```

- Retorno: Depende do método invocado
- Input: Nome da classe em forma de `TEXT`, nome do método em forma de `TEXT`, referência do driver em `FAF_Driver*` e argumentos opcionais via `...`

<br>

O `FAF_DRIVER_CALL` invoca um método público da `Class` de um driver de forma segura e sem a necessidade de cast manual. Ele expande para a chamada direta da função correspondente no formato `className_Class_method(ptr, ...)`.

### Exemplo:

```c
FAF_Driver* driver = FAF_Provider_GetDevice(0, DRIVER_SIGNATURE(ArduinoLED));
FAF_DRIVER_CALL(ArduinoLED, Turn_ON, driver);
```