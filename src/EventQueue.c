#include "EventQueue.h"
#include "Event.h"
#include <stdlib.h>


struct EventQueue {
    Event** buffer;
    size_t capacity;
    size_t head;      // Index where next item will be written
    size_t tail;      // Index where next item will be read
    size_t count;
};

EventQueue* queue_create(size_t capacity) {
    if (capacity == 0) return NULL;
    
    EventQueue* queue = malloc(sizeof(EventQueue));
    if (!queue) return NULL;
    
    queue->buffer = malloc(sizeof(Event*) * capacity);
    if (!queue->buffer) {
        free(queue);
        return NULL;
    }
    queue->capacity = capacity;
    queue->head = 0;
    queue->tail = 0;
    queue->count = 0;
    return queue;
}

void queue_destroy(EventQueue* queue) {
    if (queue) {
        for (size_t i = 0; i < queue->count; i++) {
            size_t index = (queue->tail + i) % queue->capacity;
            free(queue->buffer[index]);
        }
        free(queue->buffer);
        free(queue);
    }
}

bool queue_enqueue(EventQueue* queue, const Event* event) {
    if (!queue || queue_is_full(queue)) {
        return false;
    }
    queue->buffer[queue->head] = *event;
    queue->head = (queue->head + 1) % queue->capacity;
    queue->count++;
    return true;
}

bool queue_dequeue(EventQueue* queue, Event* out_event) {
    if (!queue || !out_event || queue_is_empty(queue)) {
        return false;
    }
    
    *out_event = queue->buffer[queue->tail];
    queue->tail = (queue->tail + 1) % queue->capacity;
    queue->count--;
    
    return true;
}

bool queue_peek(const EventQueue* queue, Event* out_event) {
    if (!queue || !out_event || queue_is_empty(queue)) {
        return false;
    }
    
    *out_event = queue->buffer[queue->tail];
    return true;
}

bool queue_is_empty(const EventQueue* queue) {
    return queue && queue->count == 0;
}

bool queue_is_full(const EventQueue* queue) {
    return queue && queue->count == queue->capacity;
}

size_t queue_size(const EventQueue* queue) {
    return queue ? queue->count : 0;
}

size_t queue_capacity(const EventQueue* queue) {
    return queue ? queue->capacity : 0;
}

void queue_clear(EventQueue* queue) {
    if (queue) { //TODO also looks wrong.
        queue->head = 0;
        queue->tail = 0;
        queue->count = 0;
    }
}