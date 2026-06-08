#include <Arduino.h>

#include <FAF/FAF.h>
#include <Board_Conf.hpp>

#define LED_DEVICE 0

bool toggle = false;
FAF_Driver* led = nullptr;

void setup() {
  Serial.begin(115200);
  FAF_Provider_Provide(GET_PROVIDER_SUPPLY(hello_config));
  FAF_Provider_Init();
  FAF_Manager_DriverInit_Index(LED_DEVICE);

  led = FAF_Provider_GetDevice(LED_DEVICE, DRIVER_SIGNATURE(ArduinoLED));
}

void loop() {
  if (toggle) { FAF_DRIVER_CALL(ArduinoLED, Turn_OFF, led); toggle = false; }
  else { FAF_DRIVER_CALL(ArduinoLED, Turn_ON, led); toggle = true; }
  
  delay(2000);
}