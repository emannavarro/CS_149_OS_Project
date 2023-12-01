#simple make file

#define target, its dependencies amd files
schedule: scheduling_policy.cpp scheduling_policy.h context_switching.cpp context_switching.h
	g++ -o schedule scheduling_policy.cpp context_switching.cpp
#define 
clean:
	rm -f schedule  *.o *~