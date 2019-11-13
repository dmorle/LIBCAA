#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "Factory.hpp"

#define USE_OBJ_MACROS
#define USE_OP_MACROS
#include "stdAlias.hpp"

#define MAX_SIZE 64

enum MainMenuAction {
    INVALID,
    EXIT
};

class {

public:
    void start() {
        this->descriptions = {
            "Exit the program"
        };
        this->options = {
            "exit\n"
        };

        while (1) {
            // getting an action from the user
            MainMenuAction action = getMainAction();

            // doing the action
            switch (action) {
                case EXIT:
                    return;
            }
        }
    }

private:
    MainMenuAction getMainAction() {
        // flushing the input stream
        fflush(stdin);

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

    std::vector<std::string> descriptions;
    std::vector<std::string> options;
} ConsoleUI;


int main() {
    ConsoleUI.start();
    return 0;
}