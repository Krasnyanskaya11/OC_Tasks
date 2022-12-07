#ifndef OPERATING_SYSTEM_SOLVE_H
#define OPERATING_SYSTEM_SOLVE_H

typedef struct {
    double x1;
    double x2;
    int type; // -1 - not quadratic equation or | 0 - discriminant < 0 | 1 - quadratic
} QuadraticEquationResult;

QuadraticEquationResult* solveQuadraticEquation(double a, double b, double c);

#endif //OPERATING_SYSTEM_SOLVE_H
