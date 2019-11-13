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
            "Exit the program"
        };
        this->options = {
            "linsys\n",
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

    std::vector<std::string> descriptions;
    std::vector<std::string> options;
} ConsoleUI;


int main() {
    ConsoleUI.start();
    return 0;
}