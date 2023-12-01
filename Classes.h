

#ifndef CLASSES_H
#define CLASSES_H

#include <string>
#include <vector>
#include <iostream>
#include <deque>


using namespace std;

enum State{READY, RUNNING, BLOCKED};

enum prioritylevel{
    highestPriorityQueue,
    secondHighestPriorityQueue,
    thirdHighestPriorityQueue,
    lowestPriorityQueue
};


class Instruction {


public:
    char op;
    int intArg;
    std::string strArg;
    bool operator==(const Instruction& other) const {
        return op == other.op &&
               intArg == other.intArg &&
               strArg == other.strArg;
    }
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
    int childID; //== childID
    int parentID;
    int programCounter;
    int userInteger; //== value
    int priority;
    State state;
    int startTime;
};



#endif


