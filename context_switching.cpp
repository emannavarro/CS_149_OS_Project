#include <vector>
#include <string>
#include <cassert>
#include <iostream>
#include "context_switching.h"


void context_switch_saving(int currentprocesspcbindex,Cpu &cpu,PcbEntry PcbTable[] ){

    // Saving values of current proccess in the PCB
    PcbTable[currentprocesspcbindex].programCounter = cpu.programCounter;
    PcbTable[currentprocesspcbindex].value = cpu.value;
    PcbTable[currentprocesspcbindex].timeUsed = cpu.timeSliceUsed;
    PcbTable[currentprocesspcbindex].state = STATE_BLOCKED;
}

void context_switch_Loading(int nextprocesspcbindex,Cpu &cpu, PcbEntry PcbTable[] ){

    // Loading values of current proccess PCB into CPU 
    *cpu.pProgram = PcbTable[nextprocesspcbindex].program;
    cpu.programCounter = PcbTable[nextprocesspcbindex].programCounter;
    cpu.value = PcbTable[nextprocesspcbindex].value;
    cpu.timeSliceUsed = PcbTable[nextprocesspcbindex].timeUsed;
    // Update PCB block next process as running
    PcbTable[nextprocesspcbindex].state = STATE_RUNNING;

}
