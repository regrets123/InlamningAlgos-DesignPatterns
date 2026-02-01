#ifndef INLAMNINGALGOS_DESIGNPATTERNS_USERINTERFACE_H
#define INLAMNINGALGOS_DESIGNPATTERNS_USERINTERFACE_H
#include <stdbool.h>

typedef enum menuOptions {none, tickState, printState, sort, find, help, test, quit, maxNum}
menuOptions;
typedef enum sortOptions {noSort, sort_bubble, sort_selection, sort_insertion, maxValue}
sortOptions;
typedef enum comparatorOptions {noComparator, byTimestamp, bySensorId, byValue, byType, maxComparator}
comparatorOptions;

void printMenu();
int readInput();
bool readValidInt(const char *input, int *result);
void handleUserInput(menuOptions option);
int handleSortInput();
int selectComparator();
void startSorting(int chosenSort, int chosenComparator);
bool interfaceLoop();

#endif //INLAMNINGALGOS_DESIGNPATTERNS_USERINTERFACE_H