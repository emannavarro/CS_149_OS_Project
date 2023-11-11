#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/queue.h>
#include <stdbool.h>

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
    while(true){
        char userInput;
        printf("Please enter one of the commands: Q, U, P, T. \n");
        scanf("%c", userInput);
        switch(userInput){
            case 'Q': 
                //Start Simulated code
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
    return 0;
}



