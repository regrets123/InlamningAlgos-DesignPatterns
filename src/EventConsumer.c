//
#include "EventConsumer.h"

void consumeEvent(EventQueue* queue) {
    log_append(log, queue_dequeue(queue));
}

bool ensureLogInitialized() {
    if (log == NULL) {
        log = log_create(50);
    }
    return log != NULL;
}