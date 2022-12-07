#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

struct thread_arg {
    char * name;
    char * str;
    int num;
};

void * Thfunc(void * arg) {//вывод
    int i;
    struct thread_arg targ = *(struct thread_arg *) arg;
    for (i = 1; i <= targ.num; i++){
        printf("Thread %s. %s %d\n",targ.name, targ.str, i );
        sleep(1);
    }
    return NULL;
}

int main(void) {
    pthread_t thread1, thread2, thread3, thread4;

    struct thread_arg targ;
    struct thread_arg targ1;
    struct thread_arg targ2;
    struct thread_arg targ3;

    targ.name = "Thread1";
    targ.str = "Good morning";
    targ.num = 4;//кол-во повторений строки

    targ1.name = "Thread2";
    targ1.str = "Good World";
    targ1.num = 1;

    targ2.name = "Thread3";
    targ2.str = "Good day";
    targ2.num = 5;

    targ3.name = "Thread4";
    targ3.str = "Good life";
    targ3.num = 8;

    if (pthread_create(&thread1, NULL, &Thfunc, &targ) != 0) {
        fprintf(stderr, "Error (thread1)\n");
        return 1;
    }

    if (pthread_create(&thread2, NULL, &Thfunc, &targ1) != 0) {
        fprintf(stderr, "Error (thread2)\n");
        return 1;
    }

    if (pthread_create(&thread3, NULL, &Thfunc, &targ2) != 0) {
        fprintf(stderr, "Error (thread3)\n");
        return 1;
    }

    if (pthread_create(&thread4, NULL, &Thfunc, &targ3) != 0) {
        fprintf(stderr, "Error (thread4)\n");
        return 1;
    }

    sleep(5);
    return 0;
}