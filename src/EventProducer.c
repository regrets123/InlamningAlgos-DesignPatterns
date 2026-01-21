//
#include <stdlib.h>
#include "EventProducer.h"
#include "Event.h"
#include "EventConsumer.h"
#include "EventLog.h"

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
    if (eventPoolSize + iterations > eventPoolCapacity) {
        eventPoolCapacity = (eventPoolCapacity == 0) ? iterations : eventPoolCapacity * 2;
        eventPool = realloc(eventPool, sizeof(Event) * eventPoolCapacity);
    }

    for (int i = 0; i < iterations; i++) {
        Event* newEvent = &eventPool[eventPoolSize++];
        enum type randomType = NONE + 1 + rand() % (MAXNUM - 1);
        int randomValue = rand() % 1000;
        *newEvent = createEvent(time(NULL), eventCount++,randomType,randomValue);
        queue_enqueue(queue, newEvent);
    }
    for (int i = 0; i < iterations; i++) {

        log_append(log, queue_dequeue(queue));
    }
}
