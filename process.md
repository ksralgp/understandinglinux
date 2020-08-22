# Process
## Executable File
An executable or binary is a file that encodes instructions in a format that the OS understands how to run. For example in bash the command

    > ls

resolves 'ls' to a binary file commonly located at /usr/bin/ls. Bash makes the appropriate system call to run this binary.

The 'file' command provides some information on this executable file:

```
> file /usr/bin/ls
/usr/bin/ls: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=4fef2dc9762eb7d4593f402a65cc02bb3d4c48de, for GNU/Linux 3.2.0, stripped
```
This output shows that the format of '/usr/bin/ls' is ELF. ELF stands for Executable and Linkable Format. In Linux ELF is a commonly used file format for binary files.

## What is a Process
A key feature of Linux is the ability to run multiple binaries simultaneously. An instance of a running binary is called a process. In Linux a process is a fundamental abstraction used to organize running programs. A useful command for getting information about processes is 'ps'.
```
> ps l
F   UID     PID    PPID PRI  NI    VSZ   RSS WCHAN  STAT TTY        TIME COMMAND
4  1000     426     377  20   0   7820  4024 -      Ss   tty1       0:00 -bash
0  1000     429     426  20   0 160692  7688 -      S    tty1       0:00 fish
4  1000     539     538  20   0 1428188 115320 -    Sl   tty1       2:40 /usr/lib/Xorg -nolisten tcp :0 vt1
0  1000     557     538  20   0 1522152 63668 -     Sl   tty1       0:01 xfce4-session
0  1000     632     557  20   0 242408 43660 -      Sl   tty1       0:27 xfwm4 --display :0.0 --sm-client-id 
0  1000     648     557  20   0 316360 47024 -      Sl   tty1       0:15 xfce4-panel --display :0.0 --sm-client-id
0  1000     653     557  20   0 334672 22304 -      Sl   tty1       0:00 Thunar --sm-client-id 
0  1000     660     557  20   0 279928 43808 -      Sl   tty1       0:02 xfdesktop --display :0.0 --sm-client-id 28
[SNIP]
```
On my machine I see 239 processes using `ps -A | wc -l`, yet using `lscpu` I see that my machine only has 8 cores. This exemplifies another important feature of Linux. It supports having more processes running than CPUs that are availabe. Although 239 processes are running on my machine, at a single instance in time a much smaller subset of processes are executing instructions on a CPU. A subsystem of the Linux kernel known as the scheduler manages the partioning of CPU resources across all running processes. 

More generically, programs in Linux can be written without awareness of other running processes. It is the responsibility of the Linux kernel to manage the sharing of hardware resources across processes. The previously mentioned scheduler is an example of this for CPU resources. Virtual memory is an example of this for memory resources. A process interacts with a virtual address space and the Linux kernel manages the translation of virtual addresses into physical addresses. This allows RAM to be shared across all processes.

## Lifecycle of a Process
### Creation and Execution
### Termination


## Process Hierarchy

## References
Linux Systems Programs 
https://en.wikipedia.org/wiki/Executable_and_Linkable_Format
https://en.wikipedia.org/wiki/Executable
https://en.wikipedia.org/wiki/Process_(computing)
