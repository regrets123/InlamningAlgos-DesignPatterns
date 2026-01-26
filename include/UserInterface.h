#ifndef INLAMNINGALGOS_DESIGNPATTERNS_USERINTERFACE_H
#define INLAMNINGALGOS_DESIGNPATTERNS_USERINTERFACE_H
#include <stdbool.h>

typedef enum menuOptions {none, tickState, printState, sort, find, help, test, quit, maxNum}
menuOptions;

static menuOptions currentOption = none;

void printMenu();
int readInput();
bool readValidInt(const char *input, int *result);
void handleUserInput(menuOptions option);
bool interfaceLoop();

#endif //INLAMNINGALGOS_DESIGNPATTERNS_USERINTERFACE_H