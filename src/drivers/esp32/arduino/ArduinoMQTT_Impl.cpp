#include "FAF/drivers/esp32/arduino/mqtt/ArduinoMQTT_API.h"
#include "FAF/drivers/esp32/arduino/mqtt/ArduinoMQTT_Class.h"
#include "FAF/drivers/esp32/arduino/mqtt/ArduinoMQTT_Conf.h"

#ifdef ARDUINO_ARCH_ESP32

#include <cstdlib>
#include <cstring>

#include <WiFiClient.h>
#include <PubSubClient.h>

/* Vtable Methods */

static void vArduinoMQTT_Connect(FAF_Driver* self, int* out) {
    if (!self || !out || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(ArduinoMQTT))) return;

    const FAF_Driver_VTable* vt = self->vptr;
    if (vt->signature != self->signature) return;

    ArduinoMQTT_Class* cls = (ArduinoMQTT_Class*) self;
    IConnectable* connectable = &cls->c_connectable;
    if (!connectable->connect) return;

    (*out) = connectable->connect(self);
}

static void vArduinoMQTT_Disconnect(FAF_Driver* self, int* out) {
    if (!self || !out || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(ArduinoMQTT))) return;

    const FAF_Driver_VTable* vt = self->vptr;
    if (vt->signature != self->signature) return;

    ArduinoMQTT_Class* cls = (ArduinoMQTT_Class*) self;
    IConnectable* connectable = &cls->c_connectable;
    if (!connectable->disconnect) return;

    (*out) = connectable->disconnect(self);
}

static void vArduinoMQTT_Publish(FAF_Driver* self, int* out, const char* topic, const char* payload) {
    if (!self || !out || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(ArduinoMQTT))) return;

    const FAF_Driver_VTable* vt = self->vptr;
    if (vt->signature != self->signature) return;

    ArduinoMQTT_Class* cls = (ArduinoMQTT_Class*) self;
    if (!cls->publish) return;
    
    (*out) = cls->publish(self, topic, payload);
}

static void vArduinoMQTT_Subscribe(FAF_Driver* self, int* out, const char* topic) {
    if (!self || !out || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(ArduinoMQTT))) return;

    const FAF_Driver_VTable* vt = self->vptr;
    if (vt->signature != self->signature) return;

    ArduinoMQTT_Class* cls = (ArduinoMQTT_Class*) self;
    if (!cls->subscribe) return;
    
    (*out) = cls->subscribe(self, topic);
}

static void vArduinoMQTT_Listen(FAF_Driver* self) {
    if (!self || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(ArduinoMQTT))) return;

    const FAF_Driver_VTable* vt = self->vptr;
    if (vt->signature != self->signature) return;

    ArduinoMQTT_Class* cls = (ArduinoMQTT_Class*) self;
    if (!cls->listen) return;
    
    cls->listen(self);
}

static void vArduinoMQTT_Message_IsReady(FAF_Driver* self, int* out) {
    if (!self || !out || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(ArduinoMQTT))) return;

    const FAF_Driver_VTable* vt = self->vptr;
    if (vt->signature != self->signature) return;

    FAF_Driver_Instance* context = self->context;
    if (!context || !VALIDATE_DRIVER_SIGNATURE(context, DRIVER_SIGNATURE(ArduinoMQTT))) return;

    ArduinoMQTT_Instance* instance = (ArduinoMQTT_Instance*) self->context;
    
    (*out) = instance->m_messageBusy;
}

static void vArduinoMQTT_Message_Read(FAF_Driver* self, FAF_MQTT_Packet* buf) {
    if (!self || !buf || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(ArduinoMQTT))) return;

    const FAF_Driver_VTable* vt = self->vptr;
    if (vt->signature != self->signature) return;

    FAF_Driver_Instance* context = self->context;
    if (!context || !VALIDATE_DRIVER_SIGNATURE(context, DRIVER_SIGNATURE(ArduinoMQTT))) return;

    ArduinoMQTT_Instance* instance = (ArduinoMQTT_Instance*) self->context;
    FAF_MQTT_Packet* packet = static_cast<FAF_MQTT_Packet*>(instance->m_messagePacket);
    if (!packet) return;

    memcpy(buf, packet, sizeof(FAF_MQTT_Packet));
}

static void vArduinoMQTT_Message_Flush(FAF_Driver* self) {
    if (!self || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(ArduinoMQTT))) return;

    const FAF_Driver_VTable* vt = self->vptr;
    if (vt->signature != self->signature) return;

    FAF_Driver_Instance* context = self->context;
    if (!context || !VALIDATE_DRIVER_SIGNATURE(context, DRIVER_SIGNATURE(ArduinoMQTT))) return;

    ArduinoMQTT_Instance* instance = (ArduinoMQTT_Instance*) self->context;
    instance->m_messageBusy = 0;
}

