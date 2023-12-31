

#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include "Classes.h"
#include <string>
#include <vector>
#include <deque>
#include <queue>

using namespace std;

extern CPU cpu;
extern int runningState;
extern queue<int> readyState[4];
extern deque<int> blockedState;
extern PcbBlock PcbTable[20];
extern int globalTime;
extern int programIndexCounter; //Keep track of which is the next available index
extern int terminatedProcess;
extern double avgTurnaroundTime;


// Function declarations
void set(int value);
void add(int value);
void decrement(int value);
void schedule();
void block();
void end();
void fork(int value);
void replace(const string& argument);
void quantum();
void unblock();
void print();
int runProcessManager(int fd);
bool createProgram(const string &file_name, vector<Instruction> &pProgram);

// Utility functions
string trim(const std::string &s);

#endif // PROCESSMANAGER_H
