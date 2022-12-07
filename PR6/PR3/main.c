#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int main() {
    //setbuf(stdout, NULL);
    printf("Main PID %d\n", getpid());
    int localVariable = 0;
    pid_t pid[2];
    pid[0] = fork();

    if (pid[0] == 0) {// child process
        localVariable++;
        printf("\nChild process1:\nLocal variable = %d\nAddress = %p\nParent PID = %d\nOwn PID = %d\n", localVariable, &localVariable,getppid(), getpid());

        pid_t subpid[2];//под-процессы
        subpid[0] = fork();

        if (subpid[0] == 0) { // child of child
            localVariable++;
            printf("\nChild of child1:\nLocal variable = %d\nAddress = %p\nParent PID = %d\nOwn PID = %d\n", localVariable, &localVariable, getppid(), getpid());
        } else if (subpid[0] > 0) {//parent
            subpid[1] = fork();
            if (subpid[1] == 0) {//новый child
                localVariable++;
                printf("\nChild of child2:\nLocal variable = %d\nAddress = %p\nParent PID = %d\nOwn PID = %d\n", localVariable, &localVariable, getppid(), getpid());
            } else if (subpid[1] > 0) {
                printf("Second Main IDs1 = %d IDs2 = %d\n", subpid[0], subpid[1]);
                wait(NULL);
            }
        }
    } else if (pid[0] > 0) {// parent process
        pid[1] = fork();
        if (pid[1] == 0) {// child of parent
            localVariable++;
            printf("\nChild process2:\nLocal variable = %d\nAddress = %p\nParent PID = %d\nOwn PID = %d\n", localVariable, &localVariable, getppid(), getpid());
            pid_t subpid[2];
            subpid[0] = fork();
            if (subpid[0] == 0) {
                // parent of parent child
                localVariable++;
                printf("\nChild of child3:\nLocal variable = %d\nAddress = %p\nParent PID = %d\nOwn PID = %d\n", localVariable, &localVariable, getppid(), getpid());
            } else if (subpid[0] > 0) {
                // child of parent child
                subpid[1] = fork();
                if (subpid[1] == 0) {
                    localVariable++;
                    printf("\nChild of child4:\nLocal variable = %d\nAddress = %p\nParent PID = %d\nOwn PID = %d\n", localVariable, &localVariable, getppid(), getpid());
                } else if (subpid[1] > 0) {
                    printf("Second Main IDs1 = %d IDs2 = %d\n", subpid[0], subpid[1]);
                }
            }
        } else if (pid[1] > 0) {
            printf("Main ID1 = %d ID2 = %d\n\n", pid[0], pid[1]);
            wait(NULL);
        }
    }

    return 0;
}
