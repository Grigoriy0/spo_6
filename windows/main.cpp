#include <cstdio>
#include "ptr_t.h"


int main() {
    ptr::ptr_t ptr = ptr::malloc(5 * sizeof(int));
    for (int i = 0; i < 5; ++i) {
        *(int*)ptr = i;
        printf("%d = %d\n", i, *(int*)ptr);
    }
    ptr::free(ptr);

    return 0;
}