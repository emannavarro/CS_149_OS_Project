#include <vector>
#include <string>
#include <iostream>
#include <cassert>

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


void context_switch_saving(int currentprocesspcbindex,Cpu &cpu ){

    // Saving values of current proccess in the PCB
    PcbTable[currentprocesspcbindex].programCounter = cpu.programCounter;
    PcbTable[currentprocesspcbindex].value = cpu.value;
    PcbTable[currentprocesspcbindex].timeUsed =cpu.timeSliceUsed;
}

void context_switch_Loading(int nextprocesspcbindex,Cpu &cpu ){

    // Loading values of current proccess PCB into CPU 
    *cpu.pProgram = PcbTable[nextprocesspcbindex].program;
    cpu.programCounter = PcbTable[nextprocesspcbindex].programCounter;
    cpu.value = PcbTable[nextprocesspcbindex].value;
    cpu.timeSliceUsed = PcbTable[nextprocesspcbindex].timeUsed;
}

// Simple assertion macro

    void SetUp() {
        // Initialize PcbTable with PCB entries for testing
        for (int i = 0; i < 20; ++i) {
            PcbTable[i].processId = i;
            PcbTable[i].parentProcessId = i + 1;
            // Initialize other fields as needed for testing
        }
    }

// Test context_switch_saving function
int testContextSwitchSaving() {
    Cpu cpu;
    cpu.pProgram = &PcbTable[0].program;
    cpu.programCounter = 42;
    cpu.value = 123;
    cpu.timeSliceUsed = 5;

    // Perform a context switch saving
    context_switch_saving(0, cpu);

    // Verify that the values in PcbTable are updated correctly
    assert(PcbTable[0].programCounter == 42);
    assert(PcbTable[0].value == 123);
    assert(PcbTable[0].timeUsed == 5);

    return 0;
}

PcbEntry PcbTable[20];
// Test context_switch_Loading function
int testContextSwitchLoading() {
    Cpu cpu;
    cpu.pProgram = &PcbTable[1].program;

    // Initialize PcbTable with values
    PcbTable[1].programCounter = 55;
    PcbTable[1].value = 987;
    PcbTable[1].timeUsed = 8;

    // Perform a context switch loading
    context_switch_Loading(1, cpu);

    // Verify that the CPU values are updated correctly
    assert(*cpu.pProgram == PcbTable[1].program);
    assert(cpu.programCounter == 55);
    assert(cpu.value == 987);
    assert(cpu.timeSliceUsed == 8);

    return 0;
}

int main() {

    SetUp();

    int result = 0;
    result += testContextSwitchSaving();
    result += testContextSwitchLoading();

    if (result == 0) {
        std::cout << "All tests passed successfully." << std::endl;
    } else {
        std::cerr << "Some tests failed." << std::endl;
    }

    return result;
}

