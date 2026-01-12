//
#ifndef INLAMNINGALGOS_DESIGNPATTERNS_EVENTPRODUCER_H
#define INLAMNINGALGOS_DESIGNPATTERNS_EVENTPRODUCER_H
#include "Event.h"

Event* createEvent(int sensorId, enum type type, int prio);
void tick(int iterations);

#endif //INLAMNINGALGOS_DESIGNPATTERNS_EVENTPRODUCER_H