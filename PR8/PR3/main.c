#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void * print(void * arg){
    int t = *(int*) arg;
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);//запросы на отмену игнорируются)
    int i = 0;
    for (i = 0; i < t*2; i++){
        printf("Child thread. Iteration %d.\n", i);
        sleep(1);
    }
}

int main(int argc, char **argv){
    if (argc == 1){
        printf("Set at least one argument!");
    }else{
        pthread_t thread;
        int a = atoi(argv[1]);
        if (pthread_create(&thread, NULL, &print, &a) != 0) {
            fprintf(stderr, "Error (thread1)\n");
            return 1;
        }
        sleep(atoi(argv[1]));
        pthread_cancel(thread);
        void *result;

        if (result == PTHREAD_CANCELED)
            fprintf(stderr, "Canceled\n");
        else fprintf(stderr, "Succesful exit\n");
    }
    return 0;
}