# Driver Guide

Este guia descreve como estruturar um driver para o FAF, cobrindo a definição da `VTable`, da `Class`, da `Instance`, da `SIGNATURE`, do `Constructor` e dos métodos de vtable.

## Estrutura geral

Um driver no FAF é composto por três tipos concretos: a `VTable` (contrato público de dispatch), a `Class` (estado e comportamento concreto) e a `Instance` (dados de instância):

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

Essa constante é usada pelo FAF para identificar o tipo do driver em tempo de execução. Por convenção, o valor é derivado dos caracteres ASCII do nome do driver.

## Definindo a VTable

A `VTable` é o contrato público de dispatch do driver. Ela deve ser declarada em um header `_API.h` público, estendendo `FAF_Driver_VTable` como primeiro membro:

```c
typedef struct my_driver_vtable_t {
    FAF_Driver_VTable v_parent;

    void (*v_turn_on)(FAF_Driver* self);
    void (*v_turn_off)(FAF_Driver* self);
} MyDriver_VTable;
```

O prefixo `v_` identifica métodos de vtable. Métodos com retorno lógico usam output parameter como segundo argumento:

```c
void (*v_get_state)(FAF_Driver* self, int* out);
```

## Adicionando capacidades

Capacidades são contratos opcionais que o driver pode implementar. Elas são adicionadas como membros da `Class`:

```c
typedef struct my_driver_class_t {
    FAF_Driver c_parent;
    IToggleable c_toggleable;
} MyDriver_Class;
```

## Definindo o Constructor

O `Constructor` é responsável por configurar os campos base da `Class` antes da inicialização. Ele deve definir a `signature` e o ponteiro `vptr`:

```c
void MyDriver_Constructor(FAF_Driver* self) {
    if (!self) return;

    self->vptr = (const FAF_Driver_VTable*) &my_vtable;
    self->signature = DRIVER_SIGNATURE(MyDriver);
}
```

## Definindo os métodos de vtable

Os métodos de vtable são funções internas marcadas com `DECLARE_METHOD`, colocadas na seção protegida de memória pelo linker. Métodos de lifecycle (`v_init`, `v_dispose`) devem incluir validação extra de signature:

```c
static DECLARE_METHOD void vMyDriver_init(FAF_Driver* self) {
    if (!self || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(MyDriver))) return;

    MyDriver_Class* cls = (MyDriver_Class*) self;
    IToggleable* toggleable = &cls->c_toggleable;

    toggleable->turn_on  = iMyDriver_turn_on;
    toggleable->turn_off = iMyDriver_turn_off;
}
```

Métodos de operação delegam ao estado interno da `Class`:

```c
static DECLARE_METHOD void vMyDriver_turn_on(FAF_Driver* self) {
    if (!self) return;

    MyDriver_Class* cls = (MyDriver_Class*) self;
    if (!cls->c_toggleable.turn_on) return;

    cls->c_toggleable.turn_on(self);
}
```

## Definindo a instância da VTable

A instância da vtable é declarada `static const` com `DECLARE_VTABLE`, tornando-a parte da seção protegida de memória:

```c
static DECLARE_VTABLE const MyDriver_VTable my_vtable = {
    .v_parent = {
        .signature = DRIVER_SIGNATURE(MyDriver),
        .v_init    = vMyDriver_init,
        .v_dispose = vMyDriver_dispose
    },
    .v_turn_on  = vMyDriver_turn_on,
    .v_turn_off = vMyDriver_turn_off
};
```

## Chamando métodos

Métodos sem retorno são chamados via `FAF_CALL_VOID`. Métodos com retorno lógico são chamados via `FAF_CALL_RETURN`, que força verificação de tipo do retorno em tempo de compilação:

```c
FAF_CALL_VOID(MyDriver, Turn_ON, driver);

int state = FAF_CALL_RETURN(MyDriver, int, get_state, driver);
```

O dispatcher verifica automaticamente que o `vptr` está dentro do range de memória protegido e que a signature corresponde ao tipo esperado antes de executar o método.