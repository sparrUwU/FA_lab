#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "heap.h"


Heap create_heap(size_t initial_capacity) {
    Heap h;
    h.size = 0;
    h.capacity = initial_capacity;

    if (initial_capacity > 0) 
        h.data = malloc(initial_capacity * sizeof(int));
    else 
        h.data = NULL;

    return h;
}

void delete_heap(Heap *h) {
    if (!h) return;

    free(h->data);
    h->data = NULL;
    h->size = 0;
    h->capacity = 0;
}

int is_empty_heap(const Heap *h) {
    return h->size == 0;
}

size_t size_heap(const Heap *h) {
    return h->size;
}

int peek_heap(const Heap *h) {
    return h->data[0];
}

void push_heap(Heap *h, int value) {
    ensure_capacity(h, h->size + 1);
    h->data[h->size] = value;
    h->size++;
    heapify_up(h, h->size - 1);
}

int pop_heap(Heap *h) {
    int min_value = h->data[0];
    h->data[0] = h->data[h->size - 1];
    h->size--;
    heapify_down(h, 0);

    return min_value;
}

Heap build_heap(const int *array, size_t n) {
    Heap h = create_heap(n);
    if (n > 0) memcpy(h.data, array, n * sizeof(int));
    h.size = n;

    for (int i = (int)(h.size / 2) - 1; i >= 0; i--) {
        heapify_down(&h, i);
    }

    return h;
}

int is_equal_heap(const Heap *h1, const Heap *h2) {
    if (h1->size != h2->size) return 0;

    for (size_t i = 0; i < h1->size; i++) {
        if (h1->data[i] != h2->data[i]) return 0;
    }

    return 1;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(Heap *h, size_t index) {
    if (index == 0) return;
    size_t parent = (index - 1) / 2;

    if (h->data[index] < h->data[parent]) {
        swap(&h->data[index], &h->data[parent]);
        heapify_up(h, parent);
    }
}

void heapify_down(Heap *h, size_t index) {
    size_t left = 2 * index + 1;
    size_t right = 2 * index + 2;
    size_t min = index;

    if (left < h->size && h->data[left] < h->data[min]) min = left;
    if (right < h->size && h->data[right] < h->data[min]) min = right;

    if (min != index) {
        swap(&h->data[index], &h->data[min]);
        heapify_down(h, min);
    }
}

void ensure_capacity(Heap *h, size_t new_size) {
    if (new_size <= h->capacity) return;
    
    size_t new_capacity;
    if (h->capacity == 0) new_capacity = 1;
    else new_capacity = h->capacity;

    while (new_capacity < new_size) new_capacity *= 2;

    int *new_data = malloc(new_capacity * sizeof(int));
    if (!new_data) return;

    if (h->data) memcpy(new_data, h->data, h->size * sizeof(int));

    free(h->data);
    h->data = new_data;
    h->capacity = new_capacity;
}