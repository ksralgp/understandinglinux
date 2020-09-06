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
  execl("/home/ksurable/projects/understandinglinux/understandinglinux/examples/process/forkAndExec",
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
