//
#include "EventProducer.h"
#include <stdlib.h>
#include "Event.h"

bool ensureQueueInitialized() {
    if (queue == NULL) {
        queue = queue_create(queueInitCapacity);
    }
    return queue != NULL;
}

void tick(int iterations) {
    for (int i = 0; i < iterations; i++) {
        Event* newEvent = malloc(sizeof(Event));
        enum type randomType = NONE + 1 + rand() % (MAXNUM - 1);
        int randomValue = rand() % 1000;
        newEvent = createEvent(time(NULL), eventCount++,randomType,randomValue);
        queue_enqueue(queue, newEvent);
    }
}
