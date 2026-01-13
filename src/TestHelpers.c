#include <stdio.h>
#include "TestHelpers.h"
#include "EventLog.h"
#include "EventQueue.h"

void print_event(Event e) {
    const char* type_str[] = {"NONE", "TEMP", "BUTTON", "MOTION"};
    printf("Event[time=%d, sensor=%d, type=%s, value=%d]\n",
           e.timeStamp, e.sensorId, type_str[e.type], e.value);
}

void test_eventLog() {

}

void test_eventQueue() {

}