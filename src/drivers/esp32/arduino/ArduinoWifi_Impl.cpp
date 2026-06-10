#include "FAF/drivers/esp32/arduino/wifi/ArduinoWifi_API.h"
#include "FAF/drivers/esp32/arduino/wifi/ArduinoWifi_Class.h"
#include "FAF/drivers/esp32/arduino/wifi/ArduinoWifi_Conf.h"

#ifdef ARDUINO_ARCH_ESP32

#include <WiFi.h>
#include <cstring>

/* Status Table */

WifiStatus WTable[] = {
    [WL_IDLE_STATUS] = WifiStatus::W_IDLE,
    [WL_NO_SSID_AVAIL] = WifiStatus::W_SSID_INVALID,
    [WL_SCAN_COMPLETED] = WifiStatus::W_SCAN_COMPLETED,
    [WL_CONNECTED] = WifiStatus::W_CONNECTED,
    [WL_CONNECT_FAILED] = WifiStatus::W_FAILED,
    [WL_CONNECTION_LOST] = WifiStatus::W_LOST,
    [WL_DISCONNECTED] = WifiStatus::W_DISCONNECTED
};

/* Vtable Methods */

static void vArduinoWifi_Connect(FAF_Driver* self, int* out) {
    if (!self || !out || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(ArduinoWifi))) return;

    const FAF_Driver_VTable* vt = self->vptr;
    if (vt->signature != self->signature) return;

    ArduinoWifi_Class* cls = (ArduinoWifi_Class*) self;
    IConnectable* connectable = &cls->c_connectable;
    if (!connectable->connect) return;

    (*out) = connectable->connect(self);
}

static void vArduinoWifi_Disconnect(FAF_Driver* self, int* out) {
    if (!self || !out || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(ArduinoWifi))) return;

    const FAF_Driver_VTable* vt = self->vptr;
    if (vt->signature != self->signature) return;

    ArduinoWifi_Class* cls = (ArduinoWifi_Class*) self;
    IConnectable* connectable = &cls->c_connectable;
    if (!connectable->disconnect) return;

    (*out) = connectable->disconnect(self);
}

static void vArduinoWifi_Status(FAF_Driver* self, int* out) {
    if (!self || !out || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(ArduinoWifi))) return;

    const FAF_Driver_VTable* vt = self->vptr;
    if (vt->signature != self->signature) return;

    ArduinoWifi_Class* cls = (ArduinoWifi_Class*) self;
    IReportable* reportable = &cls->c_reportable;
    
    if (!reportable->status) {
        (*out) = WifiStatus::W_EOF;
        return;
    }

    (*out) = reportable->status(self);
}

static void vArduinoWifi_MacAddress(FAF_Driver* self, char* buf, uint32_t max_len) {
    if (!self || !buf || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(ArduinoWifi))) return;

    const FAF_Driver_VTable* vt = self->vptr;
    if (vt->signature != self->signature) return;
    
    ArduinoWifi_Class* cls = (ArduinoWifi_Class*) self;
    cls->macAddress(self, buf, max_len);
}

static const ArduinoWifi_VTable arduino_wifi_vtable = {
    .v_parent = { .signature = DRIVER_SIGNATURE(ArduinoWifi) },
    
    .v_Connect = vArduinoWifi_Connect,
    .v_Disconnect = vArduinoWifi_Disconnect,

    .v_Status = vArduinoWifi_Status,

    .v_MacAddress = vArduinoWifi_MacAddress
};

/* Internal Methods */

static int iArduinoWifi_connect(FAF_Driver* self) {
    if (!self || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(ArduinoWifi))) return 0;

    FAF_Driver_Instance* inst = self->context;
    if (!inst || !VALIDATE_DRIVER_SIGNATURE(inst, DRIVER_SIGNATURE(ArduinoWifi))) return 0;

    const ArduinoWifi_Config* config = static_cast<const ArduinoWifi_Config*>(inst->config);
    if (!config) return 0;

    WiFi.begin(config->ssid, config->password);
    return 1;
}

static int iArduinoWifi_disconnect(FAF_Driver* self) {
    if (!self || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(ArduinoWifi))) return 0;

    return (int) WiFi.disconnect();
}

static int iArduinoWifi_status(FAF_Driver* self) {
    if (!self || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(ArduinoWifi))) return (int) WifiStatus::W_EOF;

    uint8_t statusID = static_cast<uint8_t>(WiFi.status());
    if (statusID >= static_cast<uint8_t>(WifiStatus::W_EOF)) return (int) WifiStatus::W_FAILED;

    return (int) WTable[statusID];
}

static void iArduinoWifi_macAddress(FAF_Driver* self, char* out, uint32_t max_len) {
    if (!self || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(ArduinoWifi))) return;

    if (!out || (max_len == 0)) return;
    const char* mac = (WiFi.macAddress()).c_str();

    strncpy(out, mac, max_len - 1);
    out[max_len - 1] = '\0';
}

static void iArduinoWifi_init(FAF_Driver* self) {
    if (!self || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(ArduinoWifi))) return;
    
    FAF_Driver_Instance* inst = self->context;
    if (!inst || !VALIDATE_DRIVER_SIGNATURE(inst, DRIVER_SIGNATURE(ArduinoWifi))) return;

    ArduinoWifi_Class* cls = (ArduinoWifi_Class*) self;

    IConnectable* connectable = &cls->c_connectable;
    connectable->connect = iArduinoWifi_connect;
    connectable->disconnect = iArduinoWifi_disconnect;

    IReportable* reportable = &cls->c_reportable;
    reportable->status = iArduinoWifi_status;

    cls->macAddress = iArduinoWifi_macAddress;
}

/* Constructor Zone */

void ArduinoWifi_Constructor(FAF_Driver* self) {
    if (!self) return;

    self->vptr = (const FAF_Driver_VTable*) &arduino_wifi_vtable;

    self->signature = DRIVER_SIGNATURE(ArduinoWifi);
    self->init = iArduinoWifi_init;
}

#endif