# CS_149_OS_Project: Process Management Simulation

### Aaron Ooi, Ali Zargari, Emanuel Navarro, Sachin Kaul ###

CS 149

## Project Description: ##

Goal: To simulate five process management functions: process creation, replacing the
current process image with a new process image, process state transition, process scheduling, and context switching.

Use Linux system calls such as fork(), wait( ), pipe( ), and sleep( ). Read man pages of these system calls for details.

This simulation consists of three types of Linux processes: commander, process manager, and reporter. There is one commander process (this is the process that starts your simulation), one process manager process that is created by the commander process, and a number of reporter processes that get created by the process manager, as needed.

## Commander Process ##

Designated: Sachin Kaul

The commander process first creates a pipe and then a process manager process. It then repeatedly reads commands (one command per second) from the standard input and passes them to the process manager process via the pipe. There are four types of commands:
1.	Q: End of one unit of time.
2.	U: Unblock the first simulated process in blocked queue.
3.	P: Print the current state of the system.
4.	T: Print the average turnaround time and terminate the system. Command T appears exactly once, being the last command. Simulated Process
Process management simulation manages the execution of simulated processes. Each
simulated process is comprised of a program that manipulates (sets/updates) the userInteger of a single integer variable. Thus the state of a simulated process at any instant is comprised of the userInteger of its integer variable and the userInteger of its program counter. A simulated process’ program consists of a sequence of instructions. There are seven types of instructions as follows:

1.	S n: Set the userInteger of the integer variable to n, where n is an integer.
2.	A n: Add n to the userInteger of the integer variable, where n is an integer.
3.	D n: Subtract n from the userInteger of the integer variable, where n is an integer. 
4.	B: Block this simulated process.
5.	E: Terminate this simulated process.
6.	F n: Create a new simulated process. The new (simulated) process is an exact copy of the parent (simulated) process. The new (simulated) process executes from the instruction immediately after this (F) instruction, while the parent (simulated) process continues its execution n instructions after the next instruction.
7.	R filename: Replace the program of the simulated process with the program in the file
filename, and set program counter to the first instruction of this new program. An example of a program for a simulated is as follows:
S 1000
A 19
A 20
D 53
A 55
F 1
R file_a F 1
R file_b F 1
R file_c F 1
R file_d F 1
R file_e E

You may store the program of a simulated process in an array, with one array entry for each instruction.

## Process Manager Process ##

The process manager process simulates five process management functions: creation of new (simulated) processes, replacing the current process image of a simulated process with a new process image, management of process state transitions, process scheduling, and context switching. In addition, it spawns a reporter process whenever it needs to print out the state of the system.

The process manager creates the first simulated process (process id = 0). Program for this process is read from a file (filename: init). This is the only simulated process created by the process manager on its own. All other simulated processes are created in response to the execution of the F instruction.

## Process manager: Data structures ##

Designated: Sachin Kaul
 
The process manager maintains six data structures: Time, Cpu, PcbTable, ReadyState, BlockedState, and RunningState. Time is an integer variable initialized to zero. Cpu is used to simulate the execution of a simulated process that is in running state. It should include data members to store a pointer to the program array, current program counter userInteger, integer userInteger, and time slice of that simulated process. In addition, it should store the number of time units used so far in the current time slice.

PcbTable is an array with one entry for every simulated process that hasn't finished its execution yet. Each entry should include data members to store process id, parent process id, a pointer to program counter userInteger (initially 0), integer userInteger, priority, state, start time, and CPU time used so far.

ReadyState stores all simulated processes (PcbTable indices) that are ready to run. This can be implemented using a queue or priority queue data structure. BlockedState stores all processes (PcbTable indices) that are currently blocked. This can be implemented using a queue data structure. Finally, RunningState stores the PcbTable index of the currently running simulated process.

## Process manager: Processing input commands ##

Designated: Ali Zargari, Aaron Ooi

After creating the first process and initializing all its data structures, the process manager repeatedly receives and processes one command at a time from the commander process (read via the pipe). On receiving a Q command, the process manager executes the next instruction of the currently running simulated process, increments program counter userInteger (except for For R instructions), increments Time, and then performs scheduling. Note that scheduling may involve performing context switching.

On receiving a U command, the process manager moves the first simulated process in the blocked queue to the ready state queue array. On receiving a P command, the process manager spawns a new reporter process. On receiving a T command, the process manager first spawns a reporter process and then terminates after termination of the reporter process. The process manager ensures that no more than one reporter process is running at any moment.

## Process manager: Executing simulated processes ##

Designated: Ali Zargari, Aaron Ooi

The process manager executes the next instruction of the currently running simulated process on receiving a Q command from the commander process. Note that this execution is completely confined to the Cpu data structure, i.e. PcbTable is not accessed.

Instructions S, A and D update the integer userInteger stored in Cpu. Instruction B moves the currently running simulated process to the blocked state and moves a process from the ready state to the running state. This will result in a context switch. Instruction E terminates the currently running simulated process, frees up all memory (e.g. program array) associated with that process and updates the PcbTable. A simulated process from the ready state is moved to running state. This also results in a context switch.

Instruction F results in the creation of a new simulated process. A new entry is created in the PcbTable for this new simulated process. A new (unique) process id is assigned and the parent process id is process id of the parent simulated process. Start time is set to the current Time userInteger and CPU time used so far is set to 0. The program array and integer userInteger of the new simulated process are a copy of the program array and integer userInteger of the parent simulated process. The new simulated process has the same priority as the parent simulated process. The program counter userInteger of the new simulated process is set to the instruction immediately after the F instruction, while the program counter userInteger of the of the parent simulated process is set to n instructions after the next instruction (instruction immediately after F. The new simulated process is created in the ready state.
Finally, the R instruction results in replacing the process image of the currently running simulated process. Its program array is overwritten by the code in file filename, program counter userInteger is set to 0, and integer userInteger is undefined. Note that all these changes are made only in the Cpu data structure. Process id, parent process id, start time, CPU time used so far, state, and priority remain unchanged.

## Process manager: Scheduling ##

Designated: Emanuel Navarro

The process manager also implements a scheduling policy. You may experiment with a scheduling policy of multiple queues with priority classes. In this policy, the first simulated process (created by the process manager) starts with priority 0 (highest priority). There are a maximum of four priority classes. Time slice (quantum size) for priority class 0 is 1 unit of time; time slice for priority class 1 is 2 units of time; time slice for priority class 2 is 4 units of time; and time slice for priority class 3 is 8 units of time. If a running process uses its time slice completely, it is preempted and its priority is lowered. If a running process blocks before its allocated quantum expires, its priority is raised.

## Process manager: Context Switching ##

Designated: Emanuel Navarro

Context switching involves copying the state of the currently running simulated process from Cpu to PcbTable (unless this process has completed its execution), and copying the state of the newly scheduled simulated process from PcbTable to Cpu.
Reporter Process
The reporter process prints the current state of the system on the standard output and then
terminates. The output from the reporter process appears as follows:



