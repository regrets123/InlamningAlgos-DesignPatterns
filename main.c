#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "EventConsumer.h"
#include "EventProducer.h"
#include "UserInterface.h"

int main() {
    srand(time(NULL));
    if (!ensureQueueInitialized() || !ensureLogInitialized()) {
        return 1;
    }
    while (currentOption != quit)
    {
        printMenu();
        const int input = readInput();
        handleUserInput(input);
    }
    queue_destroy(queue);
    free(queue);
    return 0;
}
