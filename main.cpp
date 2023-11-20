


#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <queue>

#include "ProcessManager.h"
#include "Classes.h"

using namespace std;

#define READ_FD 0
#define WRITE_FD 1


int globalTime = 0;
//implement queue CPU


PcbBlock PcbTable[20];
CPU cpu;
deque<int> readyState;
deque<int> blockedState;

//The state arrays store indexes of PcbTable
int readyStateArray[20];
int blockedStateArray[20];
int runningState[1];

int main(int argc, char *argv[]){
    int pip[2];
    pid_t processManagerPID;
    int result;
    char input;
    if(pipe(pip) == -1) {
        perror("Failed to create pipe\n");
        exit(1);
    }
    processManagerPID = fork();
    if(processManagerPID == -1) {
        perror("Failed to create process manager\n");
        exit(1);
    }
    if(processManagerPID == 0) { //We are in process manager
        //Perform simulation
        cout << "In process manager process" << endl;
        close(pip[WRITE_FD]); //We are only reading in the process manager
        result = runProcessManager(pip[READ_FD]);
        close(pip[READ_FD]); //Clean up
        _exit(result);
    }
    else {
        do {
            cout << "Enter Q, P, U or T" << endl;
            cout << "$ ";
            cin >> input ;
            // Pass commands to the process manager process via the pipe.
            if (write(pip[WRITE_FD], &input, sizeof(input)) != sizeof(input))
            {
                // Assume the child process exited, breaking the pipe.
                break;
            }
        }
        while (input != 'T');
        write(pip[WRITE_FD], &input, sizeof(input));
        close(pip[WRITE_FD]);
        wait(&result);
        //     // printf("Please enter one of the commands: Q, U, P, T. \n");
        //     // scanf("%c", input);
        //     const char* userInput = input;
        //     switch(*userInput){
        //         case 'Q':
        //             //Start Simulated code
        //             printf("Q");
        //             break;
        //         case 'U':
        //             //Commander code
        //             break;
        //         case 'P':
        //             //Simulated code?
        //             break;
        //         case 'T':
        //             //Commander code
        //             break;
        //     }
        // }
    }
    // wait(NULL); //Wait for the simulation to end before exiting the program.


    return result;
}




