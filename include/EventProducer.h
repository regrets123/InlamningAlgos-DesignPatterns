//
#ifndef INLAMNINGALGOS_DESIGNPATTERNS_EVENTPRODUCER_H
#define INLAMNINGALGOS_DESIGNPATTERNS_EVENTPRODUCER_H
#include <time.h>
#include "Event.h"
#include "EventQueue.h"

static size_t eventCount = 0;
static EventQueue* queue = NULL;
static Event*  eventPool = NULL;
const static size_t queueInitCapacity = 50;
static size_t eventPoolSize = 0;
static size_t eventPoolCapacity = 0;

Event createEvent(time_t timestamp, int sensorId, enum type type, int value);
bool ensureQueueInitialized();

void tick(int iterations);

#endif //INLAMNINGALGOS_DESIGNPATTERNS_EVENTPRODUCER_H