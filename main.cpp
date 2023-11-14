#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/queue.h>
#include <stdbool.h>
#include <iostream>

#define READ_FD 0
#define WRITE_FD 1

using namespace std;

int time;
enum state{READY, RUNNING, BLOCKED};
//implement queue CPU

typedef struct {
    int time;
    int childID;
    int parentID;
    int* programCounter;
    int userInteger;
    int priority;
    enum state state;
    int startTime;
    int cpuTime;
} PcbBlock;

PcbBlock PcbTable[20];

//The state arrays store indexes of PcbTable
int ReadyState[20];
int BlockedState[20];
int RunningState[1];

int main(){
    int pip[2];
    pid_t processManagerPID;
    if(pipe(pip) == -1) {
        perror("Failed to create pipe\n");
        exit(1);
    }
    processManagerPID = fork();
    if(processManagerPID == 0) { //We are in process manager
        //Perform simulation
    }

    wait(NULL); //Wait for the simulation to end before exiting the program.
    // while(true){
    //     char userInput;
    //     printf("Please enter one of the commands: Q, U, P, T. \n");
    //     scanf("%c", userInput);
    //     switch(userInput){
    //         case 'Q': 
    //             //Start Simulated code
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
    return 0;
}



