#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
// Thread function to display "HELLO WORLD"
void *print_hello_world(void *arg)
{
    printf("HELLO WORLD\n");
    pthread_exit(NULL); // Terminate the thread
}
int main()
{
    pthread_t thread;
    int result;
    // Create a new thread that will execute the print_hello_world function
    result = pthread_create(&thread, NULL, print_hello_world, NULL);
    if (result != 0)
    {
        // If thread creation fails, print an error message and exit
        fprintf(stderr, "Error creating thread: %d\n", result);
        exit(1);
    }
    // Wait for the created thread to complete
    result = pthread_join(thread, NULL);
    if (result != 0)
    {
        // If joining the thread fails, print an error message and exit
        fprintf(stderr, "Error joining thread: %d\n", result);
        exit(1);
    }
    return 0;
}
