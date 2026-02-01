#include "UserInterface.h"
#include "EventProducer.h"
#include "EventSort.h"
#include "TestHelpers.h"
#include "AppState.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

bool readValidInt(const char *input, int *result) {
    if (input == NULL || *input == '\0') {
        return false;
    }
    errno = 0;
    char *endPtr;
    const long value = strtol(input, &endPtr, 10);
    if (errno == ERANGE || value < INT_MIN || value > INT_MAX) {
        return false;
    }
    while (*endPtr != '\0' && isspace((unsigned char)*endPtr)) {
        endPtr++;
    }
    if (*endPtr != '\0') {
        return false;
    }
    *result = (int)value;
    return true;
}

void printMenu() {
    printf(" This is an eventLogger, tick registers n amount of events.\n Menu:\n");
    printf("1. Tick\n");
    printf("2. Print\n");
    printf("3. Sort\n");
    printf("4. Find\n");
    printf("5. Help\n");
    printf("6. Test\n");
    printf("7. Quit\n");
}

int readInput() {
    char buffer[64];
    int choice;
    while (true) {
        printf("Enter your choice: ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            return -1;
        }
        buffer[strcspn(buffer, "\n")] = '\0';
        if (readValidInt(buffer, &choice)) {
            return choice;
        }
        printf("Invalid input. Please enter a number.\n");
    }
}

void handleUserInput(menuOptions option) {
    switch (option) {
        case tickState: {
                printf("Input how many tics, must be higher than 1, will be capped at 200.\n");
                int input = -1;
                while (input < 0 )
                {
                    input = readInput();
                    if (readInput() > 200 )
                    {
                        input = 200;
                        printf("Input set to 200.\n");
                    }
                    else if (readInput() < 1)
                    {
                        printf("Input set to 1.\n");
                    }
                }
                tick(input);
            break;
        }
        case printState: {
            printf("Queue size: %zu\n", queue_size(appState_get()->queue));
            printf("Event Log contains the following:\n");
            size_t logSize = log_size(appState_get()->log);
            for (size_t i = 0; i < logSize; i++) {
                print_event(log_Get(appState_get()->log, (int)i));
            }
            break;
        }
        case sort: {
                int chosenSort = handleSortInput();
                int chosenComparator = selectComparator();
                startSorting(chosenSort, chosenComparator);

            break;
        }
        case find: {
            printf("Enter sensor ID to search for: ");
            int sensorId = readInput();
            size_t logSize = log_size(appState_get()->log);
            int found = 0;
            for (size_t i = 0; i < logSize; i++) {
                const Event* e = log_Get(appState_get()->log, (int)i);
                if (e != NULL && e->sensorId == sensorId) {
                    print_event(e);
                    found++;
                }
            }
            if (found == 0) {
                printf("No events found with sensor ID %d.\n", sensorId);
            } else {
                printf("Found %d event(s) with sensor ID %d.\n", found, sensorId);
            }
            break;
        }
        case help: {
            break;
        }
        case test: {
                test_eventLog();
                test_eventQueue();
                test_eventPoolRebase();
                test_eventSort();
            break;
        }
        case quit: {
                appState_get()->currentOption = quit;
            break;
        }
        default: {
            break;
        }
    }
}

int handleSortInput(){
    printf("Input what sorting option you want to use. 1: BubbleSort, 2: SelectionSort, 3:InsertionSort.");
    int input =  -1;
    while (input < 1)
    {
        input = readInput();
        if (readInput() > 3 )
        {
            input = -1;
            printf("Invalid input, please enter a value between 1-3.\n");
        }
        else if (readInput() < 1)
        {
            printf("Invalid input, please enter a value between 1-3.\n");
        }
    }
    return input;
}

int selectComparator(){
    printf("Input what comparator you want to use. 1: Timestamp, 2: SensorId, 3: Value, 4: Type.");
    int input =  -1;
    while (input < 1)
    {
        input = readInput();
        if (readInput() > 4 )
        {
            input = -1;
            printf("Invalid input, please enter a value between 1-4.\n");
        }
        else if (readInput() < 1)
        {
            printf("Invalid input, please enter a value between 1-4.\n");
        }
    }
    return input;
}

void startSorting(int chosenSort, int chosenComparator)
{
    SortFunction sortFn = NULL;
    switch ((sortOptions)chosenSort) {
        case sort_bubble: {
            sortFn = bubbleSort;
            break;
        }
        case sort_selection: {
            sortFn = selectionSort;
            break;
        }
        case sort_insertion: {
            sortFn = insertionSort;
            break;
        }
        default: {
            printf("Invalid sort option.\n");
            return;
        }
    }

    EventComparator cmp = NULL;
    switch ((comparatorOptions)chosenComparator) {
        case byTimestamp: {
            cmp = compareByTimestamp;
            break;
        }
        case bySensorId: {
            cmp = compareBySensorId;
            break;
        }
        case byValue: {
            cmp = compareByValue;
            break;
        }
        case byType: {
            cmp = compareByType;
            break;
        }
        default: {
            printf("Invalid comparator option.\n");
            return;
        }
    }
    sortLog(appState_get()->log, sortFn, cmp);
}

bool interfaceLoop() {
    return true;
}
