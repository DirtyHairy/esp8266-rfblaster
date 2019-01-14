#include <functional>
#include <ESPAsyncWebServer.h>
#include <AsyncJson.h>

#include "WebServer.hpp"
#include "RCCommand.hpp"
#include "LocalSettings.h"

using namespace std::placeholders;
using std::bind;

WebServer::WebServer(RCCommandQueueInterface& commandQueue, UptimeTask& uptimeTask) :
    server(80),
    commandQueue(commandQueue),
    uptimeTask(uptimeTask)
{}

void WebServer::start() {
    SPIFFS.begin();

    server.on("/command/send", bind(&WebServer::handleCommandSend, this, _1))
        .setFilter(bind(&WebServer::filterHTTPMethod, this, _1, HTTP_POST));

    server.on("/status", bind(&WebServer::handleStatus, this, _1))
        .setFilter(bind(&WebServer::filterHTTPMethod, this, _1, HTTP_GET));

    server.onNotFound(bind(&WebServer::handleNotFound, this, _1));

    server.begin();
}

bool WebServer::filterHTTPMethod(AsyncWebServerRequest *request, WebRequestMethodComposite method) {
    return request->method() == method;
}

void WebServer::internalServerError(AsyncWebServerRequest *request, String message) {
    request->send(500, F("text/plain"), message);
}

void WebServer::jsonError(AsyncWebServerRequest *request, unsigned int code, String message) {
    AsyncJsonResponse *response = new AsyncJsonResponse();
    JsonObject& root = response->getRoot();

    root[F("message")] = message;

    response->setCode(code);
    response->addHeader(F("Cache-Control"), F("no-cache"));

    response->setLength();
    request->send(response);
}

void WebServer::badRequest(AsyncWebServerRequest *request, String message) {
    jsonError(request, 400, message);
}

void WebServer::handleNotFound(AsyncWebServerRequest *request) {
    AsyncWebServerResponse* response = request->beginResponse(SPIFFS, F("/www/not_found.html"), F("text/html"));
    if (!response) return internalServerError(request, F("file not found"));

    response->addHeader(F("Cache-Control"), F("max-age=3600"));
    response->setCode(404);

    request->send(response);
}

void WebServer::handleCommandSend(AsyncWebServerRequest *request) {
    AsyncWebParameter* param;

    param = request->getParam(F("code"));
    if (!param) return badRequest(request, F("missing parameter \"code\""));

    int code = param->value().toInt();
    if (code <= 0) return badRequest(request, F("bad code"));

    param = request->getParam(F("code-length"));
    if (!param) return badRequest(request, F("missing parameter \"code-length\""));

    int codeLength = param->value().toInt();
    if (codeLength <= 0) return badRequest(request, F("bad code length"));

    RCCommand command(code, codeLength);

    param = request->getParam(F("protocol"));
    if (param) {
        int protocol = param->value().toInt();
        if (protocol <= 0) return badRequest(request, F("bad protocol"));

        command.protocol = protocol;
    }

    param = request->getParam(F("repeat"));
    if (param) {
        int repeat = param->value().toInt();
        if (repeat <= 0) return badRequest(request, F("bad repeat count"));

        command.repeat = repeat;
    }

    param = request->getParam(F("pulse-length"));
    if (param) {
        int pulseLength = param->value().toInt();
        if (pulseLength <= 0) return badRequest(request, F("bad pulse length"));

        command.pulseLength = pulseLength;
    }

    Serial.printf_P(
        PSTR("received RC command; code = %ul, length = %ul, protocol = %ul, repeat = %ul, pulse length = %ul\n"),
        command.code,
        command.codeLength,
        command.protocol,
        command.repeat,
        command.pulseLength
    );

    if (commandQueue.push(command)) request->send(200, F("text/plain"));
    else jsonError(request, 503, F("too many enqueued commands, retry later"));
}

void WebServer::handleStatus(AsyncWebServerRequest* request) {
    AsyncJsonResponse *response = new AsyncJsonResponse();
    JsonObject& root = response->getRoot();

    root[F("name")] = MDNS_NAME;
    root[F("ssid")] = WIFI_SSID;
    root[F("uptimeSeconds")] = uptimeTask.getUptimeSeconds();
    root[F("freeHeap")] = ESP.getFreeHeap();
    root[F("sdk")] = ESP.getFullVersion();

    response->setCode(200);
    response->addHeader(F("Cache-Control"), F("no-cache"));

    response->setLength();
    request->send(response);
}
