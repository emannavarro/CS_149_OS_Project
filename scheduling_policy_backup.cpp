#include <iostream>
#include <queue>
#include <deque>
#include <utility>
#include <cassert>
#include "scheduling_policy.h"
#include <cstdlib> // for std::rand and std::srand
#include <ctime>   // for std::time



enum prioritylevel{
highestPriorityQueue,
secondHighestPriorityQueue,
thirdHighestPriorityQueue,
lowestPriorityQueue
};


/*
Not tested and not complete 

*/

scheduling_policy::scheduling_policy()
{

 Priorityarray= new std::priority_queue<std::pair<int,int> , std::vector<std::pair<int,int> >, std::greater<std::pair<int,int> > > [4];
}

scheduling_policy::~scheduling_policy()
{
    // Destructor, Freeing allocated memory
    delete[] Priorityarray; Priorityarray=0;
}
void scheduling_policy::schedule(int RunningState,std::deque<int>& readyState, Cpu &cpu  )
{
    // 1. Return if there is still a processing running (runningState != -1).
    // There is no need to schedule if a process is already running (at least until iLab 3)
  if (RunningState != -1){
    return;
  }

 // 2. Get a new process to run, if possible, from the ready queue.
if(readyState.empty()){
  std::cout<<"ready queue is Empty please init a new process"<< std::endl;
  return;
}

 int newprocessindex = readyState.at(0);
 // remove current process
 readyState.pop_back();
 
 
 // 3. If we were able to get a new process to run:
 // a. Mark the processing as running (update the new process's PCB state)
 // b. Update the CPU structure with the PCB entry details (program, program counter,
 // value, etc.)

  //(newprocessindex,cpu);
  
 // TODO: Implement

}
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
scheduling_policy::scheduling_policy(std::vector<std::pair< int, int> > &highest_priority,std::vector<std::pair< int, int> > &second_highest_priority, std::vector<std::pair< int, int> > &third_highest_priority,std::vector<std::pair< int, int> > &lowest_priority  ){


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
void  scheduling_policy::insert_into_ready_que(std::deque<int>& readyState){


  std::pair<int,int> temp_pair =update_ready_que_helper_function();
  if( (temp_pair.first == -1)|| (temp_pair.second == -1) )
  {
    return;
  }
  int processPCBindex = temp_pair.second ;
  readyState.push_back(processPCBindex);
  
}

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

void scheduling_policy::insert_highestPriorityQueue(int priority, int pcbindex)
{
  std::pair<int,int> temp_pair;
  temp_pair.first = priority;
  temp_pair.second =pcbindex;
  Priorityarray[highestPriorityQueue].push(temp_pair);


}
void scheduling_policy::insert_secondHighestPriorityQueue(int priority, int pcbindex)
{
  std::pair<int,int> temp_pair;
  temp_pair.first = priority;
  temp_pair.second =pcbindex;
  Priorityarray[secondHighestPriorityQueue].push(temp_pair);
  
}
void scheduling_policy::insert_thirdHighestPriorityQueue(int priority, int pcbindex)
{
  std::pair<int,int> temp_pair;
  temp_pair.first = priority;
  temp_pair.second =pcbindex;
  Priorityarray[thirdHighestPriorityQueue].push(temp_pair);
}
void scheduling_policy::insert_lowestPriorityQueue(int priority, int pcbindex)
{
  std::pair<int,int> temp_pair;
  temp_pair.first = priority;
  temp_pair.second =pcbindex;
  Priorityarray[lowestPriorityQueue].push(temp_pair);

}
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

/*
main just a place holder used for debugging and compiling

*/

PcbEntry PcbTable[20];


int main(){

  std::srand(static_cast<unsigned>(std::time(0)));

  Cpu newcpu;

  std::vector<std::pair< int, int> > highest_priority;
  std::vector<std::pair< int, int> > second_highest_priority;
  std::vector<std::pair< int, int> > third_highest_priority;
  std::vector<std::pair< int, int> > lowest_priority;

    for (int i = 0; i < 4; ++i) 
   {
        int secondValue = std::rand() % 10 + 1; // Generate a random number between 1 and 10
        highest_priority.emplace_back(0, secondValue);     // Add the pair to the vector
    }
    for (int i = 0; i < 4; ++i) 
   {
        int secondValue = std::rand() % 10 + 1; // Generate a random number between 1 and 10
        second_highest_priority.emplace_back(1, secondValue);     // Add the pair to the vector
    }
    for (int i = 0; i < 4; ++i) 
   {
        int secondValue = std::rand() % 10 + 1; // Generate a random number between 1 and 10
        third_highest_priority.emplace_back(2, secondValue);     // Add the pair to the vector
    }
        for (int i = 0; i < 4; ++i) 
   {
        int secondValue = std::rand() % 10 + 1; // Generate a random number between 1 and 10
        lowest_priority.emplace_back(3, secondValue);     // Add the pair to the vector
    }
  /*
    std::cout << "Generated vector:" << std::endl;
    for (const auto& pair : highest_priority) {
        std::cout << "(" << pair.first << ", " << pair.second << ")" << std::endl;
    }

    std::cout << "Generated vector:" << std::endl;
    for (const auto& pair : second_highest_priority) {
        std::cout << "(" << pair.first << ", " << pair.second << ")" << std::endl;
    }
    std::cout << "Generated vector:" << std::endl;
    for (const auto& pair : third_highest_priority) {
        std::cout << "(" << pair.first << ", " << pair.second << ")" << std::endl;
    }
    std::cout << "Generated vector:" << std::endl;
    for (const auto& pair : lowest_priority) {
        std::cout << "(" << pair.first << ", " << pair.second << ")" << std::endl;
    }

    */
   scheduling_policy roundrobin(highest_priority,second_highest_priority, third_highest_priority, lowest_priority);
  roundrobin.print();
  
    


std::cout<<"hello Emanuel"<<std::endl;

return 0;


scheduling_policy newpolicy;



}
