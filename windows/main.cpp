#include <stdio.h>
#include "ptr_t.h"

using namespace ptr;

int main() {
    ptr_t ptr;

    ptr = calloc(sizeof(int), 5);
    ptr.info();
    for (int i = 0; i < 5; ++i) {
        ((int*)ptr)[i] = i;
        printf("%d = %d\n", i, ((int*)ptr)[i]);
    }
    ptr = realloc(ptr, sizeof(int) * 10);
    ptr.info();
    for (int i = 0; i < 10; ++i) {
        printf("%d = %d\n", i, ((int*)ptr)[i]);
    }
    free(ptr);

    return 0;
}