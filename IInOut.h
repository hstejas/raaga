#ifndef RAAGA_INPUT_OUTPUT_INTERFACE_H
#define RAAGA_INPUT_OUTPUT_INTERFACE_H

enum class Instruction
{
    PLAY = 1,
    PAUSE,
    STOP,
    QUIT,
    VOLUME_UP,
    VOLUME_DOWN,
    MUTE,
    NEXT,
    PREVIOUS,
    ERROR
};

enum class State
{
    PLAYING = 1,
    PAUSED,
    STOPPED,
    QUITTING,
    VOLUME_SET,
    MUTE,
    ERROR
};

class IInOut
{
public:
    virtual Instruction getInstruction() = 0;
    virtual void sendState(const State&) = 0;
    virtual ~IInOut(){}
};



#endif //RAAGA_INPUT_OUTPUT_INTERFACE_H