#include "FAF/drivers/esp32/arduino/mqtt/ArduinoMQTT_API.h"
#include "FAF/drivers/esp32/arduino/mqtt/ArduinoMQTT_Class.h"
#include "FAF/drivers/esp32/arduino/mqtt/ArduinoMQTT_Conf.h"

#ifdef ARDUINO_ARCH_ESP32

#include <cstdlib>
#include <cstring>

#include <WiFiClient.h>
#include <PubSubClient.h>

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

void ArduinoMQTT_Constructor(FAF_Driver* self) {
    if (!self) return;

    self->signature = DRIVER_SIGNATURE(ArduinoMQTT);
    self->init = iArduinoMQTT_init;
    self->dispose = iArduinoMQTT_dispose;
}

int ArduinoMQTT_Class_Connect(FAF_Driver* self) {
    if (!self || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(ArduinoMQTT))) return 0;

    ArduinoMQTT_Class* cls = (ArduinoMQTT_Class*) self;
    IConnectable* connectable = &cls->c_connectable;
    if (!connectable->connect) return 0;

    return connectable->connect(self);
}

int ArduinoMQTT_Class_Disconnect(FAF_Driver* self) {
    if (!self || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(ArduinoMQTT))) return 0;

    ArduinoMQTT_Class* cls = (ArduinoMQTT_Class*) self;
    IConnectable* connectable = &cls->c_connectable;
    if (!connectable->disconnect) return 0;

    return connectable->disconnect(self);
}

int ArduinoMQTT_Class_Publish(FAF_Driver* self, const char* topic, const char* payload) {
    if (!self || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(ArduinoMQTT))) return 0;

    ArduinoMQTT_Class* cls = (ArduinoMQTT_Class*) self;
    if (!cls->publish) return 0;
    
    return cls->publish(self, topic, payload);
}

int ArduinoMQTT_Class_Subscribe(FAF_Driver* self, const char* topic) {
    if (!self || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(ArduinoMQTT))) return 0;

    ArduinoMQTT_Class* cls = (ArduinoMQTT_Class*) self;
    if (!cls->subscribe) return 0;
    
    return cls->subscribe(self, topic);
}

void ArduinoMQTT_Class_Listen(FAF_Driver* self) {
    if (!self || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(ArduinoMQTT))) return;

    ArduinoMQTT_Class* cls = (ArduinoMQTT_Class*) self;
    if (!cls->listen) return;
    
    return cls->listen(self);
}

int ArduinoMQTT_Class_Message_IsReady(FAF_Driver* self) {
    if (!self || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(ArduinoMQTT))) return 0;

    FAF_Driver_Instance* context = self->context;
    if (!context || !VALIDATE_DRIVER_SIGNATURE(context, DRIVER_SIGNATURE(ArduinoMQTT))) return 0;

    ArduinoMQTT_Instance* instance = (ArduinoMQTT_Instance*) self->context;
    
    return instance->m_messageBusy;
}

void ArduinoMQTT_Class_Message_Read(FAF_Driver* self, FAF_MQTT_Packet* out) {
    if (!self || !out || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(ArduinoMQTT))) return;

    FAF_Driver_Instance* context = self->context;
    if (!context || !VALIDATE_DRIVER_SIGNATURE(context, DRIVER_SIGNATURE(ArduinoMQTT))) return;

    ArduinoMQTT_Instance* instance = (ArduinoMQTT_Instance*) self->context;
    FAF_MQTT_Packet* packet = static_cast<FAF_MQTT_Packet*>(instance->m_messagePacket);
    if (!packet) return;

    memcpy(out, packet, sizeof(FAF_MQTT_Packet));
}

void ArduinoMQTT_Class_Message_Flush(FAF_Driver* self) {
    if (!self || !VALIDATE_DRIVER_SIGNATURE(self, DRIVER_SIGNATURE(ArduinoMQTT))) return;

    FAF_Driver_Instance* context = self->context;
    if (!context || !VALIDATE_DRIVER_SIGNATURE(context, DRIVER_SIGNATURE(ArduinoMQTT))) return;

    ArduinoMQTT_Instance* instance = (ArduinoMQTT_Instance*) self->context;
    instance->m_messageBusy = 0;
}

#endif