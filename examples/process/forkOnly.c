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
