#include <Board_Conf.hpp>

#include <FAF/FAF_Setup_Internal.h>
#include <FAF/drivers/esp32/arduino/ArduinoDrivers_Internal.h>

static ArduinoLED_Config ledConfig = { .pin = 2 };

DRIVER_LIST_INIT(hello_config, 
    DRIVER_DECLARE_MEMBER(ArduinoLED, led)
)
DRIVER_LIST_APPEND(hello_config, ArduinoLED, led, &ledConfig)
DRIVER_LIST_END

PROVIDER_SUPPLY_CREATE(hello_config,
    PROVIDER_SUPPLY_APPEND(hello_config, ArduinoLED, led, "Built-in LED")
)