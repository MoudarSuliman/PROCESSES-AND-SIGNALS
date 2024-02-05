#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include<sys/wait.h>

#define NUM_CHILD 4

int main(void)
{
    int status,count=0;
    pid_t pid,pidWait;
    for(int i=0; i<NUM_CHILD; i++){
        pid = fork();
        if(pid == -1){
            printf("Child not created\n");
            kill(0,SIGTERM); //SIGTERM sends signal to all children
            exit(1);
        }else if(pid == 0){
            printf("Child with PID  %d and a Parent Process with %d\n", getpid(),getppid());
            sleep(10);
            printf("Execution is complete! Child %d\n",getpid());
            exit(0);
        }
        sleep(1);
    }

    printf("All children has been created\n");
    
    //if pidWait is postive integer then child process was terminated
    while((pidWait = wait(&status)) > 0){
        if(WIFEXITED(status)){
            count++;
        }
    }
    printf("No more child processes\n");
    printf("Recieved children processes exit codes %d\n", count);
    return 0;
}