#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#define SECONDS 3

int main() {


    printf("Forking started\n");
    pid_t pid = fork();

    int count = 0;
    time_t currentTime = time(NULL);

    if (pid == 0) {
        while (time(NULL) != (currentTime + SECONDS)) {
            count++;//сколько раз выполнится
        }
        printf("Child PID = %d. Count = %d\n", getpid(), count);
    } else if (pid > 0) {
        while (time(NULL) != (currentTime + SECONDS)) {
            count++;
        }
        printf("Parent PID = %d. Count = %d\n", getpid(), count);
    } else {
        printf("Error\n");
    }

    return 0;
}