#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "EventConsumer.h"
#include "EventProducer.h"
#include "TestHelpers.h"

int main() {
    srand(time(NULL));
    if (!ensureQueueInitialized() || !ensureLogInitialized()) {
        return 1;
    }
    test_eventLog();
    test_eventQueue();
    printf("All tests completed!\n");
    tick(10);
    queue_destroy(queue);
    free(queue);
    return 0;
}