#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int a = 0;

static void signal_handler(int signo) {//обработчик сигналов
    if (signo == SIGUSR1){//User-defined signal	1
        printf("%d. Received SIGUSR1!\n", a);
        a++;
    }
}

int main(void) {
    int flag = 0;
    pid_t pid = fork();
    while(1){
        if (signal(SIGUSR1, signal_handler) == SIG_ERR) {
            //невозможно обработать сигнал
            fprintf(stderr, "Unable to process the signal - SIGUSeR1!\n");
            exit(EXIT_FAILURE);
        }
        if (pid == 0) {
            //сигнал   SIGUSR1 отправляется(сообщает) всем процессам в группе процессов вызывающего процесса
            kill(getppid(), SIGUSR1);
            pause();
            printf("Child process\n");
        }
        if (pid > 0) {
            pause();
            printf("Parent process\n");
            kill(pid, SIGUSR1);//отправляет сигнал SIGUSR1 процессу pid
        }
        //sleep(1);
    }
    return 0;
}
