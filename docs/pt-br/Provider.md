# Provider
O Provider é o módulo responsável por gerir o repositório onde ficará registrado os drivers que foram adicionados na configuação do projeto.

Basicamente ele é um **Service Locator** que é o ponto central onde fica guardado os drivers.

## Provider API:

### Types:

- *typedef struct* FAF_Provider_t [FAF_Provider](#FAF_Provider)

### Variables:

- *static FAF_Provider* [provider](#provider)

### Macros:

- [GET_PROVIDER_SUPPLY](#GET_PROVIDER_SUPPLY)(list_name)

### Functions:

- *void* [FAF_Provider_Provide](#FAF_Provider_Provide)(FAF_ProviderConfig* config)
- *void* [FAF_Provider_Init](#FAF_Provider_Init)()
- *FAF_Driver* *[FAF_Provider_GetDevice](#FAF_Provider_GetDevice)(size_t index, uint32_t type_signature)
- *size_t* [FAF_Provider_Size](#FAF_Provider_Size)()

<br>

## Types:

## FAF_Provider

```c
typedef struct FAF_Provider_t FAF_Provider
```

<br>

O `FAF_Provider` é uma definição de tipo para a **struct** interna `FAF_Provider_t`:

```c
struct FAF_Provider_t {
    FAF_ProviderConfig* config;
}
```

<br>

Basicamente essa struct possui um membro que é uma referência para uma variável de configuração global que vai ser consumida pelo Provider internamente.

## Variables:

## provider

```c
static FAF_Provider provider
```

<br>

A variável `provider` é a representação interna do Provider na memoria, é uma variavel de escopo global que só pode ser manipulada usando as funções de API do Provider.


## Macros:

## GET_PROVIDER_SUPPLY

```C
GET_PROVIDER_SUPPLY(list_name)
```

- Retorno: Indefinido
- Input: ID de uma config. em forma de `TEXT`.

<br>

O `GET_PROVIDER_SUPPLY` é uma macro auxiliar que basicamente transforma um ID em forma de `TEXT` em uma variável valida de configuração em estágio de pré-processamento.

```c
GET_PROVIDER_SUPPLY(example) --> &(provider_example_data)
```

### Exemplo:

```c
GET_PROVIDER_SUPPLY(example)
```


## Functions:

## FAF_Provider_Provide

```c
void FAF_Provider_Provide(FAF_ProviderConfig* config)
```

- Retorno: void
- Input: Referência de uma variável do tipo `FAF_ProviderConfig`

<br>

O `FAF_Provider_Provide` é uma função que espera uma `FAF_ProviderConfig*` que contém o registro de todos os drivers configurados e injeta no Provider para que possamos ter acesso aos drivers futuramente.

> **NOTE:** Para limpar o registro atual, basta passar uma referência nova ou passar `NULL` caso queira deixar o Provider vazio.

### Exemplo:

```c
FAF_Provider_Provide(GET_PROVIDER_SUPPLY(example));
```

## FAF_Provider_Init

```c
void FAF_Provider_Init()
```

- Retorno: void
- Input: Indefinido

<br>

O `FAF_Provider_Init` é a função responsável pela inicialização interna dos **constructors** dos drivers registrados, não se confunda com a inicialização de fato, é apenas uma configuração inicial para *vtables* internas e configuração de `SIGNATURE`, que é o meio pelo qual o driver se identifica.

>**NOTE:** o `FAF_Provider_Init` deve ser chamado logo em seguida da função `FAF_Provider_Provide`, assim garantimos que a inicialização do Provider está devidamente feita corretamente.

### Exemplo:

```c
FAF_Provider_Provide(GET_PROVIDER_SUPPLY(example));
FAF_Provider_Init();
```

## FAF_Provider_GetDevice

```c
FAF_Driver* FAF_Provider_GetDevice(size_t index, uint32_t type_signature)
```

- Retorno: Referência do Driver em `FAF_Driver*`
- Input: indice via `Número`, e o ID de tipo do driver via `DRIVER SIGNATURE`.

<br>

O `FAF_Provider_GetDevice` é a função responsável por buscar uma referência `FAF_Driver` válida para que o driver retornado ser usado depois.

Ela precisa que você informe qual posição de registro onde o driver se localiza e a sua `SIGNATURE` e se ela achar e o tipo ser igual ao que foi requisitado, ele retorna a referência do driver requisitado.

### Exemplo:

```c
FAF_Driver* driver = FAF_Provider_GetDevice(index, DRIVER_SIGNATURE(driverClass));
```

## FAF_Provider_Size

```c
size_t FAF_Provider_Size()
```

- Retorno: Quantidade total de drivers em *size_t*
- Input: Indefinido

<br>

O `FAF_Provider_Size` é a função responsável por retornar o valor de quantos drivers estão registrados no Provider.

### Exemplo:

```c
size_t quantityDrivers = FAF_Provider_Size();
```