#include <stdio.h>
#include <getopt.h>

int main(int argc, char **argv) {
    int opt;
    char *file_name = NULL;
    int workMode = 0;

    while((opt = getopt(argc, argv, "ho:c")) != -1) {
        switch(opt) {
            case 'h':
                printf("Help string\n");
                break;
            case 'c':
                workMode = 1;
                break;
            case 'o':
                file_name = optarg;
                break;
            case '?':
                printf("Unknown option ignored\n");
                break;
            default:
                printf("Unknown error!!!\n");
                return -1;
        }
    }

    if (file_name != NULL) {
        printf("Output file: %s\n", file_name);
    }

    if (workMode) {
        printf("Specific work mode\n");
    } else {
        printf("Ordinary work mode\n");
    }

    printf("\n");

    return 0;
}
