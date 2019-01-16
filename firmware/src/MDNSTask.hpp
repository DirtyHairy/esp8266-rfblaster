#ifndef MDNS_TASK_H
#define MDNS_TASK_H

#include <Scheduler.h>

class MDNSTask: public Task {
    public:

        virtual void loop();

        static MDNSTask& instance();

    private:

        MDNSTask();

    private:

        MDNSTask(const MDNSTask&) = delete;
        MDNSTask(MDNSTask&&) = delete;

        MDNSTask& operator=(const MDNSTask&) = delete;
        MDNSTask& operator=(MDNSTask&&) = delete;
};

#endif // MDNS_TASK_H
