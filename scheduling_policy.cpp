#include <iostream>
#include <queue>
#include <deque>
#include <utility>
#include <cassert>
#include "scheduling_policy.h"
#include <cstdlib> // for std::rand and std::srand
#include <ctime>   // for std::time
#include "Classes.h"

using namespace std;
/*
   Default constructor for scheduling_policy.
   Initializes the Priorityarray with an array of four priority queues.
   Each priority queue is a min-heap of pairs<int, int>, sorted in ascending order of the first element.
*/
scheduling_policy::scheduling_policy()
{

    Priorityarray = new priority_queue <pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > [4];
}

/*
   Destructor for scheduling_policy.
   Releases the allocated memory for Priorityarray to prevent memory leaks.
*/

scheduling_policy::~scheduling_policy()
{
    // Freeing the allocated memory for Priorityarray
    delete[] Priorityarray; 

    // Set Priorityarray pointer to nullptr to avoid potential dangling pointer issues
    Priorityarray = 0;
}

/*
   Overloaded constructor for scheduling_policy.
   Initializes the Priorityarray with an array of four priority queues, and populates them
   with elements from the provided vectors, distributed across the priority levels.
   
   Parameters:
   - highest_priority: Vector of pairs representing elements with the highest priority.
   - second_highest_priority: Vector of pairs representing elements with the second-highest priority.
   - third_highest_priority: Vector of pairs representing elements with the third-highest priority.
   - lowest_priority: Vector of pairs representing elements with the lowest priority.
*/
scheduling_policy::scheduling_policy(std::vector<std::pair< int, int> > &highest_priority,
                                    std::vector<std::pair< int, int> > &second_highest_priority,
                                     std::vector<std::pair< int, int> > &third_highest_priority,
                                     std::vector<std::pair< int, int> > &lowest_priority  )
                                     {

     // Populate priority queues with elements from the provided vectors
    Priorityarray = new std::priority_queue<std::pair<int,int> , std::vector<std::pair<int,int> >, std::greater<std::pair<int,int> > > [4];
    for(int i =0 ; i < highest_priority.size(); ++i)
    {
        Priorityarray[highestPriorityQueue].push(highest_priority.at(i));
    }
    for(int j = 0 ; j < second_highest_priority.size() ; ++j)
    {
        Priorityarray[secondHighestPriorityQueue].push(second_highest_priority.at(j));
    }
    for(int k = 0 ; k < third_highest_priority.size() ; ++k)
    {
        Priorityarray[thirdHighestPriorityQueue].push(third_highest_priority.at(k));
    }
    for(int l =0 ; l < lowest_priority.size() ; ++l )
    {
        Priorityarray[lowestPriorityQueue].push(lowest_priority.at(l));
    }



}
/*
   Insert a pair with the given priority and PCB index into the highest priority queue.
   
   Parameters:
   - priority: The priority of the PCB.
   - pcbindex: The index of the PCB.
*/
void scheduling_policy::insert_highestPriorityQueue(int priority, int pcbindex)
{
    std::pair<int,int> temp_pair;
    temp_pair.first = priority;
    temp_pair.second =pcbindex;
    Priorityarray[highestPriorityQueue].push(temp_pair);


}
/*
   Insert a pair with the given priority and PCB index into the second highest priority queue.
   
   Parameters:
   - priority: The priority of the PCB.
   - pcbindex: The index of the PCB.
*/
void scheduling_policy::insert_secondHighestPriorityQueue(int priority, int pcbindex)
{
    std::pair<int,int> temp_pair;
    temp_pair.first = priority;
    temp_pair.second =pcbindex;
    Priorityarray[secondHighestPriorityQueue].push(temp_pair);

}
/*
   Insert a pair with the given priority and PCB index into the third highest priority queue.
   
   Parameters:
   - priority: The priority of the PCB.
   - pcbindex: The index of the PCB.
*/
void scheduling_policy::insert_thirdHighestPriorityQueue(int priority, int pcbindex)
{
    std::pair<int,int> temp_pair;
    temp_pair.first = priority;
    temp_pair.second =pcbindex;
    Priorityarray[thirdHighestPriorityQueue].push(temp_pair);
}
/*
   Insert a pair with the given priority and PCB index into the lowest priority queue.
   
   Parameters:
   - priority: The priority of the PCB.
   - pcbindex: The index of the PCB.
*/
void scheduling_policy::insert_lowestPriorityQueue(int priority, int pcbindex)
{
    std::pair<int,int> temp_pair;
    temp_pair.first = priority;
    temp_pair.second =pcbindex;
    Priorityarray[lowestPriorityQueue].push(temp_pair);

}
/*
   Lower the priority of a process in the scheduling policy.
   
   Parameters:
   - priority: The current priority of the process.
   - pcbindex: The index of the process in the PCB table.
   - PcbTable: An array representing the PCB table containing process information.
*/