static const ArduinoMQTT_VTable arduino_mqtt_vtable = {
    .v_parent = { .signature = DRIVER_SIGNATURE(ArduinoMQTT) },

    .v_Connect = vArduinoMQTT_Connect,
    .v_Disconnect = vArduinoMQTT_Disconnect,

    .v_Publish = vArduinoMQTT_Publish,
    .v_Subscribe = vArduinoMQTT_Subscribe,
    .v_Listen = vArduinoMQTT_Listen,

    .v_Message_IsReady = vArduinoMQTT_Message_IsReady,
    .v_Message_Read = vArduinoMQTT_Message_Read,
    .v_Message_Flush = vArduinoMQTT_Message_Flush
};

/* Internal Stuff */

struct arduino_mqtt_internal_t {
    WiFiClient* m_wifiClient;
    PubSubClient* m_mqttClient;
};

static void iArduinoMQTT_callback(FAF_Driver* self, char* topic, byte* payload, unsigned int lenght) {
    if (!self || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(ArduinoMQTT))) return;

    FAF_Driver_Instance* context = self->context;
    if (!context || !VALIDATE_DRIVER_SIGNATURE(context, DRIVER_SIGNATURE(ArduinoMQTT))) return;

    ArduinoMQTT_Instance* instance = (ArduinoMQTT_Instance*) self->context;

    if (instance->m_messageBusy) return;

    FAF_MQTT_Packet* packet = static_cast<FAF_MQTT_Packet*>(instance->m_messagePacket);
    if (!packet) return;

    packet->topic = topic;
    memcpy(packet->payload, payload, lenght);
    packet->payload[lenght] = '\0';

    instance->m_messageBusy = 1;
}

static int iArduinoMQTT_connect(FAF_Driver* self) {
    if (!self || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(ArduinoMQTT))) return 0;

    FAF_Driver_Instance* context = self->context;
    if (!context || !VALIDATE_DRIVER_SIGNATURE(context, DRIVER_SIGNATURE(ArduinoMQTT))) return 0;

    ArduinoMQTT_Instance* instance = (ArduinoMQTT_Instance*) self->context;
    ArduinoMQTT_Internal* internal = (ArduinoMQTT_Internal*) instance->itn_props;
    if (!internal) return 0;

    PubSubClient* mqttClient = internal->m_mqttClient;
    if (!mqttClient) return 0;

    size_t trys = 0;

    while (trys < 3 && (!mqttClient->connected())) {
        if (mqttClient->connect(instance->m_clientID)) break;
        trys++;
        delay(2000);
    }

    return (int) mqttClient->connected(); 
}

static int iArduinoMQTT_disconnect(FAF_Driver* self) {
    if (!self || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(ArduinoMQTT))) return 0;

    FAF_Driver_Instance* context = self->context;
    if (!context || !VALIDATE_DRIVER_SIGNATURE(context, DRIVER_SIGNATURE(ArduinoMQTT))) return 0;

    ArduinoMQTT_Instance* instance = (ArduinoMQTT_Instance*) self->context;
    ArduinoMQTT_Internal* internal = (ArduinoMQTT_Internal*) instance->itn_props;
    if (!internal) return 0;

    PubSubClient* mqttClient = internal->m_mqttClient;
    if (!mqttClient) return 0;

    mqttClient->disconnect();
    return 1;
}

static int iArduinoMQTT_publish(FAF_Driver* self, const char* topic, const char* payload) {
    if (!self || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(ArduinoMQTT))) return 0;

    FAF_Driver_Instance* context = self->context;
    if (!context || !VALIDATE_DRIVER_SIGNATURE(context, DRIVER_SIGNATURE(ArduinoMQTT))) return 0;

    ArduinoMQTT_Instance* instance = (ArduinoMQTT_Instance*) self->context;
    ArduinoMQTT_Internal* internal = (ArduinoMQTT_Internal*) instance->itn_props;
    if (!internal) return 0;

    PubSubClient* mqttClient = internal->m_mqttClient;
    if (!mqttClient) return 0;

    return (int) mqttClient->publish(topic, payload);
}

static int iArduinoMQTT_subscribe(FAF_Driver* self, const char* topic) {
    if (!self || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(ArduinoMQTT))) return 0;

    FAF_Driver_Instance* context = self->context;
    if (!context || !VALIDATE_DRIVER_SIGNATURE(context, DRIVER_SIGNATURE(ArduinoMQTT))) return 0;

    ArduinoMQTT_Instance* instance = (ArduinoMQTT_Instance*) self->context;
    ArduinoMQTT_Internal* internal = (ArduinoMQTT_Internal*) instance->itn_props;
    if (!internal) return 0;

    PubSubClient* mqttClient = internal->m_mqttClient;
    if (!mqttClient) return 0;

    return (int) mqttClient->subscribe(topic);
}

