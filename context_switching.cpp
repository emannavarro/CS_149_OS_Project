#include <vector>
#include <string>
#include <cassert>
#include <iostream>
#include "context_switching.h"


/*
   Save the context of the current process in the PCB.
   
   Parameters:
   - currentprocesspcbindex: The index of the current process in the PCB table.
   - cpu: Reference to the CPU object.
   - PcbTable: An array representing the PCB table containing process information.
*/

void context_switch_saving(int currentprocesspcbindex,CPU &cpu,PcbBlock PcbTable[] ){

    // Saving values of current proccess in the PCB

    PcbTable[currentprocesspcbindex].programCounter = cpu.programCounter;
    PcbTable[currentprocesspcbindex].userInteger = cpu.value;
    PcbTable[currentprocesspcbindex].processedTime = cpu.timeSliceUsed;
    PcbTable[currentprocesspcbindex].state = READY;
}
/*
   Save the context of the current process in the PCB for a blocked operation.
   
   Parameters:
   - currentprocesspcbindex: The index of the current process in the PCB table.
   - cpu: Reference to the CPU object.
   - PcbTable: An array representing the PCB table containing process information.
*/
void context_switch_saving_for_blocked_operation(int currentprocesspcbindex,CPU &cpu,PcbBlock PcbTable[] ){

    // Saving values of current proccess in the PCB

    PcbTable[currentprocesspcbindex].programCounter = cpu.programCounter;
    PcbTable[currentprocesspcbindex].userInteger = cpu.value;
    PcbTable[currentprocesspcbindex].processedTime = cpu.timeSliceUsed;
    PcbTable[currentprocesspcbindex].state = BLOCKED;
}
/*
   Load the context of the next process into the CPU.
   
   Parameters:
   - nextprocesspcbindex: The index of the next process in the PCB table.
   - cpu: Reference to the CPU object.
   - PcbTable: An array representing the PCB table containing process information.
*/
void context_switch_Loading(int nextprocesspcbindex,CPU &cpu, PcbBlock PcbTable[] ){
    
    int newtimeslice;
    if( PcbTable[nextprocesspcbindex].priority == 0 )
    {
        newtimeslice = 1;
    }
    else if( PcbTable[nextprocesspcbindex].priority ==1)
    {
        newtimeslice = 2;
    }
    else if( PcbTable[nextprocesspcbindex].priority ==2 )
    {
        newtimeslice = 4;
    }
    else if( PcbTable[nextprocesspcbindex].priority == 3 )
    {
        newtimeslice = 8;
    }


    // Loading values of current proccess PCB into CPU
    *cpu.pProgram = PcbTable[nextprocesspcbindex].program;
    cpu.programCounter = PcbTable[nextprocesspcbindex].programCounter;
    cpu.value = PcbTable[nextprocesspcbindex].userInteger;
    cpu.timeSliceUsed = 0; // time slice is initlized to zero b/c it just got ahold of the CPU
    cpu.timeSlice = newtimeslice; // initilize its timeslice,"Burst" , depending on its priority 
    // Update PCB block next process as running
    PcbTable[nextprocesspcbindex].state = RUNNING;
}
