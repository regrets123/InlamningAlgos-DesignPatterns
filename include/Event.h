//
#ifndef INLAMNINGALGOS_DESIGNPATTERNS_EVENT_H
#define INLAMNINGALGOS_DESIGNPATTERNS_EVENT_H

#include <stdio.h>
#include <time.h>
enum type {NONE, TEMP, BUTTON, MOTION, MAXTYPE};

typedef struct Event {
    time_t timeStamp;
    int sensorId;
    enum type type;
    int value;
} Event;

void print_event(const Event* e) {
    if (!e) {
        printf("Event[NULL]\n");
        return;
    }
    const char* type_str[] = {"NONE", "TEMP", "BUTTON", "MOTION"};
    printf("Event[time=%lld, sensor=%d, type=%s, value=%d]\n",
           e->timeStamp, e->sensorId, type_str[e->type], e->value);
}

#endif //INLAMNINGALGOS_DESIGNPATTERNS_EVENT_H