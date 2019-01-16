#include <ESP8266mDNS.h>

#include "MDNSTask.hpp"

MDNSTask::MDNSTask() {}

void MDNSTask::loop() {
    MDNS.update();
}

MDNSTask& MDNSTask::instance() {
    static MDNSTask instance;

    return instance;
}
