#ifndef INLAMNINGALGOS_DESIGNPATTERNS_EVENTQUEUE_H
#define INLAMNINGALGOS_DESIGNPATTERNS_EVENTQUEUE_H
#include <stddef.h>
#include <stdbool.h>
#include "Event.h"

typedef struct EventQueue EventQueue;

EventQueue* queue_create(size_t capacity);
void queue_destroy(EventQueue* queue);

bool queue_enqueue(EventQueue* queue, Event event);
bool queue_dequeue(EventQueue* queue, Event* out_event);
bool queue_peek(const EventQueue* queue, Event* out_event);

bool queue_is_empty(const EventQueue* queue);
bool queue_is_full(const EventQueue* queue);
size_t queue_size(const EventQueue* queue);
size_t queue_capacity(const EventQueue* queue);

void queue_clear(EventQueue* queue);

#endif //INLAMNINGALGOS_DESIGNPATTERNS_EVENTQUEUE_H