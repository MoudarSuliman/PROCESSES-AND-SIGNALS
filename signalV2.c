#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define NUM_CHILD 4

volatile int interrupt_happened = 0;

void parentInterruptHandler(int signalNum) {
  interrupt_happened = 1;
  printf("[Parent] Keyboard interrupt received. Terminating...\n");
}

void childInterruptHandler(int signalNum) {
  pid_t pid;
  int status;

  // Wait for child process to terminate
  while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
    printf("[Child] Child process %d terminated\n", pid);
  }
}

int main(void) {
  int status, count = 0;
  pid_t pid, pidWait;

  // Disable all the children
  for (int signalNum = 0; signalNum <= 31; signalNum++) {
    signal(signalNum, SIG_IGN);
  }

  // Setup Interrupt Signal Handler for Parent
  signal(SIGINT, parentInterruptHandler);

  // Restore default handler
  signal(SIGCHLD, childInterruptHandler);

  for (int i = 0; i < NUM_CHILD; i++) {
    if (interrupt_happened) {
      printf("Children Creations Interrupted!\n");
      kill(0, SIGTERM); // SIGTERM sends signal to all children
      interrupt_happened = 0;
      break;
    }

    pid = fork();
    if (pid == -1) {
      printf("Child not created\n");
      kill(0, SIGTERM); // SIGTERM sends signal to all children
      exit(1);
    } else if (pid == 0) {
      signal(SIGINT, SIG_IGN);
      printf("Child with PID %d and a Parent Process with %d\n", getpid(),
             getppid());
      sleep(10);
      printf("Execution is complete! Child %d\n", getpid());
      exit(0);
    }
    sleep(1);
  }

  printf("All children has been created\n");

  // if pidWait is postive integer then child process was terminated
  while ((pidWait = wait(&status)) > 0) {
    if (WIFEXITED(status)) {
      count++;
    }
  }

  // Restore all the signal handlers to default
  for (int signalNum = 0; signalNum <= 31; signalNum++) {
    signal(signalNum, SIG_DFL);
  }

  printf("No more child processes\n");
  printf("Recieved children processes exit codes %d\n", count);
  return 0;
}