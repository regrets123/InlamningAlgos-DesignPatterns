//
#ifndef INLAMNINGALGOS_DESIGNPATTERNS_EVENT_H
#define INLAMNINGALGOS_DESIGNPATTERNS_EVENT_H

#include <time.h>
enum type {NONE, TEMP, BUTTON, MOTION, MAXTYPE};

typedef struct Event {
    time_t timeStamp;
    int sensorId;
    enum type type;
    int value;
} Event;

#endif //INLAMNINGALGOS_DESIGNPATTERNS_EVENT_H