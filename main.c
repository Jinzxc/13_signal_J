#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void sighandler(int signo) {
    if(signo == SIGINT) {
        char msg[100];
        snprintf(msg, sizeof(msg), "Program exited with process PID %d\n", getpid());
        printf("%s", msg);

        int log = open("log.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
        write(log, msg, strlen(msg));

        close(log);
        exit(0);
    } 
    
    if(signo == SIGUSR1){
        printf("    Parent process PID: %d\n", getppid());
    }
}

int main() {
    signal(SIGINT, sighandler);
    signal(SIGUSR1, sighandler);

    while(1) {
        printf("Current process PID: %d\n", getpid());
        sleep(1);
    }

    return 0;
}