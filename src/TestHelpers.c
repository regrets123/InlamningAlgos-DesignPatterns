#include <stdio.h>
#include <stdbool.h>
#include "TestHelpers.h"
#include "EventLog.h"
#include "EventQueue.h"
#include "EventSort.h"

void print_event(const Event* e) {
    const char* type_str[] = {"NONE", "TEMP", "BUTTON", "MOTION"};
    printf("Event[time=%lld, sensor=%d, type=%s, value=%d]\n",
           e->timeStamp, e->sensorId, type_str[e->type], e->value);
}

void test_eventLog() {
    printf("\n=== EventLog Tests ===\n");
    int passed = 0;
    int failed = 0;

    printf("Test 1: log_create... ");
    EventLog* log = log_create(4);
    if (log != NULL) {
        printf("PASSED\n");
        passed++;
    } else {
        printf("FAILED\n");
        failed++;
    }

    printf("Test 2: Empty log size... ");
    if (log_size(log) == 0) {
        printf("PASSED\n");
        passed++;
    } else {
        printf("FAILED (expected 0, got %zu)\n", log_size(log));
        failed++;
    }

    printf("Test 3: log_append... ");
    Event e1 = {100, 1, TEMP, 25};
    Event e2 = {200, 2, BUTTON, 1};
    Event e3 = {300, 3, MOTION, 50};
    log_append(log, &e1);
    log_append(log, &e2);
    log_append(log, &e3);
    if (log_size(log) == 3) {
        printf("PASSED\n");
        passed++;
    } else {
        printf("FAILED (expected 3, got %zu)\n", log_size(log));
        failed++;
    }

    printf("Test 4: log_Get... ");
    const Event* retrieved = log_Get(log, 0);
    if (retrieved != NULL && retrieved->sensorId == 1 && retrieved->type == TEMP && retrieved->value == 25) {
        printf("PASSED\n");
        passed++;
    } else {
        printf("FAILED\n");
        failed++;
    }

    printf("Test 5: log_Get middle element... ");
    retrieved = log_Get(log, 1);
    if (retrieved != NULL && retrieved->sensorId == 2 && retrieved->type == BUTTON) {
        printf("PASSED\n");
        passed++;
    } else {
        printf("FAILED\n");
        failed++;
    }

    printf("Test 6: log_Get negative index... ");
    retrieved = log_Get(log, -1);
    if (retrieved == NULL) {
        printf("PASSED\n");
        passed++;
    } else {
        printf("FAILED (should return NULL)\n");
        failed++;
    }

    printf("Test 7: log_Get out of bounds... ");
    retrieved = log_Get(log, 10);
    if (retrieved == NULL) {
        printf("PASSED\n");
        passed++;
    } else {
        printf("FAILED (should return NULL)\n");
        failed++;
    }

    printf("Test 8: log_set... ");
    Event e4 = {400, 4, MOTION, 100};
    log_set(log, 1, &e4);
    retrieved = log_Get(log, 1);
    if (retrieved != NULL && retrieved->sensorId == 4 && retrieved->value == 100) {
        printf("PASSED\n");
        passed++;
    } else {
        printf("FAILED\n");
        failed++;
    }

    printf("Test 9: log_set invalid index... ");
    log_set(log, 100, &e4);
    if (log_size(log) == 3) {
        printf("PASSED\n");
        passed++;
    } else {
        printf("FAILED\n");
        failed++;
    }

    printf("Test 10: Auto-expand capacity... ");
    Event e5 = {500, 5, TEMP, 30};
    Event e6 = {600, 6, BUTTON, 0};
    Event e7 = {700, 7, MOTION, 75};
    log_append(log, &e5);
    log_append(log, &e6);
    log_append(log, &e7);
    if (log_size(log) == 6) {
        printf("PASSED\n");
        passed++;
    } else {
        printf("FAILED (expected 6, got %zu)\n", log_size(log));
        failed++;
    }

    printf("Test 11: NULL log handling... ");
    if (log_size(NULL) == 0 && log_Get(NULL, 0) == NULL) {
        printf("PASSED\n");
        passed++;
    } else {
        printf("FAILED\n");
        failed++;
    }

    printf("Test 12: log_append NULL log... ");
    log_append(NULL, &e1);
    printf("PASSED (no crash)\n");
    passed++;

    printf("Test 13: log_set NULL log... ");
    log_set(NULL, 0, &e1);
    printf("PASSED (no crash)\n");
    passed++;
    log_destroy(log);

    printf("Test 14: log_destroy NULL... ");
    log_destroy(NULL);
    printf("PASSED (no crash)\n");
    passed++;
    printf("\nEventLog Results: %d passed, %d failed\n", passed, failed);
}

