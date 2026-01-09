#include "include/Eventlog.h"
#include "include/Event.h"
#include <stdlib.h>

struct EventLog {
    Event* events;
    size_t size;
    size_t capacity;
};

EventLog* log_create(size_t capacity) {
    EventLog* log = malloc(sizeof(EventLog));
    if (!log) return NULL;
    log->events = malloc(capacity * sizeof(Event));
    if (!log->events) {
        free(log);
        return NULL;
    }
    log->size = 0;
    log->capacity = capacity;
    return log;
}

size_t log_size(const EventLog* log) {
    return log ? log->size : 0;
}

Event log_Get(const EventLog* log, int index) {
    Event error_event = {0, 0, NONE, 0};

    if (!log || index < 0 || (size_t)index >= log->size) {
        return error_event;
    }
    return log->events[index];
}

void log_append(EventLog* log, Event e) {
    if (!log) return;

    if (log->size >= log->capacity) {
        size_t new_capacity = log->capacity * 2;
        Event* new_events = realloc(log->events, new_capacity * sizeof(Event));

        if (!new_events) {
            return;
        }
        log->events = new_events;
        log->capacity = new_capacity;
    }

    log->events[log->size] = e;
    log->size++;
}

void log_set(EventLog* log, int index, Event e) {
    if (!log || index < 0 || (size_t)index >= log->size) {
        return;
    }

    log->events[index] = e;
}

void log_destroy(EventLog* log) {
    if (!log) return;

    free(log->events);
    free(log);
}