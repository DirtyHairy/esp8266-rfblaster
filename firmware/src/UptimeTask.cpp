#include <Arduino.h>

#include "UptimeTask.hpp"

UptimeTask::UptimeTask() :
    uptimeSeconds(0),
    timestamp(millis()),
    delta(0)
{}

void UptimeTask::loop() {
    delay(500);

    unsigned long newTimestamp = millis();
    unsigned long d = newTimestamp - timestamp + delta;

    if (d < 1000) return;

    uptimeSeconds += d / 1000;
    delta = d % 1000;

    timestamp = newTimestamp;
}

uint32_t UptimeTask::getUptimeSeconds() const {
    return uptimeSeconds;
}

UptimeTask& UptimeTask::instance() {
    static UptimeTask instance;

    return instance;
}
