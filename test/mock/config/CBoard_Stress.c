#include <FAF/FAF_Setup_Internal.h>
#include "CBoard_Stress.h"

#include "../drivers/DummyDriver.h"
#include "../drivers/DummySignature.h"

DRIVER_LIST_INIT(stress,
    DRIVER_DECLARE_MEMBER(DummyDriver, d1)
    DRIVER_DECLARE_MEMBER(DummyDriver, d2)
    DRIVER_DECLARE_MEMBER(DummyDriver, d3)
    DRIVER_DECLARE_MEMBER(DummyDriver, d4)
    DRIVER_DECLARE_MEMBER(DummyDriver, d5)
    DRIVER_DECLARE_MEMBER(DummyDriver, d6)
    DRIVER_DECLARE_MEMBER(DummyDriver, d7)
    DRIVER_DECLARE_MEMBER(DummyDriver, d8)
    DRIVER_DECLARE_MEMBER(DummyDriver, d9)
    DRIVER_DECLARE_MEMBER(DummyDriver, d10)
)

DRIVER_LIST_APPEND(stress, DummyDriver, d1, NULL),
DRIVER_LIST_APPEND(stress, DummyDriver, d2, NULL),
DRIVER_LIST_APPEND(stress, DummyDriver, d3, NULL),
DRIVER_LIST_APPEND(stress, DummyDriver, d4, NULL),
DRIVER_LIST_APPEND(stress, DummyDriver, d5, NULL),
DRIVER_LIST_APPEND(stress, DummyDriver, d6, NULL),
DRIVER_LIST_APPEND(stress, DummyDriver, d7, NULL),
DRIVER_LIST_APPEND(stress, DummyDriver, d8, NULL),
DRIVER_LIST_APPEND(stress, DummyDriver, d9, NULL),
DRIVER_LIST_APPEND(stress, DummyDriver, d10, NULL)
DRIVER_LIST_END

PROVIDER_SUPPLY_CREATE(stress,
    PROVIDER_SUPPLY_APPEND(stress, DummyDriver, d1, "Sensor Temperatura"),
    PROVIDER_SUPPLY_APPEND(stress, DummyDriver, d2, "Sensor Umidade"),
    PROVIDER_SUPPLY_APPEND(stress, DummyDriver, d3, "Modulo WiFi"),
    PROVIDER_SUPPLY_APPEND(stress, DummyDriver, d4, "Modulo Bluetooth"),
    PROVIDER_SUPPLY_APPEND(stress, DummyDriver, d5, "Display OLED"),
    PROVIDER_SUPPLY_APPEND(stress, DummyDriver, d6, "Botao Emergencia"),
    PROVIDER_SUPPLY_APPEND(stress, DummyDriver, d7, "LED Status"),
    PROVIDER_SUPPLY_APPEND(stress, DummyDriver, d8, "Flash Memory"),
    PROVIDER_SUPPLY_APPEND(stress, DummyDriver, d9, "Buzzer"),
    PROVIDER_SUPPLY_APPEND(stress, DummyDriver, d10, "Sensor Presenca")
)