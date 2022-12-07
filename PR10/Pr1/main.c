#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define PRODUCE 1
#define CONSUME 1

int *buffer, ind;
sem_t lock; //использоваться как производителем,
// так и потребителем, защищая доступ к буферу от любых других потоков;
sem_t empty_items;//для организации ожидания производителя в случае полного буфера
sem_t full_items;//в случае полного буфера

void initialize(int size){
    int check;
    ind = 0;
    buffer = malloc(sizeof(int) * size);//буфер для чисел

    check = sem_init(&lock, 0, 1);
    if (check != 0) {
        perror("Semaphore initialization failed.");
        exit(EXIT_FAILURE);
    }

    check = sem_init(&empty_items, 0, size);
    if (check != 0) {
        perror("Semaphore initialization failed.");
        exit(EXIT_FAILURE);
    }

    check = sem_init(&full_items, 0, 0);
    if (check != 0){
        perror("Semaphore initialization failed.");
        exit(EXIT_FAILURE);
    }
}

void *producer(void *arg){//производитель
    srand(time(NULL));
    while(1){
        int value = (rand() % 10) + 1;
        //уменьшает значение семафора на единицу
        sem_wait(&empty_items);// есть ли место в буфере?
        sem_wait(&lock);// вход в критическую серцию
        buffer[ind] = value;//для синхронизации,забирает потом потребитель
        ind++;
        printf("Produce: %d\n", value);
        //увеличение семофора на один
        sem_post(&lock);// выход из критической секции
        sem_post(&full_items);//уведомить потребителей, что есть новый объект
        sleep(2);
    }
    pthread_exit(NULL);
}

void *consumer(void *arg){//потребитель
    while(1){
        sem_wait(&full_items);//не пустой ли буфер
        sem_wait(&lock);
        ind--;
        printf("Consume: %d\n", buffer[ind]);
        buffer[ind] = 0;
        sem_post(&lock);
        sem_post(&empty_items);
        sleep(2);
    }
    pthread_exit(NULL);
}

void *print(void *arg){
    int size = *(int*) arg;
    int i;
    while (1) {
        for (i = 0; i < size; i++){
            printf("%d ", buffer[i]);
        }
        printf("\n");
        sleep(1);
    }
}

int main(int argc, char **argv){
    pthread_t *pr, *cn;
    int size = 10;
    if (argc > 1){
        size = atoi(argv[1]);
    }
    initialize(size);

    pthread_attr_t attr;
    pthread_t pt;
    pthread_attr_init(&attr);
    // установить состояние отключения потока
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&pt, &attr, &print, &size);
    pthread_attr_destroy(&attr);

    pr = malloc(sizeof(pthread_t) * PRODUCE);
    cn = malloc(sizeof(pthread_t) * CONSUME);

    int i;
    for (i = 0; i < PRODUCE; i++){
        if (pthread_create(&pr[i], NULL, &producer, NULL) != 0) {
            fprintf(stderr, "Error (thread)\n");
            return 1;
        }
    }

    for (i = 0; i < CONSUME; i++){
        if (pthread_create(&cn[i], NULL, &consumer, NULL) != 0) {
            fprintf(stderr, "Error (thread)\n");
            return 1;
        }
    }

    sleep(15);

    for(i = 0; i < PRODUCE; ++i){
        pthread_cancel(pr[i]);
        if (pthread_join(pr[i], NULL) != 0) {
            printf("Error\n");
        }
    }

    for(i = 0; i < CONSUME; ++i){
        pthread_cancel(cn[i]);
        if (pthread_join(cn[i], NULL) != 0) {
            printf("Error\n");
        }
    }

    pthread_cancel(pt);

    free(pr);
    free(cn);
    free(buffer);
    sem_destroy(&lock);
    sem_destroy(&empty_items);
    sem_destroy(&full_items);
    return 0;
}