//
#include "EventConsumer.h"
#include "AppState.h"

void consumeEvent(EventQueue* queue) {
    const Event* toLog = queue_dequeue(queue);
    log_append(appState_get()->log, toLog);
}
