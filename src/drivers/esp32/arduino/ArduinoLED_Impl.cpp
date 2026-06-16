#include "FAF/drivers/esp32/arduino/led/ArduinoLED_API.h"
#include "FAF/drivers/esp32/arduino/led/ArduinoLED_Class.h"
#include "FAF/drivers/esp32/arduino/led/ArduinoLED_Conf.h"

#ifdef ARDUINO_ARCH_ESP32

#include <Arduino.h>

/* Internal Methods */

static void iArduinoLED_turn_on(FAF_Driver* self) {
    if (!self || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(ArduinoLED))) return;

    FAF_Driver_Instance* instance = self->context;
    if (!instance || !VALIDATE_DRIVER_SIGNATURE(instance, DRIVER_SIGNATURE(ArduinoLED))) return;

    ArduinoLED_Class* cls = (ArduinoLED_Class*) self;
    const ArduinoLED_Config* config = static_cast<const ArduinoLED_Config*>(instance->config);

    if (!config) return;

    digitalWrite(config->pin, HIGH);
}

static void iArduinoLED_turn_off(FAF_Driver* self) {
    if (!self || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(ArduinoLED))) return;

    FAF_Driver_Instance* instance = self->context;
    if (!instance || !VALIDATE_DRIVER_SIGNATURE(instance, DRIVER_SIGNATURE(ArduinoLED))) return;

    ArduinoLED_Class* cls = (ArduinoLED_Class*) self;
    const ArduinoLED_Config* config = static_cast<const ArduinoLED_Config*>(instance->config);

    if (!config) return;

    digitalWrite(config->pin, LOW);
}

/* Vtable Methods */

static DECLARE_METHOD void vArduinoLED_Init(FAF_Driver* self) {
    if (!self || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(ArduinoLED))) return;

    FAF_Driver_Instance* instance = self->context;
    if (!instance || !VALIDATE_DRIVER_SIGNATURE(instance, DRIVER_SIGNATURE(ArduinoLED))) return;

    ArduinoLED_Class* cls = (ArduinoLED_Class*) self;
    const ArduinoLED_Config* config = static_cast<const ArduinoLED_Config*>(instance->config);

    if (!config) return;
    pinMode(config->pin, OUTPUT);

    IToggleable* toggleable = &cls->c_toggleable;

    toggleable->turn_on = iArduinoLED_turn_on;
    toggleable->turn_off = iArduinoLED_turn_off;
}

static DECLARE_METHOD void vArduinoLED_Turn_ON(FAF_Driver* self) {
    if (!self) return;

    const FAF_Driver_VTable* vt = self->vptr;
    if (vt->signature != self->signature) return;

    ArduinoLED_Class* cls = (ArduinoLED_Class*) self;
    IToggleable* toggleable = &cls->c_toggleable;
    if (!toggleable->turn_on) return;

    toggleable->turn_on(self);
}

static DECLARE_METHOD void vArduinoLED_Turn_OFF(FAF_Driver* self) {
    if (!self || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(ArduinoLED))) return;

    const FAF_Driver_VTable* vt = self->vptr;
    if (vt->signature != self->signature) return;

    ArduinoLED_Class* cls = (ArduinoLED_Class*) self;
    IToggleable* toggleable = &cls->c_toggleable;
    if (!toggleable->turn_off) return;

    toggleable->turn_off(self);
}

static DECLARE_VTABLE const ArduinoLED_VTable arduinoLED_vtable = {
    .v_parent = { 
        .signature = DRIVER_SIGNATURE(ArduinoLED),
        .v_init = vArduinoLED_Init
    },
    .v_Turn_ON = vArduinoLED_Turn_ON,
    .v_Turn_OFF = vArduinoLED_Turn_OFF
};

/* Constructor Zone */

void ArduinoLED_Constructor(FAF_Driver* self) {
    if (!self) return;

    self->vptr = (const FAF_Driver_VTable*) &arduinoLED_vtable;
    self->signature = DRIVER_SIGNATURE(ArduinoLED);
}

#endif