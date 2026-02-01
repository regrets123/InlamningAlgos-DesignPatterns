//
#ifndef INLAMNINGALGOS_DESIGNPATTERNS_EVENTPRODUCER_H
#define INLAMNINGALGOS_DESIGNPATTERNS_EVENTPRODUCER_H
#include <time.h>
#include "Event.h"

Event createEvent(time_t timestamp, int sensorId, enum type type, int value);
time_t rewindTime(time_t time, int seconds);

void tick(int iterations);

#endif //INLAMNINGALGOS_DESIGNPATTERNS_EVENTPRODUCER_H
