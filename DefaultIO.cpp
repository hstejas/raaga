#include <iostream>
#include "DefaultIO.h"


const std::map<std::string, Instruction> ConsoleIO::_instructionMap = 
{
    {"play", Instruction::PLAY}, 
    {"pause", Instruction::PAUSE}, 
    {"stop", Instruction::STOP}, 
    {"quit", Instruction::QUIT},
    {"+", Instruction::VOLUME_UP},   
    {"-", Instruction::VOLUME_DOWN},
    {"mute", Instruction::MUTE},
    {"next", Instruction::NEXT},
    {"prev", Instruction::PREVIOUS}
};
    
const std::map<State, std::string> ConsoleIO::_stateMap = 
{
    {State::PLAYING, "playing"},
    {State::PAUSED, "paused...."},
    {State::STOPPED, "stopped"},
    {State::QUITTING, "Bye :)"},
    {State::VOLUME_SET, "Volume set"},
    {State::MUTE, "toggled mute"},
    {State::ERROR, "error"}
};

Instruction ConsoleIO::getInstruction()
{
    std::string in;
    std::cout << ">> ";
    if(std::getline(std::cin,in) );
    {
        std::map<std::string, Instruction>::const_iterator ci = _instructionMap.find(in);
        if(ci != _instructionMap.end())
        {
            return ci->second;
        }
    }
    return Instruction::STOP;
}

void ConsoleIO::sendState(const State& state)
{
    std::cout << _stateMap.find(state)->second << std::endl;
}
