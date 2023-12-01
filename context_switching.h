#ifndef context_switching_H
#define context_switching_H
#include <vector>
#include <string>
#include "Classes.h"


void context_switch_saving(int currentprocesspcbindex, CPU &cpu, PcbBlock PcbTable[]);
void context_switch_Loading(int nextprocesspcbindex, CPU &cpu, PcbBlock PcbTable[]);


#endif