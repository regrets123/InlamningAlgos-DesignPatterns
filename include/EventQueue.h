#ifndef INLAMNINGALGOS_DESIGNPATTERNS_EVENTQUEUE_H
#define INLAMNINGALGOS_DESIGNPATTERNS_EVENTQUEUE_H
#include <stddef.h>
#include <stdbool.h>

// Forward declare the event type if it's defined elsewhere
typedef struct Event Event;

typedef struct EventQueue EventQueue;

// Create/destroy
EventQueue* queue_create(size_t capacity);
void queue_destroy(EventQueue* queue);

// Operations
bool queue_enqueue(EventQueue* queue, Event event);
bool queue_dequeue(EventQueue* queue, Event* out_event);
bool queue_peek(const EventQueue* queue, Event* out_event);

// Status
bool queue_is_empty(const EventQueue* queue);
bool queue_is_full(const EventQueue* queue);
size_t queue_size(const EventQueue* queue);
size_t queue_capacity(const EventQueue* queue);

// Optional: clear all events
void eventqueue_clear(EventQueue* queue);

#endif //INLAMNINGALGOS_DESIGNPATTERNS_EVENTQUEUE_H