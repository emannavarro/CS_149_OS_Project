

#include "ProcessManager.h"
#include <cctype> // for toupper()
#include <cstdlib> // for EXIT_SUCCESS and EXIT_FAILURE
#include <cstring> // for strerror()
#include <cerrno> // for errno
#include <deque> // for deque (used for ready and blocked queues)
#include <fstream> // for ifstream (used for reading simulated programs)
#include <algorithm> // for find_if()
#include <iostream> // for cout, endl, and cin
#include <sstream> // for stringstream (used for parsing simulated programs)
#include <sys/wait.h> // for wait()
#include <unistd.h> // for pipe(), read(), write(), close(), fork(), and _exit()
#include <vector> // for vector (used for PCB table
#include <string>

using namespace std;

void set(int value) {
    cpu.value = value;
}

void add(int value) {
    cpu.value += value;
}

void decrement(int value) {
    cpu.value -= value;
}

// Performs scheduling.
void schedule()
{
    // TODO: Implement
    // 1. Return if there is still a processing running
    // (runningState != -1). There is no need to schedule if a process is already running (at least until iLab 3)
    // 2. Get a new process to run, if possible, from the ready queue.
    // 3. If we were able to get a new process to run:
    // a. Mark the processing as running (update the new process's PCB state)
    // b. Update the CPU structure with the PCB entry details
    // (program, program counter, value, etc.)

}

// Implements the B operation.
void block()
{
    // TODO: Implement
    // 1. Add the PCB index of the running process (stored in runningState) to the blocked queue.
    int idx = runningState[0];
    // 2. Update the process's PCB entry
    // a. Change the PCB's state to blocked.
    PcbTable[idx].state = BLOCKED;
    // b. Store the CPU program counter in the PCB's program
    //counter.
    PcbTable[idx].programCounter = cpu.programCounter;
    // c. Store the CPU's value in the PCB's value.
    PcbTable[idx].userInteger = cpu.value;
    // 3. Update the running state to -1 (basically mark no process as running). Note that a new process will be chosen to run later (via the
    // Q command code calling the schedule() function).
    runningState[0] = -1;
}

// Implements the E operation.
void end()
{
    // TODO: Implement
    // 1. Get the PCB entry of the running process.
    int idx = runningState[0];
    // 2. Update the cumulative time difference (increment it by timestamp + 1 - start time of the process).
    /*
        Not sure what is the use of the cumulative time difference
    */
    PcbTable[idx].processedTime = globalTime + 1 - PcbTable[idx].startTime;
    // 3. Increment the number of terminated processes.
    terminatedProcess++;
    // 4. Update the running state to -1 (basically mark no process as running). Note that a new process will be chosen to run later (via the Q command code calling the schedule function).
    runningState[0] = -1;
}

// Implements the F operation.
void fork(int value)
{
    // TODO: Implement
    // 1. Get a free PCB index (pcbTable.size())
    int idx = ++programIndexCounter;
    // 2. Get the PCB entry for the current running process.
    PcbBlock currProcess = PcbTable[idx-1];
    PcbBlock childProcess;
    // 3. Ensure the passed-in value is not out of bounds.
    if(programIndexCounter + value >= (sizeof(PcbTable) / sizeof(PcbBlock))) {
        cout << "Out of bound, unable to allocate memory" << endl;
        exit(1);
    }
    // 4. Populate the PCB entry obtained in #1
    // a. Set the process ID to the PCB index obtained in #1.
    childProcess.childID = idx;
    // b. Set the parent process ID to the process ID of the running process (use the running process's PCB entry to get this).
    childProcess.parentID = currProcess.childID;
    // c. Set the program counter to the cpu program counter.
    childProcess.programCounter = cpu.programCounter;
    // d. Set the value to the cpu value.
    childProcess.userInteger = cpu.value;
    // e. Set the priority to the same as the parent process's priority.
    childProcess.priority = currProcess.priority;
    // f. Set the state to the ready state.
    childProcess.state = READY;
    // g. Set the start time to the current timestamp
    childProcess.startTime = globalTime;
    // 5. Add the pcb index to the ready queue.
    readyState.push_back(idx);
    PcbTable[idx] = childProcess;
    // 6. Increment the cpu's program counter by the value read in #3
    cpu.programCounter += value; //Not sure if I am doing this correct
}

// Implements the R operation.
void replace(string &argument)
{
/*
    Not sure if this implementation is correct
*/

    // TODO: Implement
    // 1. Clear the CPU's program (cpu.pProgram->clear()).
    cpu.pProgram->clear();
    // 2. Use createProgram() to read in the filename specified by argument into the CPU (*cpu.pProgram)
    if (!createProgram(argument, PcbTable[programIndexCounter].program)) {
        cout << "Error opening " << argument << endl;
        cpu.programCounter++;
        return;
    }
    //  a. Consider what to do if createProgram fails. I printed an error, incremented the cpu program counter and then
    //  returned. Note that createProgram can fail if the file could not be opened or did not exist.
    // 3. Set the program counter to 0.
    PcbTable[programIndexCounter].programCounter = 0;

}

