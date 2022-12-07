#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

struct thread_arg1 {
	char * str;
	int num;
};

struct thread_arg2 {
	int min;
	int max;
	int num;
	int close;
};

void * func1(void * arg) {
	int i;
	struct thread_arg1 targ = *(struct thread_arg1 *) arg;
	for (i = 1; i <= targ.num; i++){
		printf("Child thread: %s Iteration %d.\n", targ.str, i);
		sleep(1);
	}
}

void * func2(void * arg) {//генерирует заданое кол-во случайных чисел
	int i,x;
	struct thread_arg2 targ = *(struct thread_arg2 *) arg;
	srand(time(NULL));
	for (i = 1; i <= targ.num; i++){
  		x = rand() % targ.max + 1;
  		if (x == targ.close){//получено заданое случайное число
  			printf("Invalid number: %d. Closing...\n", targ.close);//завершение работы
  			pthread_exit(NULL);
  		}
  		printf("%d.) Number: %d\n",i, x);
  		sleep(1);
	}
}

int main(void) {
	pthread_t thread1, thread2;

	struct thread_arg1 targ1;
	struct thread_arg2 targ2;

	targ1.str = "Hello World!";
	targ1.num = 10;
	targ2.num = 15;
	targ2.min = 1;
	targ2.max = 10;
	targ2.close = 5;

	if (pthread_create(&thread1, NULL, &func1, &targ1) != 0) {
		fprintf(stderr, "Error (thread1)\n");
		return 1;
	}

	if (pthread_create(&thread2, NULL, &func2, &targ2) != 0) {
		fprintf(stderr, "Error (thread2)\n");
		return 1;
	}

	if (pthread_join(thread1, NULL) != 0) {
		fprintf(stderr, "Join error\n");
		return 1;
	}

	if (pthread_join(thread2, NULL) != 0) {
		fprintf(stderr, "Join error\n");
		return 1;
	}
	printf("All threads finished...\n");
	return 0;
}