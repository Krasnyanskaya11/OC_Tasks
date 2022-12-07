#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>


void * print(void * arg){
    //немедленная отмена потока(в любой момент)
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
	int i = 0;
	while (1){
		printf("Child thread. Iteration %d.\n", i);
		sleep(1);
		i++;//подсчет
	}
}

int main(int argc, char **argv){
	if (argc == 1){
        printf("Set at least one argument!");
	}else{
		pthread_t thread;
		if (pthread_create(&thread, NULL, &print, NULL) != 0) {
				fprintf(stderr, "Error (thread1)\n");
				return 1;
		}
        int num=atoi(argv[1]);
		sleep(num);//время задержки выбрали
		pthread_cancel(thread);//отправляет в поток запрос на отмену
		void *result;

		if (result == PTHREAD_CANCELED)
			fprintf(stderr, "Canceled\n");
		else fprintf(stderr, "Succesful exit\n");
	}
	return 0;
}