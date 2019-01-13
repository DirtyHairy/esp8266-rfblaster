#include "RCCommandTask.h"

void RCCommandTask::loop() {
    commandQueue.execute();
}

bool RCCommandTask::shouldRun() {
    if (commandQueue.empty()) return false;

    return Task::shouldRun();
}

RCCommandTask& RCCommandTask::instance(RCCommandQueueInterface& commandQueue) {
    static RCCommandTask instance(commandQueue);

    return instance;
}
