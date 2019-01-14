#ifndef UPTIME_TASK_H
#define UPTIME_TASK_H

#include <Scheduler.h>

class UptimeTask: public Task {
    public:

        virtual void loop();

        uint32_t getUptimeSeconds() const;

        static UptimeTask& instance();

    private:

        UptimeTask();

    private:

        uint32_t uptimeSeconds;
        unsigned long timestamp;
        unsigned long delta;

    private:

        UptimeTask(const UptimeTask&) = delete;
        UptimeTask(UptimeTask&&) = delete;

        UptimeTask& operator=(const UptimeTask&) = delete;
        UptimeTask& operator=(UptimeTask&&) = delete;
};

#endif // UPTIME_TASK
