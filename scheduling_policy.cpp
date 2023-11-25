#include <iostream>
#include <queue>
#include "scheduling_policy.h"



using IntPair = std::pair<int, int>;

/*
Not tested and not complete 

*/

scheduling_policy::scheduling_policy()
{

 Priorityarray= new std::priority_queue<std::pair<int,int> , std::vector<std::pair<int,int> >, std::greater<std::pair<int,int> > > [4];

 delete[] Priorityarray;
}

scheduling_policy::~scheduling_policy()
{
    // Destructor, Freeing allocated memory
    delete[] Priorityarray; Priorityarray=0;
}
void scheduling_policy::schedule(int RunningState)
{
    // 1. Return if there is still a processing running (runningState != -1).
    // There is no need to schedule if a process is already running (at least until iLab 3)
  if (RunningState != -1){
    return;
  }

   // 2. Get a new process to run, if possible, from the ready queue.

 // TODO: Implement
 // 3. If we were able to get a new process to run:
 // a. Mark the processing as running (update the new process's PCB state)
 // b. Update the CPU structure with the PCB entry details (program, program counter,
 // value, etc.)

}

void scheduling_policy::block()
{

  return;
 // TODO: Implement
 // 1. Add the PCB index of the running process (stored invrunningState) to the blocked queue.
 // 2. Update the process's PCB entry
 // a. Change the PCB's state to blocked.
 // b. Store the CPU program counter in the PCB's programvvcounter.
 // c. Store the CPU's value in the PCB's value.
 // 3. Update the running state to -1 (basically mark no process asvr
 //unning). Note that a new process will be chosen to run later (via thevQ command code calling the schedule() function).
}
std::pair<int, int> scheduling_policy::update_ready_que()
{
  // Helper function that returns the next highest priority proccess next in line
  IntPair topPair;
  for(int i = 0 ; i < 4; ++i) {
    while (!Priorityarray[i].empty()) {
        topPair = Priorityarray[i].top();
        Priorityarray[i].pop(); // pop of the returning value b/c we don't know if we are going to be blocked or not
        return topPair;
    }
  }
}

void scheduling_policy::insert_highestPriorityQueue(int priority, int pcbindex)
{
  IntPair temp_pair;
  temp_pair.first = priority;
  temp_pair.second =pcbindex;
  Priorityarray[highestPriorityQueue].push(temp_pair);


}
void scheduling_policy::insert_secondHighestPriorityQueue(int priority, int pcbindex)
{
  IntPair temp_pair;
  temp_pair.first = priority;
  temp_pair.second =pcbindex;
  Priorityarray[secondHighestPriorityQueue].push(temp_pair);
  
}
void scheduling_policy::insert_thirdHighestPriorityQueue(int priority, int pcbindex)
{
  IntPair temp_pair;
  temp_pair.first = priority;
  temp_pair.second =pcbindex;
  Priorityarray[thirdHighestPriorityQueue].push(temp_pair);
}
void scheduling_policy::insert_lowestPriorityQueue(int priority, int pcbindex)
{
  IntPair temp_pair;
  temp_pair.first = priority;
  temp_pair.second =pcbindex;
  Priorityarray[lowestPriorityQueue].push(temp_pair);

}

/*
main just a place holder used for debugging and compiling

*/




int main(){


std::cout<<"hello Emanuel"<<std::endl;

return 0;


}
