#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H
#include <vector>
#include <strings.h>

#include "Classes.h"


bool createProgram(const std::string, std::vector<Instruction>);
int runProcessManager(int fd);

#endif