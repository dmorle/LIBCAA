#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdio_ext.h>
#include <string.h>
#include <math.h>

#include "Factory.hpp"

#define USE_OBJ_MACROS
#define USE_OP_MACROS
#include "stdAlias.hpp"

#define MAX_SIZE 64

int main() {
    LIBCAA::Factory f;

    // getting user inputs
    int m;
    printf("Please enter the number of data points you have: ");
    scanf("%d", &m);

    printf("Please enter your x values: \n");
    matrix x = f.usrInit(m, 1);

    printf("Please enter your y values: \n");
    matrix y = f.usrInit(m, 1);

    // calculating the optimal solution
    matrix ones = f.constant(m, 1, 1.0);
    matrix A = concat(x, ones, 1);
    f.release(ones);
    matrix Atrans = trans(A);

    matrix M = matmul(Atrans, A);
    matrix Y = matmul(Atrans, y);
    f.release(A);
    f.release(Atrans);

    matrix M1 = inv(M);
    matrix sol = matmul(M1, Y);
    f.release(M1);

    //r^2 = (n∑(xiyi)−(∑xi)(∑yi))^2 / ( (n∑xi^2−(∑xi)^2)*(n∑yi^2−(∑yi)^2) )
    double sum_x = M->getAbsIndex(0, 1);
    double sum_y = Y->getAbsIndex(0, 1);
    double sum_xy = Y->getAbsIndex(0, 0);
    double sum_xx = M->getAbsIndex(0, 0);
    double sum_yy = innerProd(y, y);

    double r2 = pow(m * sum_xy - sum_x * sum_y, 2) / ((m * sum_xx - pow(sum_x, 2)) * (m * sum_yy - pow(sum_y, 2)));

    printf("The solution is: \n");
    sol->print();

    printf("R^2 is: %lf", r2);
    return 0;
}