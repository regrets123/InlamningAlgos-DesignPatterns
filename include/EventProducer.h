//
#ifndef INLAMNINGALGOS_DESIGNPATTERNS_EVENTPRODUCER_H
#define INLAMNINGALGOS_DESIGNPATTERNS_EVENTPRODUCER_H
#include <time.h>
#include "Event.h"
#include "EventQueue.h"

static int eventCount = 0;
static EventQueue* queue = NULL;
const static int queueInitCapacity = 50;

Event* createEvent(time_t timestamp, int sensorId, enum type type, int value);
bool ensureQueueInitialized();

void tick(int iterations);

#endif //INLAMNINGALGOS_DESIGNPATTERNS_EVENTPRODUCER_H