// Implements the Q command.
void quantum()
{
    Instruction instruction;
    cout << "In quantum" << endl;
    if (runningState[0] == -1) {
        cout << "No processes are running" << endl;
        ++globalTime;
        return;
    }
    if (cpu.programCounter < cpu.pProgram->size()) {
        instruction = (*cpu.pProgram)[cpu.programCounter];
        ++cpu.programCounter;
        cout << "Incremented program counter by 1" << endl;
    } else {
        cout << "End of program reached without E operation" << endl;
        instruction.op = 'E';
    }
    switch (instruction.op) {
        case 'S':
            set(instruction.intArg);
            cout << "instruction S " << instruction.intArg << endl;
            break;
        case 'A':
            add(instruction.intArg);
            cout << "instruction A " << instruction.intArg << endl;
            break;
        case 'D':
            decrement(instruction.intArg);
            break;
        case 'B':
            block();
            break;
        case 'E':
            end();
            break;
        case 'F':
            fork(instruction.intArg);
            break;
        case 'R':
            replace(instruction.strArg);
            break;
    }
    ++globalTime;
    
    //The PCBTable will need to be updated with the current PCBBlock object when context switching
    schedule();
}
// Implements the U command.
void unblock()
{
    // 1. If the blocked queue contains any processes:
    if(blockedState.empty()) {
        cout << "There are no processes that are blocked." << endl;
        return;
    }
    // a. Remove a process form the front of the blocked queue.
    int idx = blockedState.front();
    blockedState.pop_front();
    // b. Add the process to the ready queue.
    readyState.push_back(idx);
    // c. Change the state of the process to ready (update its PCB entry).
    PcbTable[idx].state = READY;
    // 2. Call the schedule() function to give an unblocked process a chance to run (if possible).
    schedule();
}
// Implements the P command.
void print()
{
    cout << "Print command is not implemented until iLab 3" << endl;
}

// Function that implements the process manager.
int runProcessManager(int fileDescriptor)
{
//vector<PcbEntry> pcbTable;
    // Attempt to create the init process.
    if (!createProgram("init", PcbTable[0].program)) {
        return EXIT_FAILURE;
    }
    PcbTable[0].childID = 0;
    PcbTable[0].parentID = -1;
    PcbTable[0].programCounter = 0;
    PcbTable[0].userInteger = 0;
    PcbTable[0].priority = 0;
    PcbTable[0].state = State::RUNNING;
    PcbTable[0].startTime = 0;
    PcbTable[0].processedTime = 0;
    runningState[0] = 0;

    cpu.pProgram = &(PcbTable[0].program);
    cpu.programCounter = PcbTable[0].programCounter;
    cpu.value = PcbTable[0].userInteger;
    terminatedProcess = 0;
    globalTime = 0;
    programIndexCounter = 0;
    double avgTurnaroundTime = 0;
    // Loop until a 'T' is read, then terminate.
    char ch;
    do {
        // Read a command character from the pipe.
        cout << "Read a command character from the pipe" << endl;
        if (read(fileDescriptor, &ch, sizeof(ch)) != sizeof(ch)) {
            // Assume the parent process exited, breaking the pipe.
            break;
        }
        //TODO: Write a switch statement
        switch (ch) {
            case 'Q':
                quantum();
                break;
            case 'U':
                //Implement the unblock()
                cout << "You entered U" << endl;
                unblock();
                break;
            case 'P':
                //Implement the print()
                cout << "You entered P" << endl;
                print();
                break;
            case 'T':
                cout << "Terminating. . ." << endl;
                print();
                break;
            default:
                cout << "You entered an invalid character!" << endl;
        }
    }while (ch != 'T');

    return EXIT_SUCCESS;
}


// Trim from start (in place)
static inline void ltrim(string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// Trim from end (in place)
static inline void rtrim(string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

string trim(const std::string &s) {
    size_t start = s.find_first_not_of(" \t\n\r\f\v");
    size_t end = s.find_last_not_of(" \t\n\r\f\v");

    return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
}


bool createProgram(const std::string &file_name, std::vector<Instruction> &pProgram) {
    ifstream file;
    int lineNum = 0;
    file.open(file_name.c_str());
    if (!file.is_open()) {
        cout << "Error opening file " << file_name << endl;
        return false;
    }
    while (file.good()) {
        string line;
        getline(file, line);
        trim(line);
        if (line.size() > 0) {
            Instruction instruction;
            instruction.op = toupper(line[0]);
            instruction.strArg = trim(line.erase(0, 1));
            instruction.intArg = atoi(instruction.strArg.c_str());
            stringstream argStream(instruction.strArg);
            switch (instruction.op) {
                case 'S': // Integer argument.
                    set(instruction.intArg);
                    cout << "Read S from createProgram, setting value " << instruction.intArg << endl;
                    break;
                case 'A': // Integer argument.
                    cout << "Read A from createProgram, adding value " << instruction.intArg << endl;
                    add(instruction.intArg);
                    break;
                case 'D': // Integer argument.
                    cout << "Read A from createProgram, adding value " << instruction.intArg << endl;
                    decrement(instruction.intArg);
                    break;
                case 'F': // Integer argument.
                    if (!(argStream >> instruction.intArg)) {
                        cout << file_name << ":" << lineNum
                             << " - Invalid integer argument "
                             << instruction.strArg << " for "
                             << instruction.op << " operation"
                             << endl;
                        file.close();
                        return false;
                    }
                    break;
                case 'B': // No argument.
                case 'E': // No argument.
                    break;
                case 'R': // String argument.
                    // Note that since the string is trimmed on bothends, file_name
                    // with leading or trailing whitespace (unlikely) will not work.
                    if (instruction.strArg.size() == 0) {
                        cout << file_name << ":" << lineNum << " - Missing string argument" << endl;
                        file.close();
                        return false;
                    }
                    break;
                default:
                    cout << file_name << ":" << lineNum << " - Invalid operation, " << instruction.op << endl;
                    file.close();
                    return false;
            }

            pProgram.push_back(instruction);

        }

        lineNum++;
    }
    file.close();

    return true;
}

// Add other necessary function implementations here...

