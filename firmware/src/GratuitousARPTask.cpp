#include <lwip/netif.h>
#include <lwip/etharp.h>

#include "GratuitousARPTask.h"

GratuitousARPTask::GratuitousARPTask() {}

void GratuitousARPTask::loop() {
    netif *n = netif_list;

    while (n) {
        etharp_gratuitous(n);
        n = n->next;
    }

    delay(5000);
}

GratuitousARPTask& GratuitousARPTask::instance() {
    static GratuitousARPTask instance;

    return instance;
}
