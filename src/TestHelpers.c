#include <stdio.h>
#include "include/TestHelpers.h"
#include "include/EventLog.h"
#include "include/EventQueue.h"

void print_event(Event e) {
    const char* type_str[] = {"NONE", "TEMP", "BUTTON", "MOTION"};
    printf("Event[time=%d, sensor=%d, type=%s, value=%d]\n",
           e.timeStamp, e.sensorId, type_str[e.type], e.value);
}

void test_eventLog() {
    printf("=== Testing EventLog ===\n\n");

    // Create log with small capacity to test doubling
    EventLog* log = log_create(2);
    printf("Created log with capacity 2\n");
    printf("Initial size: %zu\n\n", log_size(log));
    Event e1 = {100, 1, TEMP, 25};
    Event e2 = {200, 2, BUTTON, 1};
    Event e3 = {300, 3, MOTION, 5};
    Event e4 = {400, 4, TEMP, 30};
    printf("Appending 4 events (should trigger capacity doubling)...\n");
    log_append(log, e1);
    printf("Size after 1st append: %zu\n", log_size(log));
    log_append(log, e2);
    printf("Size after 2nd append: %zu\n", log_size(log));
    log_append(log, e3);
    printf("Size after 3rd append: %zu (capacity doubled!)\n", log_size(log));
    log_append(log, e4);
    printf("Size after 4th append: %zu\n\n", log_size(log));

    printf("Reading all events with log_Get:\n");
    for (int i = 0; i < (int)log_size(log); i++) {
        Event e = log_Get(log, i);
        printf("  [%d] ", i);
        print_event(e);
    }
    printf("\n");

    printf("Testing bounds check (invalid index -1):\n");
    Event invalid = log_Get(log, -1);
    printf("  Returned: ");
    print_event(invalid);

    printf("Testing bounds check (invalid index 100):\n");
    invalid = log_Get(log, 100);
    printf("  Returned: ");
    print_event(invalid);
    printf("\n");

    printf("Modifying event at index 1...\n");
    Event e_new = {250, 2, BUTTON, 0};
    log_set(log, 1, e_new);
    printf("  After modification: ");
    print_event(log_Get(log, 1));
    printf("\n");

    log_destroy(log);
    printf("Log destroyed\n\n");
}

void test_eventQueue() {
    printf("=== Testing EventQueue ===\n\n");

    EventQueue* queue = queue_create(3);
    printf("Created queue with capacity 3\n");
    printf("Is empty: %s\n", queue_is_empty(queue) ? "true" : "false");
    printf("Size: %zu, Capacity: %zu\n\n", queue_size(queue), queue_capacity(queue));

    Event e1 = {100, 1, TEMP, 25};
    Event e2 = {200, 2, BUTTON, 1};
    Event e3 = {300, 3, MOTION, 5};
    Event e4 = {400, 4, TEMP, 30};

    printf("Enqueuing 3 events...\n");
    printf("Enqueue e1: %s\n", queue_enqueue(queue, e1) ? "success" : "failed");
    printf("Enqueue e2: %s\n", queue_enqueue(queue, e2) ? "success" : "failed");
    printf("Enqueue e3: %s\n", queue_enqueue(queue, e3) ? "success" : "failed");
    printf("Is full: %s\n", queue_is_full(queue) ? "true" : "false");
    printf("Size: %zu\n\n", queue_size(queue));

    printf("Trying to enqueue when full:\n");
    printf("Enqueue e4: %s\n\n", queue_enqueue(queue, e4) ? "success" : "failed");

    Event peeked;
    printf("Peeking at front:\n");
    if (queue_peek(queue, &peeked)) {
        printf("  ");
        print_event(peeked);
    }
    printf("Size after peek: %zu (should be unchanged)\n\n", queue_size(queue));

    Event dequeued;
    printf("Dequeuing all events:\n");
    while (queue_dequeue(queue, &dequeued)) {
        printf("  Dequeued: ");
        print_event(dequeued);
        printf("  Size now: %zu\n", queue_size(queue));
    }
    printf("Is empty: %s\n\n", queue_is_empty(queue) ? "true" : "false");

    printf("Testing circular buffer behavior:\n");
    queue_enqueue(queue, e1);
    queue_enqueue(queue, e2);
    queue_dequeue(queue, &dequeued);  // Remove e1
    queue_enqueue(queue, e3);
    queue_enqueue(queue, e4);  // This should wrap around

    printf("After enqueue-dequeue-enqueue sequence:\n");
    while (queue_dequeue(queue, &dequeued)) {
        printf("  ");
        print_event(dequeued);
    }
    printf("\n");

    queue_enqueue(queue, e1);
    queue_enqueue(queue, e2);
    printf("Size before clear: %zu\n", queue_size(queue));
    queue_clear(queue);
    printf("Size after clear: %zu\n", queue_size(queue));
    printf("Is empty: %s\n\n", queue_is_empty(queue) ? "true" : "false");

    queue_destroy(queue);
    printf("Queue destroyed\n\n");
}