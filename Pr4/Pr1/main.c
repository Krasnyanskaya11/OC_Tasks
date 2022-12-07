#include <stdio.h>
#include <stdlib.h>
#include "quadraticEquation.h"

int main(int argc, char *argv[]) {

    if (argc != 4) {
        printf("Error!!! Wrong number of arguments (expected 3 after call program)\n");
        return -1;
    } else {
        double a = atof(argv[1]);
        double b = atof(argv[2]);
        double c = atof(argv[3]);

        QuadraticEquationResult *quadraticEquationResult = solveQuadraticEquation(a, b, c);

        switch(quadraticEquationResult->type) {
            case -1:
                printf("This is NOT QUADRATIC EQUATION\n");
                break;
            case 0:
                printf("Discriminant less than zero\n");
                break;
            case 1:
                printf("Quadratic equation\nx1 = %g, x2 = %g\n", quadraticEquationResult->x1, quadraticEquationResult->x2);
                break;
            default:
                printf("Wrong Solution Selector\n");
        }
    }

    return 0;
}
