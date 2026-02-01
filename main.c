#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "UserInterface.h"
#include "AppState.h"

int main() {
    srand(time(NULL));
    if (!appState_get()) {
        return 1;
    }
    while (appState_get()->currentOption != quit)
    {
        printMenu();
        const int input = readInput();
        handleUserInput(input);
    }
    appState_destroy();
    return 0;
}
