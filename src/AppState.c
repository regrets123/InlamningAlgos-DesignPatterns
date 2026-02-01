#include <stdlib.h>
#include "AppState.h"

static AppState* instance = NULL;

AppState* appState_get() {
    if (instance == NULL) {
        instance = calloc(1, sizeof(AppState));
        if (!instance) return NULL;
        instance->queue = queue_create(90);
        instance->log = log_create(50);
        instance->eventPool = NULL;
        instance->eventCount = 0;
        instance->eventPoolSize = 0;
        instance->eventPoolCapacity = 0;
        instance->currentOption = none;
    }
    return instance;
}

void appState_destroy() {
    if (instance == NULL) return;
    queue_destroy(instance->queue);
    log_destroy(instance->log);
    free(instance->eventPool);
    free(instance);
    instance = NULL;
}
