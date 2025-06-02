#include <unistd.h>
#include <stddef.h>
#include <stdio.h>

//malloc function
void *MyOwnMalloc(size_t size) {
    void *ptr = sbrk(0);            
    void *request = sbrk(size);     

    if (request == (void *) -1) {
        // sbrk failed
        return NULL;
    }

    return ptr;  
}

//free function
void MyOwnFree(void *ptr) {
    if (ptr != NULL) {
        printf("Memory at address %p has been freed\n", ptr);
    }
}

#define N 10

int main() {
    int i, *array;
    printf("\nEnter %d numbers:\n", N);

    array = MyOwnMalloc(sizeof(int) * N);
    if (!array) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (i = 0; i < N; i++)
        scanf("%d", &array[i]);

    printf("\nThe numbers are:\n");
    for (i = 0; i < N; i++)
        printf("%d ", array[i]);
    printf("\n");

    // Free the memory
    MyOwnFree(array);

    return 0;
}
