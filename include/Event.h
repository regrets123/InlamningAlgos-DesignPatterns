//
#ifndef INLAMNINGALGOS_DESIGNPATTERNS_EVENT_H
#define INLAMNINGALGOS_DESIGNPATTERNS_EVENT_H

typedef struct Event Event;
typedef enum type {NONE, TEMP, BUTTON, MOTION};

struct Event {
    int timeStamp;
    int sensorId;
    enum type type;
    int value;
};


#endif //INLAMNINGALGOS_DESIGNPATTERNS_EVENT_H