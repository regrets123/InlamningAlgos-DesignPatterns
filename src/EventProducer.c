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

Event createEvent(time_t timestamp, int sensorId, enum type type, int value) {
    Event e;
    e.timeStamp = timestamp;
    e.sensorId = sensorId;
    e.type = type;
    e.value = value;
    return e;
}


void tick(int iterations) {
    // Ensure we have space
    if (eventPoolSize + iterations > eventPoolCapacity) {
        eventPoolCapacity = (eventPoolCapacity == 0) ? iterations : eventPoolCapacity * 2;
        eventPool = realloc(eventPool, sizeof(Event) * eventPoolCapacity);
    }

    // Create events directly in the pool
    for (int i = 0; i < iterations; i++) {
        Event* newEvent = &eventPool[eventPoolSize++];
        enum type randomType = NONE + 1 + rand() % (MAXNUM - 1);
        int randomValue = rand() % 1000;
        *newEvent = createEvent(time(NULL), eventCount++,randomType,randomValue);
        queue_enqueue(queue, newEvent);
    }
}
