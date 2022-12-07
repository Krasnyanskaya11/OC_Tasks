#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

char *msg;

static void signal_handler(int signo) {
    if (signo == SIGALRM) {//Timer	signal	from	alarm
        printf("%s\n", msg);//получаем сигнал
    }
}
    int main(int argc, char **argv) {
        pid_t pid;
        if (signal(SIGALRM, signal_handler) == SIG_ERR) {
            //невозможно обработать
            fprintf(stderr, "Unable to process the signal - SIGALRM!\n");
            exit(EXIT_FAILURE);
        }
        msg = argv[2];
        double sec = atof(argv[1]);//с командной строки
        pid = fork();//создаем процесс
        if (pid == 0) {//сhild process
            printf("Alarm");
            alarm(sec);
            pause();
        }
        if (pid > 0) {
            printf("Termination of the main thread\n");//завершение главного потока
            exit(EXIT_SUCCESS);
        }
        return 0;
    }
