//
#include <stdlib.h>
#include <stdio.h>
#include "EventProducer.h"
#include "Event.h"
#include "EventConsumer.h"
#include "AppState.h"

Event createEvent(time_t timestamp, int sensorId, enum type type, int value) {
    Event e;
    e.timeStamp = timestamp;
    e.sensorId = sensorId;
    e.type = type;
    e.value = value;
    return e;
}

void tick(int iterations) {
    AppState* state = appState_get();

    if (state->eventPoolSize + iterations > state->eventPoolCapacity) {
        size_t newCapacity = (state->eventPoolCapacity == 0) ? iterations : state->eventPoolCapacity * 2;
        Event* newPool = realloc(state->eventPool, sizeof(Event) * newCapacity);
        if (!newPool) {
            printf("Pool realloc failed, keeping current capacity of %zu.\n", state->eventPoolCapacity);
            return;
        }
        if (state->eventPool != NULL && newPool != state->eventPool) {
            ptrdiff_t delta = (char*)newPool - (char*)state->eventPool;
            log_rebase(state->log, delta);
        }
        state->eventPool = newPool;
        state->eventPoolCapacity = newCapacity;
    }

    int produced = 0;
    while (produced < iterations) {
        while (produced < iterations && !queue_is_full(state->queue)) {
            Event* newEvent = &state->eventPool[state->eventPoolSize++];
            enum type randomType = NONE + 1 + rand() % (MAXTYPE - 1);
            int randomValue = rand() % 1000;
            *newEvent = createEvent(rewindTime(time(NULL), produced), state->eventCount++, randomType, randomValue);
            queue_enqueue(state->queue, newEvent);
            produced++;
        }
        while (!queue_is_empty(state->queue)) {
            consumeEvent(state->queue);
        }
    }
}

time_t rewindTime(time_t time, int seconds)
{
    return time - seconds;
}