void test_eventQueue() {
    printf("\n=== EventQueue Tests ===\n");
    int passed = 0;
    int failed = 0;

    printf("Test 1: queue_create... ");
    EventQueue* queue = queue_create(4);
    if (queue != NULL) {
        printf("PASSED\n");
        passed++;
    } else {
        printf("FAILED\n");
        failed++;
    }

    printf("Test 2: queue_create zero capacity... ");
    EventQueue* invalid_queue = queue_create(0);
    if (invalid_queue == NULL) {
        printf("PASSED\n");
        passed++;
    } else {
        printf("FAILED (should return NULL)\n");
        queue_destroy(invalid_queue);
        failed++;
    }
    printf("Test 3: Empty queue state... ");
    if (queue_is_empty(queue) && !queue_is_full(queue) && queue_size(queue) == 0 && queue_capacity(queue) == 4) {
        printf("PASSED\n");
        passed++;
    } else {
        printf("FAILED\n");
        failed++;
    }

    printf("Test 4: queue_enqueue... ");
    Event e1 = {100, 1, TEMP, 25};
    Event e2 = {200, 2, BUTTON, 1};
    Event e3 = {300, 3, MOTION, 50};
    bool r1 = queue_enqueue(queue, &e1);
    bool r2 = queue_enqueue(queue, &e2);
    bool r3 = queue_enqueue(queue, &e3);
    if (r1 && r2 && r3 && queue_size(queue) == 3) {
        printf("PASSED\n");
        passed++;
    } else {
        printf("FAILED\n");
        failed++;
    }

    printf("Test 5: queue_peek... ");
    const Event* peeked = queue_peek(queue);
    if (peeked != NULL && peeked->sensorId == 1 && peeked->type == TEMP && queue_size(queue) == 3) {
        printf("PASSED\n");
        passed++;
    } else {
        printf("FAILED\n");
        failed++;
    }

    printf("Test 6: queue_dequeue... ");
    const Event* dequeued = queue_dequeue(queue);
    if (dequeued != NULL && dequeued->sensorId == 1 && queue_size(queue) == 2) {
        printf("PASSED\n");
        passed++;
    } else {
        printf("FAILED\n");
        failed++;
    }

    printf("Test 7: FIFO order... ");
    dequeued = queue_dequeue(queue);
    if (dequeued != NULL && dequeued->sensorId == 2) {
        printf("PASSED\n");
        passed++;
    } else {
        printf("FAILED\n");
        failed++;
    }

    printf("Test 8: Fill to capacity... ");
    Event e4 = {400, 4, TEMP, 30};
    Event e5 = {500, 5, BUTTON, 0};
    Event e6 = {600, 6, MOTION, 75};
    queue_enqueue(queue, &e4);
    queue_enqueue(queue, &e5);
    queue_enqueue(queue, &e6);  // Now 4 elements: e3, e4, e5, e6
    if (queue_is_full(queue) && queue_size(queue) == 4) {
        printf("PASSED\n");
        passed++;
    } else {
        printf("FAILED (size=%zu, full=%d)\n", queue_size(queue), queue_is_full(queue));
        failed++;
    }

    printf("Test 9: Enqueue on full queue... ");
    Event e7 = {700, 7, NONE, 0};
    bool result = queue_enqueue(queue, &e7);
    if (!result && queue_size(queue) == 4) {
        printf("PASSED\n");
        passed++;
    } else {
        printf("FAILED\n");
        failed++;
    }

    printf("Test 10: Circular buffer wrap-around... ");
    // Dequeue two and enqueue two new ones to test wrap-around
    queue_dequeue(queue);  // Remove e3
    queue_dequeue(queue);  // Remove e4
    Event e8 = {800, 8, TEMP, 40};
    Event e9 = {900, 9, BUTTON, 1};
    queue_enqueue(queue, &e8);
    queue_enqueue(queue, &e9);
    // Should now contain: e5, e6, e8, e9 in FIFO order
    const Event* first = queue_peek(queue);
    if (first != NULL && first->sensorId == 5 && queue_size(queue) == 4) {
        printf("PASSED\n");
        passed++;
    } else {
        printf("FAILED\n");
        failed++;
    }

    printf("Test 11: queue_clear... ");
    queue_clear(queue);
    if (queue_is_empty(queue) && queue_size(queue) == 0 && queue_capacity(queue) == 4) {
        printf("PASSED\n");
        passed++;
    } else {
        printf("FAILED\n");
        failed++;
    }

    printf("Test 12: Dequeue from empty queue... ");
    dequeued = queue_dequeue(queue);
    if (dequeued == NULL) {
        printf("PASSED\n");
        passed++;
    } else {
        printf("FAILED (should return NULL)\n");
        failed++;
    }

    printf("Test 13: Peek on empty queue... ");
    peeked = queue_peek(queue);
    if (peeked == NULL) {
        printf("PASSED\n");
        passed++;
    } else {
        printf("FAILED (should return NULL)\n");
        failed++;
    }

    printf("Test 14: NULL queue handling... ");
    if (queue_size(NULL) == 0 && queue_capacity(NULL) == 0 &&
        queue_peek(NULL) == NULL && queue_dequeue(NULL) == NULL &&
        !queue_enqueue(NULL, &e1)) {
        printf("PASSED\n");
        passed++;
    } else {
        printf("FAILED\n");
        failed++;
    }

    printf("Test 15: queue_is_empty NULL... ");
    if (!queue_is_empty(NULL)) {
        printf("PASSED\n");
        passed++;
    } else {
        printf("FAILED (should return false for NULL)\n");
        failed++;
    }

    printf("Test 16: queue_is_full NULL... ");
    if (!queue_is_full(NULL)) {
        printf("PASSED\n");
        passed++;
    } else {
        printf("FAILED (should return false for NULL)\n");
        failed++;
    }

    printf("Test 17: queue_clear NULL... ");
    queue_clear(NULL);
    printf("PASSED (no crash)\n");
    passed++;

    queue_destroy(queue);

    printf("Test 18: queue_destroy NULL... ");
    queue_destroy(NULL);  // Should not crash
    printf("PASSED (no crash)\n");
    passed++;

    printf("\nEventQueue Results: %d passed, %d failed\n", passed, failed);
}

