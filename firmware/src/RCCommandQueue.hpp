#ifndef RC_COMMAND_QUEUE_H
#define RC_COMMAND_QUEUE_H

#include <Arduino.h>
#include <RCSwitch.h>

#include "SimpleQueue.hpp"
#include "RCCommand.hpp"
#include "RCCommandQueueInterface.hpp"

template <unsigned int size> class RCCommandQueue: public RCCommandQueueInterface {
    public:

        RCCommandQueue(RCSwitch& swtch) : swtch(swtch) {}

        virtual bool push(RCCommand& command) {
            return queue.push(command);
        }

        virtual void execute() {
            RCCommand command;
            if (!queue.pop(command)) return;

            Serial.printf(
                "sending RC command; code = %ul, length = %ul, protocol = %ul, repeat = %ul, pulse length = %ul\n",
                command.code,
                command.codeLength,
                command.protocol,
                command.repeat,
                command.pulseLength
            );

            swtch.setProtocol(command.protocol);
            if (command.pulseLength > 0) swtch.setPulseLength(command.pulseLength);
            swtch.setRepeatTransmit(command.repeat);
            swtch.send(command.code, command.codeLength);
        }

        virtual bool empty() {
            return (queue.getLength() == 0);
        }

    private:

        SimpleQueue<size, RCCommand> queue;

        RCSwitch& swtch;

        RCSwitch::Protocol protocol;

    private:

        RCCommandQueue() = delete;
        RCCommandQueue(const RCCommandQueue&) = delete;
        RCCommandQueue(RCCommandQueue&&) = delete;

        RCCommandQueue& operator=(const RCCommandQueue&&) = delete;
        RCCommandQueue& operator=(RCCommandQueue&&) = delete;
};

#endif // RC_COMMAND_QUEUE_H
