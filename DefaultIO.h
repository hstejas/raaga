#ifndef RAAGA_KEY_INPUT_H
#define RAAGA_KEY_INPUT_H

#include <string>
#include <map>
#include "IInOut.h"

class ConsoleIO : public IInOut
{
public:
    virtual Instruction getInstruction();
    virtual void sendState(const State&);
    virtual ~ConsoleIO(){}
    
protected:
    static const std::map<std::string, Instruction> _instructionMap;
    static const std::map<State, std::string> _stateMap;
};



#endif //RAAGA_KEY_INPUT_H