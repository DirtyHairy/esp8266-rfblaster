#ifndef RC_COMMAND_H
#define RC_COMMAND_H

struct RCCommand {
    RCCommand(uint32_t code, uint32_t codeLength) :
        code(code),
        codeLength(codeLength),
        protocol(1),
        pulseLength(0),
        repeat(10)
    {}

    RCCommand() {}

    uint32_t code;
    uint32_t codeLength;
    uint32_t protocol;
    uint32_t pulseLength;
    uint32_t repeat;
};

#endif // RC_COMMAND_H
