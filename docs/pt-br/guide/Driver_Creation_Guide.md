# Driver Guide

Este guia descreve como estruturar um driver para o FAF, cobrindo a definição da `Class`, da `Instance`, da `SIGNATURE`, do `Constructor` e dos métodos públicos.

## Estrutura geral

Um driver no FAF é composto por dois tipos concretos que estendem `FAF_Driver` e `FAF_Driver_Instance`:

```c
typedef struct my_driver_instance_t {
    FAF_Driver_Instance i_parent;
} MyDriver_Instance;

typedef struct my_driver_class_t {
    FAF_Driver c_parent;
} MyDriver_Class;
```

O prefixo `i_parent` na `Instance` e `c_parent` na `Class` é a convenção do FAF para identificar os membros base de cada tipo.

## Definindo a SIGNATURE

Cada driver deve definir uma constante `uint32_t` única no formato `className_Class_SIGNATURE`:

```c
#define MyDriver_Class_SIGNATURE 0x12345678
```

Essa constante é usada pelo FAF para identificar o tipo do driver em tempo de execução e é validada em tempo de compilação pelo `DRIVER_DECLARE_MEMBER`.

## Adicionando capacidades

Capacidades são contratos opcionais que o driver pode implementar. Elas são adicionadas como membros da `Class`:

```c
typedef struct my_driver_class_t {
    FAF_Driver c_parent;
    IToggleable c_toggleable;
} MyDriver_Class;
```

## Definindo o Constructor

O `Constructor` é responsável por configurar os campos base da `Class` antes da inicialização. Ele deve definir a `signature` e o ponteiro `init`:

```c
void MyDriver_Constructor(FAF_Driver* self) {
    if (!self) return;

    self->signature = DRIVER_SIGNATURE(MyDriver);
    self->init = iMyDriver_init;
}
```

## Definindo o init

O `init` é chamado pelo Manager durante a inicialização. É nele que as capacidades são vinculadas e o hardware é configurado:

```c
static void iMyDriver_init(FAF_Driver* self) {
    if (!self) return;

    MyDriver_Class* cls = (MyDriver_Class*) self;
    IToggleable* toggleable = &cls->c_toggleable;

    toggleable->turn_on  = iMyDriver_turn_on;
    toggleable->turn_off = iMyDriver_turn_off;
}
```

## Definindo métodos públicos

Os métodos públicos do driver seguem o formato `className_Class_method` e são a interface exposta ao restante do sistema, chamados via `FAF_DRIVER_CALL`:

```c
void MyDriver_Class_Turn_ON(FAF_Driver* self) {
    if (!self || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(MyDriver))) return;

    MyDriver_Class* cls = (MyDriver_Class*) self;
    IToggleable* toggleable = &cls->c_toggleable;
    if (!toggleable->turn_on) return;

    toggleable->turn_on(self);
}
```

```c
FAF_DRIVER_CALL(MyDriver, Turn_ON, driver);
```