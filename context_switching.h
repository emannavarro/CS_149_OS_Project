#ifndef context_switching_H
#define context_switching_H
#include <vector>
#include <string>
#include "Classes.h"

// enum State{READY, RUNNING, BLOCKED};

// class Instruction {
// public:
// char op;
// int intArg;
// std::string strArg;
//  bool operator==(const Instruction& other) const {
//         return op == other.op &&
//                intArg == other.intArg &&
//                strArg == other.strArg;
//     }
// };

// class CPU {
// public:
//     std::vector<Instruction> *pProgram;
//     int programCounter;
//     int value;
//     int timeSlice;
//     int timeSliceUsed;
// };

// // class PcbBlock{
// // public:
// //     std::vector<Instruction> program;
// //     int processedTime; //== timeUsed
// //     int childID; //== processId
// //     int parentID;
// //     int programCounter;
// //     int userInteger; //== value
// //     int priority;
// //     State state;
// //     int startTime;
// // };

void context_switch_saving(int currentprocesspcbindex,CPU &cpu, PcbBlock PcbTable[]);
void context_switch_Loading(int nextprocesspcbindex,CPU &cpu, PcbBlock PcbTable[]);



#endif