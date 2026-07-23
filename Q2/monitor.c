#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        exit(1);
    } 
    else if (pid == 0) {
        printf("Child process (PID: %d) started.\n", getpid());
        while(1) { sleep(1); }
    } 
    else {
        printf("Parent (PID: %d) monitoring child (PID: %d).\n", getpid(), pid);
        sleep(3);
        
        kill(pid, SIGKILL);
        
        int status;
        waitpid(pid, &status, 0);
        printf("Child reaped. Zombie prevented.\n");
    }
    return 0;
}