void scheduling_policy::lower_priority(int priority, int pcbindex,PcbBlock PcbTable[])
{

    int temp_priority;
    if(priority != 3 )
    {
    temp_priority = priority -1;
    }
    else{
    temp_priority = priority;
    }

    PcbTable[pcbindex].priority=temp_priority;

    if(priority == 0)
    {
        insert_secondHighestPriorityQueue(temp_priority, pcbindex);
    }
    else if(priority == 1)
    {
        insert_thirdHighestPriorityQueue(temp_priority, pcbindex);
    }
    else if(priority == 2)
    {
        insert_lowestPriorityQueue(temp_priority, pcbindex);
    }
    else if(priority == 3)
    {
        insert_lowestPriorityQueue(temp_priority, pcbindex);
    }
}
/*
   Raise the priority of a process in the scheduling policy.
   Without add the process back into the scheduling queues because the process is blocked
   
   Parameters:
   - priority: The current priority of the process.
   - pcbindex: The index of the process in the PCB table.
   - PcbTable: An array representing the PCB table containing process information.
*/
void scheduling_policy::raise_priority(int priority, int pcbindex, PcbBlock PcbTable[])
{
  int temp_priority;
    
    if(priority != 0 )
    {
    temp_priority = priority +1;
    }
    else{
    temp_priority = priority;
    }

    PcbTable[pcbindex].priority=temp_priority;

}

/*
   Schedule a new process to run on the CPU.
   
   Parameters:
   - RunningState: The index of the currently running process (-1 if no process is running).
   - currentprocesspcbindex: The index of the currently running process in the PCB table.
   - readyState: Reference to a deque representing the ready state containing process indices.
   - cpu: Reference to the CPU object.
   - PcbTable: An array representing the PCB table containing process information.
*/

void scheduling_policy::schedule(int RunningState,int currentprocesspcbindex , std::deque<int>& readyState, CPU &cpu ,PcbBlock PcbTable[] )
{
    // 1. Return if there is still a processing running (runningState != -1).
    // There is no need to schedule if a process is already running (at least until iLab 3)
    if (RunningState != -1){
        return;
    }

    // Insert new process into the ready que
    if(readyState.empty()){
        insert_into_ready_que(readyState);
    }

    int newprocessindex = readyState.at(0);

    readyState.pop_front();
    // lower the priority of the current process that will be preempted and it to be scheduled again by its new priority
    lower_priority(PcbTable[currentprocesspcbindex].priority, currentprocesspcbindex,PcbTable);
    // save the current running process in the PCB table
    context_switch_saving(currentprocesspcbindex,cpu,PcbTable);//grab the information from the CPU and PCBtable
    // Load the new process and set it to running
    context_switch_Loading(newprocessindex,cpu, PcbTable);
}

/*
   Schedule a new process to run on the CPU, while handling blocked state.
   
   Parameters:
   - RunningState: The index of the currently running process (-1 if no process is running).
   - currentprocesspcbindex: The index of the currently running process in the PCB table.
   - readyState: Reference to a deque representing the ready state containing process indices.
   - blockedState: Reference to a deque representing the blocked state containing process indices.
   - cpu: Reference to the CPU object.
   - PcbTable: An array representing the PCB table containing process information.
*/


void scheduling_policy::schedule_block(int RunningState,int currentprocesspcbindex , deque<int>& readyState,deque<int>& blockedState ,CPU &cpu ,PcbBlock PcbTable[] )
{

    if(readyState.empty()){
        insert_into_ready_que(readyState);
    }

    int newprocessindex = readyState.at(0);

    readyState.pop_front();

    ///block the current process and save the values into the PCBblock
    context_switch_saving_for_blocked_operation(currentprocesspcbindex,cpu,PcbTable);
    // raise the priority of the the current process
    blockedState.push_back(currentprocesspcbindex);
    raise_priority(PcbTable[currentprocesspcbindex].priority, currentprocesspcbindex,PcbTable);
    context_switch_Loading(newprocessindex,cpu, PcbTable);

}

