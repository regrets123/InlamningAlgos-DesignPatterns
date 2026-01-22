#ifndef INLAMNINGALGOS_DESIGNPATTERNS_USERINTERFACE_H
#define INLAMNINGALGOS_DESIGNPATTERNS_USERINTERFACE_H
#include <stdbool.h>

typedef enum menuOptions {none, tick, print, sort, find, help, test, exit, maxNum}
menuOptions;

void PrintMenu();
void HandleUserInput(menuOptions option);
bool InterfaceLoop();

#endif //INLAMNINGALGOS_DESIGNPATTERNS_USERINTERFACE_H