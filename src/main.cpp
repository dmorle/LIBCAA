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

enum MainMenuAction {
    INVALID,
    LINSYS,
    SIMPLEX,
    EXIT
};

class {

public:
    void start()
    {
        this->descriptions = {
            "Solve a linear system",
            "Solve simplex "
            "Exit the program"
        };
        this->options = {
            "linsys\n",
            "simplex\n",
            "exit\n"
        };

        while (1) {
            // getting an action from the user
            MainMenuAction action = getMainAction();

            // doing the action
            switch (action) {
                case LINSYS:
                    solveLinearSystem();
                    break;
                case SIMPLEX:
                    solveConstraintOpt();
                    break;
                case EXIT:
                    return;
            }
        }
    }

private:
    MainMenuAction getMainAction()
    {
        // lambda for printing user options
        auto printOptions = [&] () {
            for (int i = 0; i < options.size(); i++)
                printf("%48s <=> %s", descriptions[i].c_str(), options[i].c_str());
            
            printf("\nPlease enter your action: ");
        };

        // input and output
        char input[MAX_SIZE];
        MainMenuAction act = INVALID;

        // decodes input into act if possible
        auto decodeInput = [&] () {
            for (int i = 0; i < options.size(); i++)
                if(!strcmp(input, options[i].c_str()))
                    act = (MainMenuAction)(i + 1);
        };

        // gets action from user
        printOptions();
        __fpurge(stdin);
        if (fgets(input, MAX_SIZE, stdin))
            decodeInput();

        // invalid action loop
        while (act == INVALID) {
            printf("\nInvalid Action\n\n");
            printOptions();
            __fpurge(stdin);
            if (fgets(input, MAX_SIZE, stdin))
                decodeInput();
        }
        
        return act;
    }

    void solveLinearSystem()
    {
        LIBCAA::Factory fact;

        // getting the m value for the matrix
        int size;
        printf("Please enter the number of equations/variables in your system: ");
        scanf("%d", &size);
        while (size < 1) {
            printf("Invalid Input\n\nPlease enter the number of equations/variables in your system: ");
            scanf("%d", &size);
        }

        // getting the value for the matrix
        printf("Please enter your matrix of coefficients: \n");
        matrix x = fact.usrInit(size, size);

        // getting the constant values of the system
        printf("Please enter the constant values of your equations: \n");
        vector y = fact.usrInit(size);

        // solving the system
        try {
            matrix xInv = inv(x);
            vector solution = matmul(xInv, y);

            // displaying the solution
            printf("the solution is: \n");
            solution->print();
            printf("\n");

            // freeing local memory
            fact.release(xInv);
            fact.release(solution);
        }
        catch (LIBCAA::invEx) {
            printf("The system of equations provided has no solution\n\n");
        }

        // freeing memory
        fact.release(x);
        fact.release(y);
    }

    void solveConstraintOpt() {
        LIBCAA::Factory f;

        int m;
        printf("Please enter the number of constraints: ");
        scanf("%d", &m);

        int n;
        printf("Please enter the number of variables: ");
        scanf("%d", &n);

        if (m <= 0 || n <= 0) {
            printf("\n\nInvalid Input(s)\n\n");
            return;
        }

        printf("Please enter the coefficients of the constraints (a_ij): \n");
        matrix A = f.usrInit(m, n);

        printf("Please enter the coefficients of the objective function (c_i): \n");
        matrix c = f.usrInit(1, n);

        printf("Please enter the constraining values (b_i): \n");
        matrix b = f.usrInit(m, 1);


        matrix idn = f.identity(m);
        matrix zeros = f.constant(1, m + 1);

        

        while ()
            int j0 = getMaxIndex(c);
            int i0 = 0;
            for (int i = 1; i < n; i++) {
                if (!A->getIndex(i0, j0)) {
                    i0 = i;
                    continue;
                }
                
                if (!A->getIndex(i, j0))
                    continue;

                if (b->getIndex(i)/A->getIndex(i, j0) < b->getIndex(i0)/A->getIndex(i0, j0))
                    i0 = i;
            }

            double pivotVal = 1/A->getIndex(i0, j0);
            A->scaleRow(i0, pivotVal);
            idn->scaleRow(i0, pivotVal);
            b->scaleRow(i0, pivotVal);

            for (int i = 0; i < n; i++)
                if (i != i0) {
                    A->rowSub(i, i0, A->getIndex(i, j0));
                    idn->rowSub(i, i0, A->getIndex(i, j0));
                    b->rowSub(i, i0, A->getIndex(i, j0));
                }
            
            for (int j = 0; j < m; j++) {
                c->setIndex(0, j, c->getIndex(0, j) - c->getIndex(0, j0) * A->getIndex(i0, j));
            }

        // concatonating the matricies
        // matrix left = concat(constrainFunc, objFunc, 0);
        // matrix upperRight = concat(idn, constrainVals, 1);
        // matrix right = concat(upperRight, zeros, 0);

        // matrix mrx = concat(left, right, 1);
        
        // // releasing unnessisary matricies
        // f.release(constrainFunc);
        // f.release(objFunc);
        // f.release(constrainVals);
        // f.release(idn);
        // f.release(zeros);
        // f.release(left);
        // f.release(upperRight);
        // f.release(right);


        // mrx->print();

        // f.release(mrx);


    }

    std::vector<std::string> descriptions;
    std::vector<std::string> options;
} ConsoleUI;


int main() {
    ConsoleUI.start();
    return 0;
}