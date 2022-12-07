#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int factorial (int n){

    if(n==0||n==1) return 1;
    return n* factorial(n-1);

}

void * numberKatlan(void * arg) {
    int i;
	int size = *(int*) arg;
    int *arr = (int*)malloc(size*sizeof(int));
   	for (i = 0; i < size; i++){
   		arr[i] = factorial(2*i)/(factorial(i + 1)*factorial(i));
   	}
   	pthread_exit((void *) arr);
}

void * findSimpleNumber(void * arg) {
    int i,j,a;
	int size = *(int*) arg;
	int *arr = (int*)malloc(size*sizeof(int));
	for(i = 0; i < size; i++){
           arr[i] = i;
    }
    arr[1] = 0;
    for(a= 2; a < size; a++){
        if(arr[a] != 0){
            for(j = a*2; j < size; j +=a){
                arr[j] = 0;
            }
        }
    }
    pthread_exit((void*) arr);
}

int main(void) {
	pthread_t thread1, thread2;
	int a = 7;
	int b = 100;
	int *x, *y;

	if (pthread_create(&thread1, NULL, &numberKatlan, &a) != 0) {
		fprintf(stderr, "Error (thread1)\n");
		return 1;
	}

    pthread_join(thread1, (void **)&x);//ждем

    int i;
    printf("Kutlan numbers : ");
    for(i = 0;i < a; i++){
        printf("%d ", x[i]);
    }

	if (pthread_create(&thread2, NULL, &findSimpleNumber, &b) != 0) {
		fprintf(stderr, "Error (thread2)\n");
		return 1;
	}


	pthread_join(thread2, (void **)&y);

	printf("\nPrime numbers: ");
	 for(i = 0; i < b; i++){
        if(y[i] != 0)
            printf("%d ", y[i]);
        }
	printf("\nThreads finished\n");
	free(x);
	free(y);
	return 0;
}