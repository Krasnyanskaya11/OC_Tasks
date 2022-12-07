
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

static void signal_handler(int signo) {
    //регистрируем обработчики для сигналов
    if (signo == SIGINT)//когда пользователь нажимает Ctrl+C.
        printf("Received SIGINT!\n");
    else if (signo == SIGTERM)
        printf("Received SIGTERM!\n");
    else {
        fprintf(stderr, "Unexpected signal!\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}


int main (void) {
    struct signal sa;
    //sigset_t newset;
    sa.sa_handler = signal_handler;
    //Регистрируем signal_handler нак наш обработчик сигнала * для SIGINT

    if (signal(SIGINT, &sa, 0) != 0) {
        fprintf(stderr, "!\n");
        exit(EXIT_FAILURE);
    }

    if (signal(SIGTERM, &sa, 0) != 0) {
        fprintf(stderr, "Unable to process the signal SIGTERM!\n");
        exit(EXIT_FAILURE);
    }
    //Восстановление поведения по умолчание для сигнала SIGPROF(прекращение процесса)
    sa.sa_handler = SIG_DFL;
    if (signal(SIGPROF, &sa, 0) != 0) {
        fprintf(stderr, "Unable to process the signal SIGPROF!\n");
        exit(EXIT_FAILURE);
    }
//игнорируем SIGHUP (который также завершает процесс)
    sa.sa_handler = SIG_IGN;
    if (signal(SIGHUP, &sa, 0) != 0) {
        fprintf(stderr, "Unable to process the signal SlGHUP!\n");
        exit(EXIT_FAILURE);
    }
    for (;;) {
        raise(SIGTERM);
        pause();
    }
    return 0;
}