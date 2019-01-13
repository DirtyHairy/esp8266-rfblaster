#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <Hash.h>
#include <Scheduler.h>

#include "RCCommandTask.h"
#include "RCCommandQueue.h"
#include "LocalSettings.h"
#include "Settings.h"

void setup()
{
    Serial.begin(9600);

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PSK);

    if (!WiFi.waitForConnectResult() || WiFi.localIP() == static_cast<uint32_t>(0))
    {
        Serial.println("wifi connection failed");
        return;
    }

    Serial.print("connected, IP: ");
    Serial.println(WiFi.localIP());

    if (!MDNS.begin(MDNS_NAME))
    {
        Serial.println("MDNS failed");
    }

    Serial.print("MDNS started as ");
    Serial.println(MDNS_NAME);

    RCSwitch swtch;
    swtch.enableTransmit(RC_TRANSMIT_PIN);
    RCCommandQueue<COMMAND_QUEUE_LENGTH> commandQueue(swtch);

    Scheduler.start(&RCCommandTask::instance(commandQueue));

    Scheduler.begin();
}

void loop() {}
