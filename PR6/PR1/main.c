#include <stdio.h>
#include <unistd.h>

int main() {
	printf("PID %d\n", getpid());
	printf("parent PID %d\n", getppid());
	printf("group PID %d\n", getpgrp());
	printf("real user ID %d\n", getuid());
	printf("effective user ID %d\n", geteuid());
	printf("group ID %d\n", getgid());
	printf("effective group ID %d\n", getegid());

	return 0;
}