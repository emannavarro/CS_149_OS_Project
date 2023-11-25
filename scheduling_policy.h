#ifndef scheduling_policy_H
#define scheduling_policy_H
#include <queue>
#include <vector>
#include <deque>

enum State {
highestPriorityQueue,
secondHighestPriorityQueue,
thirdHighestPriorityQueue,
lowestPriorityQueue

};
using IntPair = std::pair<int, int>;

class scheduling_policy{

/*
Not tested and not complete 
Under construction, class definition not complete

*/


public:
scheduling_policy();
~scheduling_policy();
void schedule(int RunningState);
std::pair<int, int> update_ready_que();
void block();
void insert_highestPriorityQueue(int priority, int pcbindex);
void insert_secondHighestPriorityQueue(int priority, int pcbindex);
void insert_thirdHighestPriorityQueue(int priority, int pcbindex);
void insert_lowestPriorityQueue(int priority, int pcbindex);
private:
std::priority_queue<std::pair<int,int> , std::vector<std::pair<int,int> >, std::greater<std::pair<int,int> > >* Priorityarray;

};



#endif