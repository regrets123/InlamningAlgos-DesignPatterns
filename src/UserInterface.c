#include "UserInterface.h"
#include "EventProducer.h"
#include "EventConsumer.h"
#include "TestHelpers.h"
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
            printf("Queue size: %zu\n", queue_size(queue));
            printf("Event Log contains the following:\n");
            size_t logSize = log_size(log);
            for (size_t i = 0; i < logSize; i++) {
                print_event(log_Get(log, (int)i));
            }
            break;
        }
        case sort: {
            break;
        }
        case find: {
            printf("Enter sensor ID to search for: ");
            int sensorId = readInput();
            size_t logSize = log_size(log);
            int found = 0;
            for (size_t i = 0; i < logSize; i++) {
                const Event* e = log_Get(log, (int)i);
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
                test_eventSort();
            break;
        }
        case quit: {
                currentOption = quit;
            break;
        }
        default: {
            break;
        }
    }
}

bool interfaceLoop() {
    return true;
}
//
