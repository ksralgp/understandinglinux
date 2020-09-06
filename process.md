# Process
## Read this Instead
Linux Systems Programs sectoin on Processes. Honestly just read this whole book.

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

### PID 
A PID (process ID) is a unique identifier for a process. The Linux kernel is responsible for assigning a PID to a process when the process is created. The following PID values are special:
* 0 - The idle process. When there is nothing to do this process runs.
* 1 - The init process. This is the first process the kernel runs after booting a system.

A PID uniquely identifies a process at a single instance in time. If a process has a PID 426, no other process shares the same PID. After this process is terminated, it is possible for a newly created process to be assigned the PID 426. In practice this takes a long time to happen. The Linux kernel allocates PID values sequentially and wraps around when '/proc/sys/kernel/pid_max' is reached.
```
> cat /proc/sys/kernel/pid_max
4194304
```
## Lifecycle of a Process
### Creation and Execution
Linux provides a system command <code>fork</code> for creating a new process. Fork is conceptually simple. It creates a new process that is an exact clone of the calling process. Both the calling and child process continue execution after a call to <code>fork</code>. The return value of fork depends on whether you are in the calling or child process context.
```
#include "unistd.h"
#include <stdio.h>

int main(int argn, char** argv) {
  pid_t parent_pid = getpid();  
  pid_t child_pid = fork();
  if (child_pid == -1) {
    printf("Unexpected error. Unabled to fork\n");
  } else if (child_pid > 0) {
    printf("I am the Parent Process pid=%u. My child is pid=%u\n",parent_pid,child_pid);
    return 0;
  } else {
    child_pid = getpid();
    printf("I am the Child pid=%u. My parent is pid=%u\n",child_pid,parent_pid);
    printf("My parent %s was called with %u input arguments\n",
	   argv[0],
	   argn-1);
  }
  
  return 0;
}
```
```
> ./processLifeCycle 1 2 3
I am the Parent Process pid=3149. My child is pid=3150
I am the Child pid=3150. My parent is pid=3149
My parent ./processLifeCycle was called with 3 input arguments
```
Fork alone does not explain process creation's common use-case: create a new process running a different program. For example the bash command
```
> gcc processLifeCycle.c -o processLifeCycle
```
will create a new process running the binary '/usr/bin/gcc' with the input arguments 'processLifeCycle.c -o processLifeCycle'. This is done using one of Linux's exec* commands.

The exec* family of commands load a specified binary into the current address space (replacing the existing contents) and start execution of the binary.
```
#include "unistd.h"
#include <stdio.h>
#include <string.h>

void runEntryPoint(char** argv) {
  pid_t pid = fork();
  if(pid == -1) {
    printf("Unexpected error when trying to fork\n");
  } else if(pid > 0) {
    return; 
  }

  /* Run the same binary with different arguments */
  execl("/path/to/forkAndExec",
	"forkAndExec","child",NULL);
}

void runChild(int argn, char** argv)
{
  printf("I am the Child. My arguments are: \n");
  for(int k = 1; k < argn; k++) {
    printf("%s ",argv[k]);
  }
  printf("\n");
}

int main(int argn, char** argv) {
  if(argn == 1) {
    runEntryPoint(argv);
    return 0;
  } else {
    runChild(argn, argv);
  }
  return 0;
}
```
```
> ./forkAndExec
I am the Child. My arguments are:
child
```
Putting everything together, the general workflow for creating a new process is fork then exec.
### Termination
## Process Organization and Hierarchy

### Groups and Job Control

### Sessions and TTYs

## Daemonizing a Process

## Things to Fix
Clarifying a running process. It also includes a zombie. Should I instead use an available process? Will understand better after writing lifecycle of a process.


## References
Linux Systems Programs 
https://en.wikipedia.org/wiki/Executable_and_Linkable_Format
https://en.wikipedia.org/wiki/Executable
https://en.wikipedia.org/wiki/Process_(computing)
https://en.wikipedia.org/wiki/Process_identifier
