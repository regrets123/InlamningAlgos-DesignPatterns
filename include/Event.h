//
#ifndef INLAMNINGALGOS_DESIGNPATTERNS_EVENT_H
#define INLAMNINGALGOS_DESIGNPATTERNS_EVENT_H
enum type {NONE, TEMP, BUTTON, MOTION};

typedef struct Event {
    int timeStamp;
    int sensorId;
    enum type type;
    int value;
} Event;

#endif //INLAMNINGALGOS_DESIGNPATTERNS_EVENT_H