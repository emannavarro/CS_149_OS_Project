#simple make file

#define target, its dependencies amd files
schedule: scheduling_policy.cpp scheduling_policy.h
	g++ -o schedule scheduling_policy.cpp 
#define 
clean:
	rm -f schedule  *.o *~