static void iArduinoMQTT_listen(FAF_Driver* self) {
    if (!self || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(ArduinoMQTT))) return;

    FAF_Driver_Instance* context = self->context;
    if (!context || !VALIDATE_DRIVER_SIGNATURE(context, DRIVER_SIGNATURE(ArduinoMQTT))) return;

    ArduinoMQTT_Instance* instance = (ArduinoMQTT_Instance*) self->context;
    ArduinoMQTT_Internal* internal = (ArduinoMQTT_Internal*) instance->itn_props;
    if (!internal) return;

    PubSubClient* mqttClient = internal->m_mqttClient;
    if (!mqttClient) return;

    mqttClient->loop();
}

static void iArduinoMQTT_init(FAF_Driver* self) {
    if (!self || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(ArduinoMQTT))) return;

    FAF_Driver_Instance* context = self->context;
    if (!context || !VALIDATE_DRIVER_SIGNATURE(context, DRIVER_SIGNATURE(ArduinoMQTT))) return;

    ArduinoMQTT_Class* cls = (ArduinoMQTT_Class*) self;

    const ArduinoMQTT_Config* config = static_cast<const ArduinoMQTT_Config*>(self->context->config);
    if (!config) return;

    ArduinoMQTT_Instance* instance = (ArduinoMQTT_Instance*) self->context;

    /* Dinamic Allocation on Internal Props */

    instance->m_messagePacket = (FAF_MQTT_Packet*) malloc(sizeof(FAF_MQTT_Packet));
    if (!instance->m_messagePacket) return;

    instance->itn_props = (ArduinoMQTT_Internal*) malloc(sizeof(ArduinoMQTT_Internal));
    if (!instance->itn_props) {
        free(instance->m_messagePacket);
        
        instance->m_messagePacket = NULL;
        return;
    }

    ArduinoMQTT_Internal* internal = instance->itn_props;
    internal->m_wifiClient = new WiFiClient;

    if (!internal->m_wifiClient) { 
        free(internal);
        free(instance->m_messagePacket);
        
        instance->itn_props = NULL;
        instance->m_messagePacket = NULL;
        return;
    }

    internal->m_mqttClient = new PubSubClient(*(internal->m_wifiClient));

    if (!internal->m_mqttClient) {
        delete (internal->m_wifiClient);
        free(internal);
        free(instance->m_messagePacket);
        
        instance->itn_props = NULL;
        instance->m_messagePacket = NULL;
        return;
    }

    /* Configuration of Internal MQTT Broker */

    PubSubClient* mqttClient = internal->m_mqttClient;
    mqttClient->setServer(config->addr, config->port);
    mqttClient->setCallback([self](char* topic, byte* payload, unsigned int lenght) {
        iArduinoMQTT_callback(self, topic, payload, lenght);
    });
    mqttClient->setBufferSize(512);

    /* Finish Driver Internal VTable */

    IConnectable* connectable = &cls->c_connectable;
    connectable->connect = iArduinoMQTT_connect;
    connectable->disconnect = iArduinoMQTT_disconnect;

    cls->publish = iArduinoMQTT_publish;
    cls->subscribe = iArduinoMQTT_subscribe;
    cls->listen = iArduinoMQTT_listen;
}

static void iArduinoMQTT_dispose(FAF_Driver* self) {
    if (!self || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(ArduinoMQTT))) return;

    FAF_Driver_Instance* context = self->context;
    if (!context || !VALIDATE_DRIVER_SIGNATURE(context, DRIVER_SIGNATURE(ArduinoMQTT))) return;

    ArduinoMQTT_Instance* instance = (ArduinoMQTT_Instance*) self->context;
    ArduinoMQTT_Internal* internal = (ArduinoMQTT_Internal*) instance->itn_props;

    if (internal) {
        if (internal->m_mqttClient) delete (internal->m_mqttClient);
        if (internal->m_wifiClient) delete (internal->m_wifiClient);

        free(internal);
        instance->itn_props = NULL;
    }

    if (instance->m_messagePacket) {
        free(instance->m_messagePacket);
        instance->m_messagePacket = NULL;
    }
}

/* Constructor Zone */

void ArduinoMQTT_Constructor(FAF_Driver* self) {
    if (!self) return;

    self->vptr = (const FAF_Driver_VTable*) &arduino_mqtt_vtable;

    self->signature = DRIVER_SIGNATURE(ArduinoMQTT);
    self->init = iArduinoMQTT_init;
    self->dispose = iArduinoMQTT_dispose;
}

#endif