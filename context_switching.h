#ifndef context_switching_H
#define context_switching_H
#include <vector>
#include <string>

class Instruction {
public:
char operation;
int intArg;
std::string stringArg;
 bool operator==(const Instruction& other) const {
        return operation == other.operation &&
               intArg == other.intArg &&
               stringArg == other.stringArg;
    }
};

class Cpu {
public:
std::vector<Instruction> *pProgram;
int programCounter;
int value;
int timeSlice;
int timeSliceUsed;
};


enum State {
STATE_READY,
STATE_RUNNING,
STATE_BLOCKED
};
class PcbEntry {
public:
int processId;
int parentProcessId;
std::vector<Instruction> program;
unsigned int programCounter;
int value;
unsigned int priority;
State state;
unsigned int startTime;
unsigned int timeUsed;
};

void context_switch_saving(int currentprocesspcbindex,Cpu &cpu, PcbEntry PcbTable[]);
void context_switch_Loading(int nextprocesspcbindex,Cpu &cpu, PcbEntry PcbTable[]);



#endif