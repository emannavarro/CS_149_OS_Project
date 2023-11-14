#ifndef scheduling_policy_H
#define scheduling_policy_H
#include <queue>

class scheduling_policy{

/*
Not tested and not complete 
Under construction, class definition not complete

*/


public:
scheduling_policy();
~scheduling_policy();
void insert_highestPriorityQueue(int a){highestPriorityQueue->push(a);};
void insert_secondHighestPriorityQueue(int b){secondHighestPriorityQueue->push(b);};
void insert_thirdHighestPriorityQueue(int c){thirdHighestPriorityQueue->push(c);};
void insert_lowestPriorityQueue(int d){lowestPriorityQueue->push(d);};

private:

std::priority_queue<int, std::vector<int>, std::greater<int> >* highestPriorityQueue;
std::priority_queue<int, std::vector<int>, std::greater<int> >* secondHighestPriorityQueue;
std::priority_queue<int, std::vector<int>, std::greater<int> >* thirdHighestPriorityQueue;
std::priority_queue<int, std::vector<int>, std::greater<int> >* lowestPriorityQueue;






};



#endif