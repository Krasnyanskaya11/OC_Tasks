#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

static  pthread_key_t key;
static pthread_once_t once = PTHREAD_ONCE_INIT;

typedef struct thread_data {
   pthread_t id;
   char message [20];
} data;

void printMessage(){
   int i;
   srand(time(NULL));
   int number = rand() % 10 + 1;//сколько строк выводит каждый поток
   for (i = 0; i < number; i++){
   		int randomNum = rand() % 10 + 1;
   		printf("\n%s%lu.Iteration: %d.Number: %d. ",((data*)pthread_getspecific(key))->message,((data*)pthread_getspecific(key))->id,i + 1,randomNum );

           sleep(1);
   }
}

static void once_creator(void) {
    //создание ключа для идентификации данных потока
   pthread_key_create( &key, NULL);
}

void * print(void * arg){

    pthread_once(&once, once_creator);//однократная инициализация
    pthread_setspecific(key, malloc(sizeof(data)));
    data *thr = pthread_getspecific(key);
    thr->id = pthread_self();//возвращает идентификатор вызывающего потока
    char *mesg = "\nThread with id: ";
    strcpy(thr->message, mesg);
    printMessage();
}


int main(int argc, char **argv){
pthread_t *pt;
	if (argc == 1){
		printf("Set at least one argument!");
	}else{
		int i;
		int number = atoi(argv[1]);//кол-во потоков
		pt = malloc (sizeof(pthread_t) * number);

		for (i = 0; i < number; ++i){
			if (pthread_create(&pt[i], NULL, &print, &i) != 0) {
				fprintf(stderr, "Error (thread)\n");
				return 1;
			}
		}
		for(i = 0; i < number; ++i){
			if (pthread_join(pt[i], NULL) == 0) {
				printf("Thread %d finished sucessfully.\n", i);
			}
		}
	}
	free(pt);
	return 0;
}