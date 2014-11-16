 /* A basic example of fork() usage.
 * For more info check the manual pages  for fork(), getpid() and wait().
 */
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main (void) {
  int forkRes;
  pid_t proccessID;


  // In parent, forkRes == child's process id
  // In child, forkRes == 0
  forkRes = fork();

  if(forkRes == 0) {
    // I am the child proccess
    printf("Child proccess says hi! My process ID is: %d My" " "
    "parents process ID is: %d\n", getpid(), getppid());
  }
  else if (forkRes == -1) {
    printf("Something went wrong...\n");
    exit(-1);
  }
  else {
    // I am the parent proccess
    printf("Parent proccess says hi! My process ID is: %d My child's process" " "
    "ID is: %d My parent is: %d\n", getpid(), forkRes, getppid());
    wait(); // wait for the child process to end before terminating
  }

  return 0;

}
