#ifndef INLAMNINGALGOS_DESIGNPATTERNS_EVENTSORT_H
#define INLAMNINGALGOS_DESIGNPATTERNS_EVENTSORT_H

#include "EventLog.h"
#include "Event.h"

typedef int (*EventComparator)(const Event* a, const Event* b);

typedef void (*SortFunction)(EventLog* log, EventComparator cmp);

void insertionSort(EventLog* log, EventComparator cmp);
void selectionSort(EventLog* log, EventComparator cmp);
void bubbleSort(EventLog* log, EventComparator cmp);

int compareByTimestamp(const Event* a, const Event* b);
int compareBySensorId(const Event* a, const Event* b);
int compareByValue(const Event* a, const Event* b);
int compareByType(const Event* a, const Event* b);

void shuffleLog(EventLog* log);
void sortLog(EventLog* log, SortFunction sortFn, EventComparator cmp);

#endif //INLAMNINGALGOS_DESIGNPATTERNS_EVENTSORT_H