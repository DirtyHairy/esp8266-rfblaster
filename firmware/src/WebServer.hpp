#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <ESPAsyncWebServer.h>

#include "RCCommandQueueInterface.hpp"
#include "UptimeTask.hpp"

class WebServer {
    public:

        WebServer(RCCommandQueueInterface& commandQueue, UptimeTask& uptimeTask);

        void start();

    private:

        void handleNotFound(AsyncWebServerRequest *request);

        void handleCommandSend(AsyncWebServerRequest *request);

        void handleStatus(AsyncWebServerRequest* request);

        void internalServerError(AsyncWebServerRequest *request, String message = "");

        void badRequest(AsyncWebServerRequest *request, String message = "");

        void jsonError(AsyncWebServerRequest *request, unsigned int code, String message = "");

        bool filterHTTPMethod(AsyncWebServerRequest *request, WebRequestMethodComposite);

    private:

        AsyncWebServer server;

        RCCommandQueueInterface& commandQueue;

        UptimeTask& uptimeTask;

    private:

        WebServer(const WebServer&) = delete;
        WebServer(WebServer&&) = delete;

        WebServer& operator=(const WebServer&) = delete;
        WebServer& operator=(WebServer&&) = delete;
};

#endif // WEB_SERVER_H
