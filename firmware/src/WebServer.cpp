#include <functional>

#include "WebServer.hpp"

using namespace std::placeholders;

WebServer::WebServer() : server(80) {}

void WebServer::start() {
    SPIFFS.begin();

    server.onNotFound(std::bind(&WebServer::handleNotFound, this, _1));

    server.begin();
}

void WebServer::internalServerError(AsyncWebServerRequest *request, const char* message) {
    request->send(500, "text/plain", message);
}

void WebServer::handleNotFound(AsyncWebServerRequest *request) {
    AsyncWebServerResponse* response = request->beginResponse(SPIFFS, "/www/not_found.html", "text/html");
    if (!response) return internalServerError(request, "file not found");

    response->addHeader("Cache-Control", "max-age=3600");
    response->setCode(404);

    request->send(response);
}
