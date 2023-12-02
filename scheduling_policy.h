#ifndef scheduling_policy_H
#define scheduling_policy_H
#include <queue>
#include <vector>
#include <deque>
#include <utility>
#include "context_switching.h"




class scheduling_policy{

/*
Not tested and not complete 
Under construction, class definition not complete

*/


public:
scheduling_policy();
scheduling_policy(std::vector<std::pair< int, int> > &highest_priority,std::vector<std::pair< int, int> > &second_highest_priority, std::vector<std::pair< int, int> > &third_highest_priority,std::vector<std::pair< int, int> > &lowest_priority  );
~scheduling_policy();
std::pair<int, int> update_ready_que_helper_function();
void block();
void insert_highestPriorityQueue(int priority, int pcbindex);
void insert_secondHighestPriorityQueue(int priority, int pcbindex);
void insert_thirdHighestPriorityQueue(int priority, int pcbindex);
void insert_lowestPriorityQueue(int priority, int pcbindex);
void Scheduleling_Algorithm(int Priority,int pcbindex );
void insert_into_ready_que(std::deque<int>& readyState);
void schedule(int RunningState,int currentprocesspcbindex , std::deque<int>& readyState, CPU &cpu ,PcbBlock PcbTable[]);
void print();
void lower_priority(int priority, int pcbindex,PcbBlock PcbTable[]);
void raise_priority(int priority, int pcbindex,PcbBlock PcbTable[]);
void schedule_block(int RunningState,int currentprocesspcbindex , deque<int>& readyState,deque<int>& blockedState ,CPU &cpu ,PcbBlock PcbTable[] );
void schedule_unblock(int RunningState,int currentprocesspcbindex , deque<int>& readyState,deque<int>& blockedState ,CPU &cpu ,PcbBlock PcbTable[] );
private:
std::priority_queue<std::pair<int,int> , std::vector<std::pair<int,int> >, std::greater<std::pair<int,int> > >* Priorityarray;

};



#endif