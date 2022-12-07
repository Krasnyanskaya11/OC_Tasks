#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef struct array_list_t {
    int *array;
    int size;
    int count;
}array_list_t;

array_list_t *newArrayList(int list_size);
void destroyArrayList(array_list_t *obj);
void printArray(array_list_t *obj);
static void add(struct array_list_t *self, int item);
static void insert(struct array_list_t *self, int index, int item);
static int size(struct array_list_t *self);
static void removeElem(struct array_list_t *self, int index);
static void set(struct array_list_t *self, int index, int item);
static int get(struct array_list_t *self, int index);

int main() {
    array_list_t *obj = newArrayList(10);
    int input, index, num;
    do{
        printf("\n 1-Add number \n 2-Insert number \n 3-Size arrayList \n 4-Remove number \n 5-set \n 6-Get number \n 7-Print arrayList\n 0-exit\n");
        scanf("%d",&input);
        switch(input){
            case 1:
                printf("Enter num: ");
                scanf("%d",&num);
                add(obj,num);
                break;
            case 2:
                printf("Enter num: ");
                scanf("%d",&num);
                printf("Enter index: ");
                scanf("%d",&index);
                insert(obj,index,num);
                break;
            case 3:
                printf("Size arrayList: %d\n",size(obj));
                break;
            case 4:
                printf("Enter index: ");
                scanf("%d",&index);
                removeElem(obj,index);
                break;
            case 5:
                printf("Enter num: ");
                scanf("%d",&num);
                printf("Enter index: ");
                scanf("%d",&index);
                set(obj,index,num);
                break;
            case 6:
                printf("Enter index: ");
                scanf("%d",&index);
                printf("Num: %d\n",get(obj,index));
                break;
            case 7:
                printf("ArrayList: ");
                printArray(obj);
                break;
            case 0:
                printf("Exit....\n");
                destroyArrayList(obj);
        }
    }while(input!=0);

    return 0;
}
//init arrayList
array_list_t *newArrayList(int list_size) {
    if (!list_size) return NULL;
    array_list_t *obj = (array_list_t *)malloc (sizeof(array_list_t));
    obj->array = (int *)malloc(list_size * sizeof(int));
    obj->size=list_size;
    //obj->count=1;
    return obj;
}
//delete arrayList
void destroyArrayList(array_list_t *obj) {
    if (!obj) return;
    free(obj->array);
    free(obj);
}

void printArray(array_list_t *obj) {
    if (!obj) return;
    printf("No numbers..add!\n");
    for (int i = 0;i < obj->count; i++) {
        printf("%d ", get(obj, i));
    }
    printf("\n");
}
//1.
static void add(struct array_list_t *self, int item) {
    if (!self) return;

    if (self->count == self->size) {
        self->size *= 2;
        self->array = (int *)realloc(self->array, self->size * sizeof(int));
    }
    self->array[self->count++] = item;
}
//2.
static void insert(struct array_list_t *self, int index, int item) {
    if (!self) return;

    if (self->count == self->size) {
        self->size *= 2;
        self->array = (int *)realloc(self->array, self->size * sizeof(int));
    }
    if (index == self->count) {
        self->array[self->count++] = item;
    }
    else {
        for (int i = index; i < self->count; i++) {
            int temp = self->array[i];
            self->array[i] = item;
            item = temp;
        }
        self->array[self->count++] = item;
    }
}
//3.
static int size(struct array_list_t *self) {
    if (!self) return -1;
    return self->count;
}
//4.
static void removeElem(struct array_list_t *self, int index) {
    if (!self || index >= self->count) return;

    for (int i = index; i < self->count-1; i++) {
        self->array[i] = self->array[i+1];
    }
    self->count--;
}
//5.
static void set(struct array_list_t *self, int index, int item) {
    if (!self || index >= self->count || index<0) return;

    self->array[index] = item;

}
//6.
static int get(struct array_list_t *self, int index) {
    if (!self || index >= self->count || index<0) return -1;

    return self->array[index];
}