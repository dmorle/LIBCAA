#include "polynomial.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_SIZE 64

namespace cl = LIBCAA;

enum MainMenuAction {
    INVALID,
    NEW,
    SWITCH,
    DEL,
    LS,
    PRINT,
    PRINTD,
    SAVED,
    EVAL,
    ROOTS1,
    ROOTS2,
    ROOTS3,
    EXIT
};

class {

public:
    void start() {
        this->descriptions = {
            "Create a new polynomial",
            "Switch to an existing polynomial",
            "Delete a stored polynomial",
            "List the stored polynomials",
            "View the current polynomial",
            "View the current polynomial's derivative",
            "Save the current polynomial's derivative",
            "Evaluate the current polynomial",
            "Find roots for the polynomial (Bisection)",
            "Find roots for the polynomial (False Position)",
            "Find roots for the polynomial (Newton-Raphson)",
            "Exit the program"
        };
        this->options = {
            "new\n",
            "switch\n",
            "del\n",
            "ls\n",
            "print\n",
            "print d/dx\n",
            "save d/dx\n",
            "eval\n",
            "roots1\n",
            "roots2\n",
            "roots3\n",
            "exit\n"
        };

        while (1) {
            // getting an action from the user
            MainMenuAction action = getMainAction();

            // doing the action
            switch (action) {
                case NEW:
                    newPoly();
                    break;
                case SWITCH:
                    switchPoly();
                    break;
                case DEL:
                    delPoly();
                    break;
                case LS:
                    lsPoly();
                    break;
                case PRINT:
                    if (!checkInit()) {
                        printf("There are no polynomials created yet\nCreate one with the 'new' command\n\n");
                        break;
                    }
                    printPoly();
                    break;
                case PRINTD:
                    if (!checkInit()) {
                        printf("There are no polynomials created yet\nCreate one with the 'new' command\n\n");
                        break;
                    }
                    printDeriv();
                    break;
                case SAVED:
                    if (!checkInit()) {
                        printf("There are no polynomials created yet\nCreate one with the 'new' command\n\n");
                        break;
                    }
                    saveDeriv();
                    break;
                case EVAL:
                    if (!checkInit()) {
                        printf("There are no polynomials created yet\nCreate one with the 'new' command\n\n");
                        break;
                    }
                    eval();
                    break;
                case ROOTS1:
                    if (!checkInit()) {
                        printf("There are no polynomials created yet\nCreate one with the 'new' command\n\n");
                        break;
                    }
                    getRoots1();
                    break;
                case ROOTS2:
                    if (!checkInit()) {
                        printf("There are no polynomials created yet\nCreate one with the 'new' command\n\n");
                        break;
                    }
                    getRoots2();
                    break;
                case ROOTS3:
                    if (!checkInit()) {
                        printf("There are no polynomials created yet\nCreate one with the 'new' command\n\n");
                        break;
                    }
                    getRoots3();
                    break;
                case EXIT:
                    return;
            }
        }
    }

private:
    std::vector<std::string> descriptions;
    std::vector<std::string> options;
    std::vector<cl::polynomial *> polys;

    int currentPoly = -1;

    MainMenuAction getMainAction() {
        // flushing the input stream

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
        fflush(stdin);
        if (fgets(input, MAX_SIZE, stdin))
            decodeInput();

        // invalid action loop
        while (act == INVALID) {
            printf("\nInvalid Action\n\n");
            printOptions();
            fflush(stdin);
            if (fgets(input, MAX_SIZE, stdin))
                decodeInput();
        }
        
        return act;
    }

    void newPoly() {

        // getting a name for the polynomial
        char tempName[MAX_SIZE];
        auto formatTempName = [&] () {
            for (int i = 0; i < MAX_SIZE; i++)
                if (!tempName[i] || tempName[i] == '\n') {
                    tempName[i] = '\0';
                    break;
                }
        };

        sprintf(tempName, "%s%d", "poly", polys.size());     // default name
        std::string name(tempName);
        
        printf("Enter a name for the polynomial (nothing creates a default name): ");
        if (fgets(tempName, MAX_SIZE, stdin)) {
            if (tempName[0] != '\n') {
                formatTempName();
                name = std::string(tempName);
            }
        }

        // getting degree from user
        int degree;

        printf("Please enter the degree of your polynomial: ");
        scanf("%d", &degree);

        // loop preventing negative degrees
        while (degree < 0) {
            printf("Invalid Input\n\nPlease enter the degree of your polynomial: ");
            scanf("%d", &degree);
        }

        // getting the coefficients of the polynomial
        double *coeff = (double *)malloc(sizeof(double) * (degree + 1));
        for (int i = degree; i >= 0; i--) {
            printf("Please enter the coefficent for x^%d: ", i);
            scanf("%lf", &coeff[i]);
        }

        cl::polynomial *npPoly = new cl::polynomial(name, degree);
        npPoly->forceSetData(coeff);

        polys.push_back(npPoly);

        currentPoly = polys.size() - 1;

        printf("\n");
        getchar();
    }

