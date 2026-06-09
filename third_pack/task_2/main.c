#include <stdio.h>
#define VECTOR_TYPE int
#include "vector.h"

int copy_int(int value) { 
    return value; 
}

void delete_int(int value) { 
    (void)value; 
}

int main() {
    Vector v = create_vector(0, copy_int, delete_int);
    push_back_vector(&v, 1);
    push_back_vector(&v, 2);
    push_back_vector(&v, 3);
    
    for (size_t i = 0; i < v.size; i++) {
        printf("%zu: %d\n", i, get_at_vector(&v, i));
    }

    delete_at_vector(&v, 1);

    for (size_t i = 0; i < v.size; i++) {
        printf("%zu: %d\n", i, get_at_vector(&v, i));
    }

    delete_vector(&v); 
    return 0;
}