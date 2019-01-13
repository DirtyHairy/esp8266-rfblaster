#ifndef RC_COMMAND_QUEUE_INTERFACE_H
#define RC_COMMAND_QUEUE_INTERFACE_H

#include "RCCommand.h"

class RCCommandQueueInterface {
    public:

        virtual bool push(RCCommand&) = 0;

        virtual void execute() = 0;

        virtual bool empty() = 0;
};

#endif // RC_COMMAND_QUEUE_INTERFACE_H