    void switchPoly() {
        int index = getPolyIndex();

        if (index == -2)
            printf("\nThere are no polynomials created yet\nCreate one with the 'new' command\n\n");

        else if (index == -1)
            printf("\nExiting the load protocol\n\n");

        else {
            printf("\nswitching to %s\n\n", polys[index]->name.c_str());
            currentPoly = index;
        }
    }

    void delPoly() {
        int index = this->getPolyIndex();

        if (index == -2)
            printf("\nThere are no polynomials created yet\nCreate one with the 'new' command\n\n");

        else if (index == -1)
            printf("\nExiting the delete protocol\n\n");

        else if (currentPoly == index) 
            printf("\nCannot delete the current polynomial\nExiting the delete protocol\n\n");
            
        else {
            printf("\ndeleting %s\n\n", polys[index]->name.c_str());
            currentPoly--;

            delete polys[index];
            polys.erase(polys.begin() + index);
        }
    }

    void lsPoly() {
        printf("\nStored polynomials listed below: \n\n");
        for (int i = 0; i < polys.size(); i++)
            printf("%s\n", polys[i]->name.c_str());
        printf("\n");
    }

    void printPoly() {
        cl::polynomial *pPoly = polys[currentPoly];

        printf("\n%s:\n", pPoly->name.c_str());
        for (int i = pPoly->getLen() - 1; i >= 0; i--) {
            if (pPoly->getIndex(i) == 0) {
                if (i == 0 && pPoly->getLen() == 1) {
                    printf("0");
                }
            }
            else {
                if (pPoly->getIndex(i) > 0)
                    printf(" +");
                printf(" %.3f", pPoly->getIndex(i));
                if (i >= 1) {
                    printf("x");
                    if (i > 1)
                        printf("^%d", i);
                }
            }
        }
        printf("\n\n");
    }

    void printDeriv() {
        cl::polynomial *pPoly = polys[currentPoly]->getDerivative();

        printf("\n%s:\n", pPoly->name.c_str());
        for (int i = pPoly->getLen() - 1; i >= 0; i--) {
            if (pPoly->getIndex(i) == 0) {
                if (i == 0 && pPoly->getLen() == 1) {
                    printf("0");
                }
            }
            else {
                if (pPoly->getIndex(i) > 0)
                    printf(" +");
                printf(" %.3f", pPoly->getIndex(i));
                if (i >= 1) {
                    printf("x");
                    if (i > 1)
                        printf("^%d", i);
                }
            }
        }
        printf("\n\n");

        delete pPoly;
    }

    void saveDeriv() {
        cl::polynomial *pPoly = polys[currentPoly]->getDerivative();
        polys.push_back(pPoly);
    }

    void eval() {
        double x;

        printf("\nPlease enter a value for the polynomial to be evaluated at: ");
        scanf("%lf", &x);
        getchar();  // clearing the leftover \n from stdin

        printf("The polynomial evaluated at %f is: %f\n\n", x, polys[currentPoly]->eval(x));
    }

    void getRoots1() {
        cl::polynomial *func = polys[currentPoly];

        double oldGuess;
        double newGuess;
        
        double ea;

        auto calcError = [&] () {
            ea = fabs((oldGuess-newGuess)/newGuess);
        };

        double es;
        printf("Please enter a value for the error tolerance: ");
        scanf("%lf", &es);
        
        double guess1;
        printf("Please enter the first value for bisection method: ");
        scanf("%lf", &guess1);

        double guess2;
        printf("Please enter the second value for bisection method: ");
        scanf("%lf", &guess2);

        // check for if the root is findable
        if (func->eval(guess1) * func->eval(guess2) > 0) {
            printf("Unable to find a root from the given initial values\n\n");
            return;
        }

        int maxIter;
        printf("Please enter the number of maximum iterations: ");
        scanf("%d", &maxIter);
        getchar();  // clearing the leftover \n from stdin

        bool foundVal = false;
        for (int i = 0; i < maxIter; i++) {
            newGuess = (guess1 + guess2)/2;
            if (func->eval(guess1) * func->eval(newGuess) > 0) {
                oldGuess = guess1;
                guess1 = newGuess;
            }
            else {
                oldGuess = guess2;
                guess2 = newGuess;
            }
            calcError();
            if (ea < es) {
                foundVal = true;
                break;
            }
        }

        printf("\nAn %s root of this polynomial is: %f\n\n", foundVal ? "accurate" : "inaccurate", newGuess);
    }

