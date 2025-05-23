#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int counter;
    pthread_mutex_t lock;
} SharedData;

void* increment(void* arg)
{
    SharedData* data = (SharedData*) arg;
    printf("hello inside increment \n\n");
    for (int i = 0; i < 100000000; i++) {
        pthread_mutex_lock(&data->lock);   // Lock the mutex
        data->counter++;                    // Critical section
        pthread_mutex_unlock(&data->lock); // Unlock the mutex
    }

    return NULL;
}

int main() {
    pthread_t t1, t2;
    SharedData data = {0, PTHREAD_MUTEX_INITIALIZER};  // Initialize struct with a mutex

    // Create two threads that increment the counter
    pthread_create(&t1, NULL, increment, (void*)&data);
    pthread_create(&t2, NULL, increment, (void*)&data);

    // Wait for both threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final counter value: %d\n", data.counter);

    // Destroy the mutex after use
    pthread_mutex_destroy(&data.lock);

    return 0;
}

