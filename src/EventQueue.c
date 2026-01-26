#include "EventQueue.h"
#include "Event.h"
#include <stdlib.h>

struct EventQueue {
    const Event** buffer;
    size_t capacity;
    size_t head;
    size_t tail;
    size_t count;
};

EventQueue* queue_create(size_t capacity) {
    if (capacity == 0) return NULL;

    EventQueue* queue = malloc(sizeof(EventQueue));
    if (!queue) return NULL;

    queue->buffer = malloc(sizeof(const Event*) * capacity);
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
        // Don't free the events - they're owned by the memory pool
        free(queue->buffer);
        free(queue);
    }
}

bool queue_enqueue(EventQueue* queue, const Event* event) {
    if (!queue || queue_is_full(queue)) {
        return false;
    }
    queue->buffer[queue->head] = event;
    queue->head = (queue->head + 1) % queue->capacity;
    queue->count++;
    return true;
}

const Event* queue_dequeue(EventQueue *queue) {
    if (!queue || queue_is_empty(queue)) {
        return NULL;
    }

    const Event* event = queue->buffer[queue->tail];
    queue->tail = (queue->tail + 1) % queue->capacity;
    queue->count--;
    return event;
}

const Event* queue_peek(const EventQueue* queue) {
    if (!queue || queue_is_empty(queue)) {
        return NULL;
    }

    return queue->buffer[queue->tail];
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
    if (queue) {
        queue->head = 0;
        queue->tail = 0;
        queue->count = 0;
    }
}

const Event* queue_get(const EventQueue* queue, size_t index) {
    if (!queue || index >= queue->count) {
        return NULL;
    }
    size_t actualIndex = (queue->tail + index) % queue->capacity;
    return queue->buffer[actualIndex];
}