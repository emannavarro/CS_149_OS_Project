#include <iostream>
#include <queue>
#include "scheduling_policy.h"


/*
Not tested and not complete 

*/

scheduling_policy::scheduling_policy(){
 // Constructor 
 // Dynamically allocate a min priority queue using the new operator
  highestPriorityQueue = new std::priority_queue<int, std::vector<int>, std::greater<int> >();
  secondHighestPriorityQueue = new std::priority_queue<int, std::vector<int>, std::greater<int> >();
  thirdHighestPriorityQueue = new std::priority_queue<int, std::vector<int>, std::greater<int> >();
  lowestPriorityQueue = new std::priority_queue<int, std::vector<int>, std::greater<int> >();




}
scheduling_policy::~scheduling_policy(){
    // Destructor, Freeing allocated memory
    delete highestPriorityQueue; highestPriorityQueue = 0;
    delete secondHighestPriorityQueue; secondHighestPriorityQueue = 0;
    delete thirdHighestPriorityQueue; thirdHighestPriorityQueue = 0;
    delete lowestPriorityQueue; lowestPriorityQueue = 0;


}

/*
main just a place holder used for debugging and compiling

*/
int main(){


std::cout<<"hello Emanuel"<<std::endl;

return 0;


}