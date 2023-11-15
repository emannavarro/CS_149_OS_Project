#ifndef CLASSES_H
#define CLASSES_H

#include <string>
#include <vector>
#include <iostream>

enum State{READY, RUNNING, BLOCKED};


class Instruction {
    public:
        char op;
        int intArg;
        std::string strArg;
};

class CPU {
    public:
        std::vector<Instruction> *pProgram;
        int programCounter;
        int value;
        int timeSlice;
        int timeSliceUsed;
};

class PcbBlock{
    public:
        std::vector<Instruction> program;
        int processedTime; //== timeUsed
        int childID; //== processId
        int parentID;
        int programCounter;
        int userInteger; //== value
        int priority;
        State state;
        int startTime;
};

#endif