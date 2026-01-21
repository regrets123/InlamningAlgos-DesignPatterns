//
#ifndef INLAMNINGALGOS_DESIGNPATTERNS_EVENTCONSUMER_H
#define INLAMNINGALGOS_DESIGNPATTERNS_EVENTCONSUMER_H
#include "EventLog.h"
#include "EventQueue.h"

static EventLog* log = NULL;

void consumeEvent(EventQueue* queue);
bool ensureLogInitialized();

#endif //INLAMNINGALGOS_DESIGNPATTERNS_EVENTCONSUMER_H