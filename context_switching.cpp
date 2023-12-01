#include <vector>
#include <string>
#include <cassert>
#include <iostream>
#include "context_switching.h"


void context_switch_saving(int currentprocesspcbindex,CPU &cpu,PcbBlock PcbTable[] ){

    // Saving values of current proccess in the PCB
    PcbTable[currentprocesspcbindex].programCounter = cpu.programCounter;
    PcbTable[currentprocesspcbindex].userInteger = cpu.value;
    PcbTable[currentprocesspcbindex].processedTime = cpu.timeSliceUsed;
    PcbTable[currentprocesspcbindex].state = BLOCKED;
}

void context_switch_Loading(int nextprocesspcbindex,CPU &cpu, PcbBlock PcbTable[] ){

    // Loading values of current proccess PCB into CPU
    *cpu.pProgram = PcbTable[nextprocesspcbindex].program;
    cpu.programCounter = PcbTable[nextprocesspcbindex].programCounter;
    cpu.value = PcbTable[nextprocesspcbindex].userInteger;
    cpu.timeSliceUsed = PcbTable[nextprocesspcbindex].processedTime;
    // Update PCB block next process as running
    PcbTable[nextprocesspcbindex].state = RUNNING;
}
