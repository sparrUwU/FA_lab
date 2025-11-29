#include <stdio.h>
#include "vector.h"


static void ensure_capacity(Vector *v, size_t new_size) {
    if (new_size <= v->capacity) return;

    size_t new_capacity = v->capacity == 0 ? 1 : v->capacity;
    while (new_capacity < new_size) {
        new_capacity *= 2;
    }

    VECTOR_TYPE *new_data =
        (VECTOR_TYPE *)malloc(new_capacity * sizeof(VECTOR_TYPE));
    if (!new_data) return;

    for (size_t i = 0; i < v->size; i++) {
        new_data[i] = v->data[i];
    }

    free(v->data);
    v->data = new_data;
    v->capacity = new_capacity;
}

Vector create_vector(size_t initial_capacity, VECTOR_TYPE (*CopyFunc)(VECTOR_TYPE), void (*DeleteFunc)(VECTOR_TYPE)) {
    Vector v;
    v.size = 0;
    v.capacity = initial_capacity;
    v.CopyVoidPtr = CopyFunc;
    v.DeleteVoidPtr = DeleteFunc;

    if (initial_capacity == 0) {
        v.data = NULL;
    } else {
        v.data = (VECTOR_TYPE *)malloc(initial_capacity * sizeof(VECTOR_TYPE));
    }

    return v;
}

void erase_vector(Vector *v) {
    if (!v) return;

    if (v->DeleteVoidPtr) {
        for (size_t i = 0; i < v->size; i++) {
            v->DeleteVoidPtr(v->data[i]);
        }
    }

    free(v->data);
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}

int is_equal_vector(const Vector *v1, const Vector *v2) {
    if (v1->size != v2->size) return 0;

    for (size_t i = 0; i < v1->size; i++) {
        if (memcmp(&v1->data[i], &v2->data[i], sizeof(VECTOR_TYPE)) != 0)
            return 0;
    }

    return 1;
}

void copy_vector(Vector *dest, const Vector *src) {
    erase_vector(dest);

    dest->capacity = src->capacity;
    dest->size = src->size;
    dest->CopyVoidPtr = src->CopyVoidPtr;
    dest->DeleteVoidPtr = src->DeleteVoidPtr;

    if (src->capacity > 0) {
        dest->data = (VECTOR_TYPE *)malloc(src->capacity * sizeof(VECTOR_TYPE));
    } else {
        dest->data = NULL;
    }

    for (size_t i = 0; i < src->size; i++) {
        if (src->CopyVoidPtr)
            dest->data[i] = src->CopyVoidPtr(src->data[i]);
        else
            dest->data[i] = src->data[i];
    }
}

Vector *copy_vector_new(const Vector *src) {
    Vector *v = (Vector *)malloc(sizeof(Vector));
    *v = create_vector(src->capacity, src->CopyVoidPtr, src->DeleteVoidPtr);

    for (size_t i = 0; i < src->size; i++) {
        push_back_vector(v, src->data[i]);
    }

    return v;
}

void push_back_vector(Vector *v, VECTOR_TYPE value) {
    ensure_capacity(v, v->size + 1);

    if (v->CopyVoidPtr)
        v->data[v->size] = v->CopyVoidPtr(value);
    else
        v->data[v->size] = value;

    v->size++;
}

void delete_at_vector(Vector *v, size_t index) {
    if (index >= v->size) return;

    if (v->DeleteVoidPtr)
        v->DeleteVoidPtr(v->data[index]);

    for (size_t i = index; i + 1 < v->size; i++) {
        v->data[i] = v->data[i + 1];
    }

    v->size--;
}

VECTOR_TYPE get_at_vector(const Vector *v, size_t index) {
    return v->data[index];
}

void delete_vector(Vector *v) {
    erase_vector(v);
}
