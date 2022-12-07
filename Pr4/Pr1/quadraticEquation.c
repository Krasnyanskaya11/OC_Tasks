#include <stdlib.h>
#include <math.h>
#include "quadraticEquation.h"

// solve equations like a*x^2 + b*x + c = 0
QuadraticEquationResult* solveQuadraticEquation(double a, double b, double c) {
    QuadraticEquationResult *result = (QuadraticEquationResult*) malloc(sizeof(QuadraticEquationResult));

    result->type = 0;
    double discriminant;

    int correctnessOfQuadraticEquation = 0;
    if (a != 0) correctnessOfQuadraticEquation += 100;
    if (b != 0) correctnessOfQuadraticEquation += 10;
    if (c != 0) correctnessOfQuadraticEquation += 1;

    switch(correctnessOfQuadraticEquation) {
        case 100:
        case 101:
        case 110:
        case 111:
            discriminant = b*b - 4*a*c;
            if (discriminant >= 0) {
                result->x1 = (-b - sqrt(discriminant)) / (2 * a);
                result->x2 = (-b + sqrt(discriminant)) / (2 * a);
                result->type = 1;
            } else {
                result->type = 0;
            }
            break;
        default:
            result->type = -1;
            break;
    }

    return result;
}
