#ifndef RC_COMMAND_TASK
#define RC_COMMAND_TASK

#include <Scheduler.h>

#include "RCCommandQueueInterface.hpp"

class RCCommandTask: public Task {
    public:

        virtual void loop();

        virtual bool shouldRun();

        static RCCommandTask& instance(RCCommandQueueInterface&);

    private:

        RCCommandTask(RCCommandQueueInterface& commandQueue): commandQueue(commandQueue) {}

    private:

        RCCommandQueueInterface& commandQueue;

    private:

        RCCommandTask() = delete;
        RCCommandTask(const RCCommandTask&) = delete;
        RCCommandTask(RCCommandTask&&) = delete;

        RCCommandTask& operator=(const RCCommandTask&) = delete;
        RCCommandTask& operator=(RCCommandTask&&) = delete;
};

#endif // RC_COMMAND_TASK>
