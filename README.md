# CS_149_OS_Project: Process Management Simulation

### Aaron Ooi, Ali Zargari, Emanuel Navarro, Sachin Kaul ###

## Project Description ##

Goal: To simulate five process management functions: process creation, replacing the 
current process image with a new process image, process state transition, process scheduling, 
and context switching.

This simulation exercise consists of three types of Linux processes: commander, process manager, and reporter. There is one commander process (this is the process that starts your simulation), one process manager process that is created by the commander process, and a number of reporter processes that get created by the process manager, as needed.

## Process manager: Scheduling ##

Designated: Emanuel Navarro

The process manager also implements a scheduling policy. You may experiment with a
scheduling policy of multiple queues with priority classes. In this policy, the first simulated
process (created by the process manager) starts with priority 0 (highest priority). There are a
maximum of four priority classes. Time slice (quantum size) for priority class 0 is 1 unit of
time; time slice for priority class 1 is 2 units of time; time slice for priority class 2 is 4 units of
time; and time slice for priority class 3 is 8 units of time. If a running process uses its time
slice completely, it is preempted and its priority is lowered. If a running process blocks before
its allocated quantum expires, its priority is raised.


## Process manager: Context Switching ##

Designated: Emanuel Navarro

Context switching involves copying the state of the currently running simulated process from
Cpu to PcbTable (unless this process has completed its execution), and copying the state of
the newly scheduled simulated process from PcbTable to Cpu.
Reporter Process TBA



## Simulated Process ##

Designated: Ali Zargari, Aaron Ooi

Process management simulation manages the execution of simulated processes. Each
simulated process is comprised of a program that manipulates (sets/updates) the value of a single integer variable. Thus the state of a simulated process at any instant is comprised of the value of its integer variable and the value of its program counter. A simulated process’ program consists of a sequence of instructions. There are seven types of instructions as follows:

1.	S n: Set the value of the integer variable to n, where n is an integer.
2.	A n: Add n to the value of the integer variable, where n is an integer.
3.	D n: Subtract n from the value of the integer variable, where n is an integer. 
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



