#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <ESPAsyncWebServer.h>

class WebServer {
    public:

        WebServer();

        void start();

    private:

        void handleNotFound(AsyncWebServerRequest *request);

        void internalServerError(AsyncWebServerRequest *request, const char* message = "");

    private:

        AsyncWebServer server;

    private:

        WebServer(const WebServer&) = delete;
        WebServer(WebServer&&) = delete;

        WebServer& operator=(const WebServer&) = delete;
        WebServer& operator=(WebServer&&) = delete;
};

#endif // WEB_SERVER_H
