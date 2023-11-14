#include <iostream>
using namespace std;

#include <stdio.h>
#include <unistd.h>
// #include <stdlib.h>
// #include <sys/queue.h>
// #include <stdbool.h>
#include <iostream>

#define READ_FD 0
#define WRITE_FD 1


int globalTime;
enum state{READY, RUNNING, BLOCKED};
//implement queue CPU

typedef struct {
    int processTime;
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
    char* input = " ";
    while(input != "T") {
        close(pip[READ_FD]); //Only writing to process manager
        scanf("%s", input);
        write(pip[WRITE_FD], &input, 1);
        if(input == "T") { //Exiting the loop, so we can close the write pipe
            close(pip[WRITE_FD]); 
        }
        sleep(1); //One command per second
    }
    if(processManagerPID == -1) {
        perror("Failed to create process manager\n");
        exit(1);
    }
    if(processManagerPID == 0) { //We are in process manager
        //Perform simulation
        close(pip[WRITE_FD]); //We are only reading in the process manager
        while(input != "T"){
            read(pip[READ_FD], &input, 7);

            // printf("Please enter one of the commands: Q, U, P, T. \n");
            // scanf("%c", input);
            const char* userInput = input; 
            switch(*userInput){
                case 'Q': 
                    //Start Simulated code
                    printf("Q");
                    break;
                case 'U':
                    //Commander code
                    break;
                case 'P':
                    //Simulated code?
                    break;
                case 'T':
                    //Commander code
                    break;
            }    
        }
    }
    wait(NULL); //Wait for the simulation to end before exiting the program.

    
    return 0;
}



