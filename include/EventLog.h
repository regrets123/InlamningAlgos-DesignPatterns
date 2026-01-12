#ifndef INLAMNINGALGOS_DESIGNPATTERNS_EVENTLOG_H
#define INLAMNINGALGOS_DESIGNPATTERNS_EVENTLOG_H
#include <stddef.h>
#include "include/Event.h"

typedef struct EventLog EventLog;

EventLog* log_create(size_t capacity);
size_t log_size(const EventLog* log);
Event log_Get(const EventLog* log, int index);
void log_destroy(EventLog* log);
void log_append(EventLog* log, Event e);
void log_set(EventLog* log, int index, Event e);

#endif //INLAMNINGALGOS_DESIGNPATTERNS_EVENTLOG_H