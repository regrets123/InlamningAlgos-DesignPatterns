#include "EventSort.h"
#include <stdbool.h>
#include <stdlib.h>

void insertionSort(EventLog* log, EventComparator cmp) {
    if (!log || !cmp) return;
    size_t n = log_size(log);
    if (n <= 1) return;

    for (size_t i = 1; i < n; i++) {
        int j = (int)i;
        while (j > 0 && cmp(log_Get(log, j - 1), log_Get(log, j)) > 0) {
            log_swap(log, j - 1, j);
            j--;
        }
    }
}

void selectionSort(EventLog* log, EventComparator cmp) {
    if (!log || !cmp) return;
    size_t n = log_size(log);
    if (n <= 1) return;

    for (size_t i = 0; i < n - 1; i++) {
        size_t minIdx = i;
        for (size_t j = i + 1; j < n; j++) {
            if (cmp(log_Get(log, (int)j), log_Get(log, (int)minIdx)) < 0) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            log_swap(log, (int)i, (int)minIdx);
        }
    }
}

void bubbleSort(EventLog* log, EventComparator cmp) {
    if (!log || !cmp) return;
    size_t n = log_size(log);
    if (n <= 1) return;

    for (size_t i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (size_t j = 0; j < n - 1 - i; j++) {
            if (cmp(log_Get(log, (int)j), log_Get(log, (int)(j + 1))) > 0) {
                log_swap(log, (int)j, (int)(j + 1));
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

int compareByTimestamp(const Event* a, const Event* b) {
    if (!a || !b) return 0;
    if (a->timeStamp < b->timeStamp) return -1;
    if (a->timeStamp > b->timeStamp) return 1;
    return 0;
}

int compareBySensorId(const Event* a, const Event* b) {
    if (!a || !b) return 0;
    return a->sensorId - b->sensorId;
}

int compareByValue(const Event* a, const Event* b) {
    if (!a || !b) return 0;
    return a->value - b->value;
}

int compareByType(const Event* a, const Event* b) {
    if (!a || !b) return 0;
    return (int)a->type - (int)b->type;
}

void shuffleLog(EventLog* log) {
    if (!log) return;
    size_t n = log_size(log);
    if (n <= 1) return;

    for (size_t i = n - 1; i > 0; i--) {
        size_t j = rand() % (i + 1);
        log_swap(log, (int)i, (int)j);
    }
}

void sortLog(EventLog* log, SortFunction sortFn, EventComparator cmp) {
    if (!log || !sortFn || !cmp) return;
    sortFn(log, cmp);
}