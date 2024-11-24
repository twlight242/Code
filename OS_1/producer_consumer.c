#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t full;
sem_t empty;
pthread_mutex_t mutex;

int buffer_size = 5;
int buffer[5];
int in = 0, out = 0;
int item_count;

int produce_item() {
    return (rand() % 100) + 1;  // Produce a random item
}

void consume_item(int item) {
    printf("Consumed: %d\n", item);  // Consume the item
}

void* producer(void* args) {
    int id = *(int *)args;  // Producer ID
    int item;
    for (int i = 0; i < item_count; ++i) {
        item = produce_item();  // Generate a new item

        sem_wait(&empty);  // Wait if the buffer is full
        pthread_mutex_lock(&mutex);  // Lock the buffer for exclusive access

        buffer[in] = item;  // Add item to the buffer
        printf("Producer %d produced: %d\n", id, item);
        in = (in + 1) % buffer_size;  // Use modulo for circular buffer

        pthread_mutex_unlock(&mutex);  // Unlock the buffer
        sem_post(&full);  // Signal that the buffer has a new item

        sleep(1);  // Simulate production time
    }
    return NULL;
}

void* consumer(void* args) {
    int id = *(int *)args;  // Consumer ID
    int item;
    for (int i = 0; i < item_count; ++i) {
        sem_wait(&full);  // Wait if the buffer is empty
        pthread_mutex_lock(&mutex);  // Lock the buffer for exclusive access

        item = buffer[out]; 
        buffer[out] = 0;  
       // Check if item is valid
        printf("Consumer %d consumed: %d\n", id, item);
        

        out = (out + 1) % buffer_size;  // Use modulo for circular buffer

        pthread_mutex_unlock(&mutex);  // Unlock the buffer
        sem_post(&empty);  // Signal that a slot is now empty

        sleep(1);  // Simulate consumption time
    }
    return NULL;
}

// Main function
int main() {
    int producers_count = 1, consumers_count = 1; // One producer and one consumer

    printf("Enter the number of items to produce/consume: ");
    scanf("%d", &item_count);

    for (int i = 0; i < 5; ++i)
    {
    	buffer[i] = 0;
    }

   

    // Initialize semaphores and mutex
    sem_init(&empty, 0, buffer_size);  // Initially, all slots are empty
    sem_init(&full, 0, 0);             // Initially, no slots are full
    pthread_mutex_init(&mutex, NULL);  // Initialize the mutex

    // Create producer and consumer threads
    pthread_t producer_thread, consumer_thread;
    int producer_id = 1, consumer_id = 1; // IDs for producer and consumer

    // Create the producer thread
    pthread_create(&producer_thread, NULL, producer, (void *)&producer_id);

    // Create the consumer thread
    pthread_create(&consumer_thread, NULL, consumer, (void *)&consumer_id);

    // Wait for the producer thread to complete
    pthread_join(producer_thread, NULL);

    // Wait for the consumer thread to complete
    pthread_join(consumer_thread, NULL);

    // Destroy semaphores and mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;  // Exit the program
}