void test_eventSort() {
    printf("\n=== EventSort Tests ===\n");
    int passed = 0;
    int failed = 0;

    // Create test events with different values for sorting
    Event e1 = {300, 5, TEMP, 25};
    Event e2 = {100, 2, BUTTON, 50};
    Event e3 = {200, 8, MOTION, 10};
    Event e4 = {400, 1, TEMP, 75};
    Event e5 = {150, 3, NONE, 30};

    // Test InsertionSort by timestamp
    printf("Test 1: InsertionSort by timestamp... ");
    EventLog* log1 = log_create(10);
    log_append(log1, &e1);
    log_append(log1, &e2);
    log_append(log1, &e3);
    log_append(log1, &e4);
    log_append(log1, &e5);
    insertionSort(log1, compareByTimestamp);
    bool sorted = true;
    for (size_t i = 1; i < log_size(log1); i++) {
        if (log_Get(log1, (int)(i-1))->timeStamp > log_Get(log1, (int)i)->timeStamp) {
            sorted = false;
            break;
        }
    }
    if (sorted) {
        printf("PASSED\n");
        passed++;
    } else {
        printf("FAILED\n");
        failed++;
    }
    log_destroy(log1);

    // Test SelectionSort by sensorId
    printf("Test 2: SelectionSort by sensorId... ");
    EventLog* log2 = log_create(10);
    log_append(log2, &e1);
    log_append(log2, &e2);
    log_append(log2, &e3);
    log_append(log2, &e4);
    log_append(log2, &e5);
    selectionSort(log2, compareBySensorId);
    sorted = true;
    for (size_t i = 1; i < log_size(log2); i++) {
        if (log_Get(log2, (int)(i-1))->sensorId > log_Get(log2, (int)i)->sensorId) {
            sorted = false;
            break;
        }
    }
    if (sorted) {
        printf("PASSED\n");
        passed++;
    } else {
        printf("FAILED\n");
        failed++;
    }
    log_destroy(log2);

    // Test BubbleSort by value
    printf("Test 3: BubbleSort by value... ");
    EventLog* log3 = log_create(10);
    log_append(log3, &e1);
    log_append(log3, &e2);
    log_append(log3, &e3);
    log_append(log3, &e4);
    log_append(log3, &e5);
    bubbleSort(log3, compareByValue);
    sorted = true;
    for (size_t i = 1; i < log_size(log3); i++) {
        if (log_Get(log3, (int)(i-1))->value > log_Get(log3, (int)i)->value) {
            sorted = false;
            break;
        }
    }
    if (sorted) {
        printf("PASSED\n");
        passed++;
    } else {
        printf("FAILED\n");
        failed++;
    }
    log_destroy(log3);

    // Test sortLog HOF with InsertionSort
    printf("Test 4: sortLog HOF with InsertionSort... ");
    EventLog* log4 = log_create(10);
    log_append(log4, &e1);
    log_append(log4, &e2);
    log_append(log4, &e3);
    log_append(log4, &e4);
    log_append(log4, &e5);
    sortLog(log4, insertionSort, compareByType);
    sorted = true;
    for (size_t i = 1; i < log_size(log4); i++) {
        if (log_Get(log4, (int)(i-1))->type > log_Get(log4, (int)i)->type) {
            sorted = false;
            break;
        }
    }
    if (sorted) {
        printf("PASSED\n");
        passed++;
    } else {
        printf("FAILED\n");
        failed++;
    }
    log_destroy(log4);

    // Test sortLog HOF with SelectionSort
    printf("Test 5: sortLog HOF with SelectionSort... ");
    EventLog* log5 = log_create(10);
    log_append(log5, &e1);
    log_append(log5, &e2);
    log_append(log5, &e3);
    log_append(log5, &e4);
    log_append(log5, &e5);
    sortLog(log5, selectionSort, compareByTimestamp);
    sorted = true;
    for (size_t i = 1; i < log_size(log5); i++) {
        if (log_Get(log5, (int)(i-1))->timeStamp > log_Get(log5, (int)i)->timeStamp) {
            sorted = false;
            break;
        }
    }
    if (sorted) {
        printf("PASSED\n");
        passed++;
    } else {
        printf("FAILED\n");
        failed++;
    }
    log_destroy(log5);

    // Test sortLog HOF with BubbleSort
    printf("Test 6: sortLog HOF with BubbleSort... ");
    EventLog* log6 = log_create(10);
    log_append(log6, &e1);
    log_append(log6, &e2);
    log_append(log6, &e3);
    log_append(log6, &e4);
    log_append(log6, &e5);
    sortLog(log6, bubbleSort, compareBySensorId);
    sorted = true;
    for (size_t i = 1; i < log_size(log6); i++) {
        if (log_Get(log6, (int)(i-1))->sensorId > log_Get(log6, (int)i)->sensorId) {
            sorted = false;
            break;
        }
    }
    if (sorted) {
        printf("PASSED\n");
        passed++;
    } else {
        printf("FAILED\n");
        failed++;
    }
    log_destroy(log6);

    // Test empty log
    printf("Test 7: Sort empty log... ");
    EventLog* log7 = log_create(10);
    insertionSort(log7, compareByTimestamp);
    if (log_size(log7) == 0) {
        printf("PASSED\n");
        passed++;
    } else {
        printf("FAILED\n");
        failed++;
    }
    log_destroy(log7);

    // Test single element log
    printf("Test 8: Sort single element log... ");
    EventLog* log8 = log_create(10);
    log_append(log8, &e1);
    selectionSort(log8, compareByTimestamp);
    if (log_size(log8) == 1 && log_Get(log8, 0) == &e1) {
        printf("PASSED\n");
        passed++;
    } else {
        printf("FAILED\n");
        failed++;
    }
    log_destroy(log8);

    // Test NULL handling
    printf("Test 9: Sort NULL log... ");
    insertionSort(NULL, compareByTimestamp);
    selectionSort(NULL, compareBySensorId);
    bubbleSort(NULL, compareByValue);
    sortLog(NULL, insertionSort, compareByTimestamp);
    printf("PASSED (no crash)\n");
    passed++;

    // Test NULL comparator
    printf("Test 10: Sort with NULL comparator... ");
    EventLog* log10 = log_create(10);
    log_append(log10, &e1);
    log_append(log10, &e2);
    insertionSort(log10, NULL);
    selectionSort(log10, NULL);
    bubbleSort(log10, NULL);
    sortLog(log10, insertionSort, NULL);
    printf("PASSED (no crash)\n");
    passed++;
    log_destroy(log10);

    // Test NULL sort function in HOF
    printf("Test 11: sortLog with NULL sort function... ");
    EventLog* log11 = log_create(10);
    log_append(log11, &e1);
    sortLog(log11, NULL, compareByTimestamp);
    printf("PASSED (no crash)\n");
    passed++;
    log_destroy(log11);

    // Test pointer stability (verify only pointers moved, not data)
    printf("Test 12: Pointer stability... ");
    EventLog* log12 = log_create(10);
    log_append(log12, &e1);
    log_append(log12, &e2);
    log_append(log12, &e3);
    insertionSort(log12, compareByTimestamp);
    // After sort by timestamp, order should be: e2(100), e3(200), e1(300)
    bool pointersCorrect = (log_Get(log12, 0) == &e2) &&
                           (log_Get(log12, 1) == &e3) &&
                           (log_Get(log12, 2) == &e1);
    if (pointersCorrect) {
        printf("PASSED\n");
        passed++;
    } else {
        printf("FAILED\n");
        failed++;
    }
    log_destroy(log12);

    printf("\nEventSort Results: %d passed, %d failed\n", passed, failed);
}