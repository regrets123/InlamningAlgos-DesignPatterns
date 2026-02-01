#ifndef INLAMNINGALGOS_DESIGNPATTERNS_APPSTATE_H
#define INLAMNINGALGOS_DESIGNPATTERNS_APPSTATE_H

#include "EventQueue.h"
#include "EventLog.h"
#include "Event.h"
#include "UserInterface.h"

typedef struct AppState {
    EventQueue* queue;
    EventLog* log;
    Event* eventPool;
    size_t eventCount;
    size_t eventPoolSize;
    size_t eventPoolCapacity;
    menuOptions currentOption;
} AppState;

AppState* appState_get();
void appState_destroy();

#endif //INLAMNINGALGOS_DESIGNPATTERNS_APPSTATE_H
