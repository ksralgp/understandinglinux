# Software Performance
## A Simple Model for Single-Threaded Software Performance 
In [1] single-thread program execution time is modeled using the formula:

(seconds/program) = (instructions/program) * (cycles/instruction) * (seconds/cycle)

where:
* seconds/program - Oberved execution time of the program-under-test
* instructions/program - Dynamic measurement of instructions executed by the program
* cycles/instruction - Average CPI over during program execution based on dynamic measurements of total cycles and total instructions
* seconds/cycle - Average clock period of CPU during program execution

Assuming CPU frequency is outside the control of the program, then performance can be broken down into two primary metrics:
* Instruction Count - Total number of instructions needed to impelement the program
* CPI - How efficiently cycles of the CPU are used to execute the program instructions

and correspondingly software performance can be improved by reducing either of these metrics. Some important factors affecting total instruction count are:
* Instruction Selection - The set of instructions used to implement various algorithms and logic in the program. For example, using SIMD instructions can significantly reduce the instruction count
* Redundant and/or Unecessary Computation - This reflects a sub-optimality in the program's source or the compilation of the source into target assembly. Rewriting the source program to use a more efficient algorithm is one approach for reducing computation. Advanced compiler optimizations like CSE and LICM can also help in reducing these computations.

CPI is highly intertwined with the features of modern pipelined CPUs. At a high-level CPI describes how well the program utilizes the pipelining and caches to prevent stalls. Stalls can be broken down into 3 categories
* Branch stalls - Caused by branch misprediction 
* Data dependency stalls -  Caused by register read-after write dependencies in adjacent instructions
* Load/store stalls - Caused by cache misses, requiring slower access to off-CPU memory.

## References
[1]Embedded Systems ARM Programming and Optimization