/*
   Schedule a new process to run on the CPU, while handling unblocking of a process.
   
   Parameters:
   - RunningState: The index of the currently running process (-1 if no process is running).
   - currentprocesspcbindex: The index of the currently running process in the PCB table.
   - readyState: Reference to a deque representing the ready state containing process indices.
   - blockedState: Reference to a deque representing the blocked state containing process indices.
   - cpu: Reference to the CPU object.
   - PcbTable: An array representing the PCB table containing process information.
*/
void scheduling_policy::schedule_unblock(int RunningState,int currentprocesspcbindex , deque<int>& readyState,deque<int>& blockedState ,CPU &cpu ,PcbBlock PcbTable[] )
{

    if(blockedState.empty())
    {
        cout<<"Cannot Unblock a process because the blocked queue is empty \n";
        return;

    }
    int blocked_process_index =blockedState.at(0);
    blockedState.pop_front();

    Scheduleling_Algorithm(PcbTable[blocked_process_index].priority, blocked_process_index);

    // Insert new process into the ready que
    if(readyState.empty()){
        insert_into_ready_que(readyState);
    }

    int newprocessindex = readyState.at(0);

    readyState.pop_front();
    // lower the priority of the current process that will be preempted and it to be scheduled again by its new priority
    lower_priority(PcbTable[currentprocesspcbindex].priority, currentprocesspcbindex,PcbTable);
    // save the current running process in the PCB table
    context_switch_saving(currentprocesspcbindex,cpu,PcbTable);//grab the information from the CPU and PCBtable
    // Load the new process and set it to running
    context_switch_Loading(newprocessindex,cpu, PcbTable);
}

/*
   Scheduling algorithm to determine the appropriate priority queue for a process.
   
   Parameters:
   - Priority: The priority of the process.
   - pcbindex: The index of the process in the PCB table.
*/

void scheduling_policy::Scheduleling_Algorithm(int Priority,int pcbindex ){

    if ( Priority < 0 || Priority > 4)
    {
        std::cout<< "Invalod Priority Initlized"<<std::endl;
        std::cout<<"Priority: " << Priority<< std::endl;
        assert( Priority >=0);
        assert(Priority <= 4);
    }

    if(Priority == 0   )
    {
        insert_highestPriorityQueue(Priority,pcbindex);
    }
    else if(Priority == 1  )
    {
        insert_secondHighestPriorityQueue(Priority,pcbindex);
    }
    else if(Priority == 2  )
    {
        insert_thirdHighestPriorityQueue(Priority,pcbindex);
    }
    else if(Priority == 3  )
    {
        insert_lowestPriorityQueue(Priority,pcbindex);
    }

}
/*
   Insert a process into the ready queue.
   
   Parameters:
   - readyState: Reference to a deque representing the ready state containing process indices.
*/

void scheduling_policy::insert_into_ready_que(std::deque<int>& readyState){


    std::pair<int,int> temp_pair =update_ready_que_helper_function();

   
    if( (temp_pair.first == -1)|| (temp_pair.second == -1) )
    {
        std::cout<< "No more more processes scheduled"<<std::endl;
        std::cout<< "Terminating program"<<std::endl;
         // bounds checking an assert
        assert( temp_pair.first !=-1);
        assert(temp_pair.second  != -1);
    }
    int processPCBindex = temp_pair.second ;
    readyState.push_back(processPCBindex);

}

/*
   Helper function to update the ready queue by retrieving the next highest priority process.
   
   Returns:
   - A pair containing the priority and PCB index of the next highest priority process.
*/

std::pair<int, int> scheduling_policy::update_ready_que_helper_function()
{
    // Helper function that returns the next highest priority proccess next in line
    std::pair<int,int> topPair(-1,-1);
    for(int i = 0 ; i < 4; ++i) {
        while (!Priorityarray[i].empty()) {
            topPair = Priorityarray[i].top();
            Priorityarray[i].pop(); // pop of the returning value b/c we don't know if we are going to be blocked or not
            return topPair;
        }
    }
    return topPair;
}
/*
   Print the contents of all priority queues in the scheduling policy.
*/

void scheduling_policy::print(){

    for (int i = 0; i < 4; ++i) {
        std::cout << "Priority Queue " << i << ":" << std::endl;
        while (!Priorityarray[i].empty()) {
            std::pair<int, int> element = Priorityarray[i].top();
            std::cout << "  Priority: " << element.first << ", Value: " << element.second << std::endl;
            Priorityarray[i].pop();
        }
        std::cout << std::endl;
    }


}