    void getRoots2() {
        cl::polynomial *func = polys[currentPoly];

        double oldGuess;
        double newGuess;
        
        double ea;

        auto calcError = [&] () {
            ea = fabs((oldGuess-newGuess)/newGuess);
        };

        double es;
        printf("Please enter a value for the error tolerance: ");
        scanf("%lf", &es);
        
        double guess1;
        printf("Please enter the first value for false position method: ");
        scanf("%lf", &guess1);

        double guess2;
        printf("Please enter the second value for false position method: ");
        scanf("%lf", &guess2);

        // check for if the root is findable
        if (func->eval(guess1) * func->eval(guess2) > 0) {
            printf("Unable to find a root from the given initial values\n\n");
            return;
        }

        int maxIter;
        printf("Please enter the number of maximum iterations: ");
        scanf("%d", &maxIter);
        getchar();  // clearing the leftover \n from stdin

        bool foundVal = false;
        for (int i = 0; i < maxIter; i++){
            newGuess = guess2 - func->eval(guess2)*(guess1 - guess2)/(func->eval(guess1)-func->eval(guess2));
            if (func->eval(guess1) * func->eval(newGuess) > 0) {
                oldGuess = guess1;
                guess1 = newGuess;
            }
            else {
                oldGuess = guess2;
                guess2 = newGuess;
            }
            calcError();
            if(ea < es) {
                foundVal = true;
                break;
            }
        }

        printf("\nAn %s root of this polynomial is: %f\n\n", foundVal ? "accurate" : "inaccurate", newGuess);
    }

    void getRoots3() {
        cl::polynomial *func = polys[currentPoly];
        cl::polynomial *derivative = func->getDerivative();

        double es;
        printf("Please enter a value for the error tolerance: ");
        scanf("%lf", &es);

        double oldGuess;
        double guess;
        printf("Please enter an initial value for the newton-raphson method: ");
        scanf("%lf", &guess);

        double ea;

        auto calcError = [&] () {
            ea = fabs((oldGuess-guess)/guess);
        };

        int maxIter;
        printf("Please enter the number of maximum iterations: ");
        scanf("%d", &maxIter);
        getchar();  // clearing the leftover \n from stdin
        
        bool foundVal = false;
        for (int i = 0; i < maxIter; i++) {
            oldGuess = guess;
            guess -= func->eval(guess)/derivative->eval(guess);
            calcError();
            if (ea < es) {
                foundVal = true;
                break;
            }
        }

        printf("\nAn %s root of this polynomial is: %f\n\n", foundVal ? "accurate" : "inaccurate", guess);
    }

    // returns -2 if the list is empty
    // returns -1 if user cancelled
    // returns the index otherwise
    int getPolyIndex() {
        if (!checkInit())
            return -2;
        
        char searchName[MAX_SIZE];
        int index = -1;

        auto formatSearchName = [&] () {
            for (int i = 0; i < MAX_SIZE; i++)
                if (!searchName[i] || searchName[i] == '\n') {
                    searchName[i] = '\0';
                    break;
                }
        };

        auto decodeName = [&] () {
            for (int i = 0; i < this->polys.size(); i++) {
                if (!strcmp(searchName, this->polys[i]->name.c_str())) {
                    index = i;
                    break;
                }
            }
        };
        
        lsPoly();
        printf("type 'exit' to cancel\n");
        fgets(searchName, MAX_SIZE, stdin);
        formatSearchName();
        if (!strcmp(searchName, "exit"))
            return -1;
        
        decodeName();

        while (index == -1) {
            printf("Invalid Name\n\n");
            lsPoly();
            printf("type 'exit' to cancel\n");
            fgets(searchName, MAX_SIZE, stdin);
            formatSearchName();
            if (!strcmp(searchName, "exit"))
                return -1;
            
            decodeName();
        }

        return index;
    }

    bool checkInit() {
        if (polys.size())
            return true;
        return false;
    }

} ConsoleUI;


int main() {
    ConsoleUI.start();
    return 0;
}