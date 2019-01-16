#include <Arduino.h>
#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <Scheduler.h>

#include "RCCommandTask.hpp"
#include "RCCommandQueue.hpp"
#include "UptimeTask.hpp"
#include "WebServer.hpp"
#include "MDNSTask.hpp"

#include "LocalSettings.h"
#include "Settings.h"

void setup()
{
    ArduinoOTA.begin();

    Serial.begin(9600);
    Serial.printf_P(PSTR("\nup and running...\n"));

    Serial.print(F("connecting to "));
    Serial.println(WIFI_SSID);

    WiFi.hostname(HOSTNAME);
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PSK);

    while (!WiFi.waitForConnectResult() || WiFi.localIP() == static_cast<uint32_t>(0))
    {
        Serial.println(F("wifi connection failed"));
        delay(1000);
    }

    Serial.print(F("connected, IP: "));
    Serial.println(WiFi.localIP());

    Serial.print(F("hostname: "));
    Serial.println(WiFi.hostname());

    if (!MDNS.begin(HOSTNAME))
    {
        Serial.println(F("MDNS failed"));
    }

    Serial.print(F("MDNS advertising as "));
    Serial.println(HOSTNAME);

    RCSwitch swtch;
    swtch.enableTransmit(RC_TRANSMIT_PIN);
    RCCommandQueue<COMMAND_QUEUE_LENGTH> commandQueue(swtch);

    WebServer server(commandQueue, UptimeTask::instance());
    server.start();

    Serial.println(F("Server running on port 80"));

    Scheduler.start(&RCCommandTask::instance(commandQueue));
    Scheduler.start(&UptimeTask::instance());
    Scheduler.start(&MDNSTask::instance());

    Scheduler.begin();
}

void loop() {}
