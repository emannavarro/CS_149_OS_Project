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


