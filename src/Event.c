#include "Event.h"

void print_event(const Event* e) {
    if (!e) {
        printf("Event[NULL]\n");
        return;
    }
    const char* type_str[] = {"NONE", "TEMP", "BUTTON", "MOTION"};
    printf("Event[time=%lld, sensor=%d, type=%s, value=%d]\n",
           e->timeStamp, e->sensorId, type_str[e->type], e->value);
}