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

    A->print();
    Atrans->print();

    matrix M = matmul(Atrans, A);
    matrix Y = matmul(Atrans, y);
    f.release(A);
    f.release(Atrans);

    M->print();

    matrix M1 = inv(M);
    matrix sol = matmul(M1, Y);
    f.release(M1);

    sol->print();
    return 0;
}