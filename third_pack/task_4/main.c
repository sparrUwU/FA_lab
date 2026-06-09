#include <stdio.h>
#include "heap.h"

int main() {
    Heap heap = create_heap(2);

    for (int i = 6; i != 0; --i) {
        push_heap(&heap, i);
        size_t size = size_heap(&heap);
        printf("size: %zu, last: %d\n", size, i);
    }
    printf("\n");
    
    for (int i = 0; i != 6; ++i) {
        printf("%d: %d\n", i, pop_heap(&heap));
    }
    delete_heap(&heap);
    return 0;
}