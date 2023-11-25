#include <vector>
#include <string>

class Cpu {
public:
std::vector<Instruction> *pProgram;
int programCounter;
int value;
int timeSlice;
int timeSliceUsed;
};

class Instruction {
public:
char operation;
int intArg;
std::string stringArg;
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