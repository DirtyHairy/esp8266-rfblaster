#ifndef GRATUITOUS_ARP_TASK
#define GRATUITOUS_ARP_TASK

#include <Scheduler.h>

class GratuitousARPTask: public Task {
    public:

        virtual void loop();

        static GratuitousARPTask& instance();

    private:

        GratuitousARPTask();

    private:

        uint32_t uptimeSeconds;
        unsigned long timestamp;
        unsigned long delta;

    private:

        GratuitousARPTask(const GratuitousARPTask&) = delete;
        GratuitousARPTask(GratuitousARPTask&&) = delete;

        GratuitousARPTask& operator=(const GratuitousARPTask&) = delete;
        GratuitousARPTask& operator=(GratuitousARPTask&&) = delete;
};

#endif // GRATUITOUS_ARP_TASK
