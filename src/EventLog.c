#include <stdlib.h>
#include "EventLog.h"
#include "Event.h"

struct EventLog {
    const Event** events;
    size_t size;
    size_t capacity;
};

EventLog* log_create(size_t capacity) {
    EventLog* log = malloc(sizeof(EventLog));
    if (!log) return NULL;
    log->events = malloc(capacity * sizeof(Event*));
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

const Event* log_Get(const EventLog* log, int index) {
    if (!log || index < 0 || (size_t)index >= log->size) {
        return NULL ;
    }
    return log->events[index];
}

void log_append(EventLog* log, const Event* e) {
    if (!log || !e) return;

    if (log->size >= log->capacity) {
        size_t new_capacity = log->capacity * 2;
        const Event** new_events = realloc(log->events, new_capacity * sizeof(const Event*));
        if (!new_events) {
            return;
        }
        log->events = new_events;
        log->capacity = new_capacity;
    }
    log->events[log->size] = e;
    log->size++;
}

void log_set(EventLog* log, int index, Event* e) {
    if (!log || index < 0 || (size_t)index >= log->size) {
        return;
    }
    log->events[index] = e;
}

void log_swap(EventLog* log, int i, int j) {
    if (!log || i < 0 || j < 0 || (size_t)i >= log->size || (size_t)j >= log->size) {
        return;
    }
    const Event* temp = log->events[i];
    log->events[i] = log->events[j];
    log->events[j] = temp;
}

void log_rebase(EventLog* log, ptrdiff_t delta) {
    if (!log || delta == 0) return;
    for (size_t i = 0; i < log->size; i++) {
        log->events[i] = (const Event*)((const char*)log->events[i] + delta);
    }
}

void log_destroy(EventLog* log) {
    if (!log) return;

    free(log->events);
    free(log);
}